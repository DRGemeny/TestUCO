#include "hrdwrnet.h"
#include "QTcpSocket"
#include <QThread>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "myclient.h"
#include "TimTest_01_cmn.h"
#include <QTextStream>

int HrdwrNet::TestMACP(int numBFDNTestMACP)
{
    quint16 numFPGA = (NumUkrForWrite+1)/2;
    // номер канала для конкретного FAPGA (1 или 2)
    quint16 NumChan = ((NumUkrForWrite -1) % 2) + 1;
    int res;
    msg_t outMsg = msg_t();
    SetupUKR();
    for (int i = 1; i < 5; i++) {
        WrapInfMes("Установка мультиплексора КРП 0x52");
        res = WriteWithWaitFor(UCODN, numBFDNTestMACP, numFPGA, 0x52,  (i-1)+((NumChan-1)*4), outMsg);
        if (res){
            WrapInfMes("Ошибка установк мультиплексора КРП 0x52");  return -1; }
        StartGTS_BFDN_TestMACP(numBFDNTestMACP);
        QThread::msleep(5500);
        res = ReadFromTramBFDN_TestMACP(numBFDNTestMACP, numFPGA, i, NumChan);
        if (res){
            WrapInfMes("Ошибка чтения данных из ловушки");  return -1; }

        res = CompareRes_TestMACP(i, NumChan);
//        if (res){
  //          WrapInfMes("Ошибка сравнения");  return -1; }

        WrapInfMes("Сброс 0x53");
        res = WriteWithWaitFor(UCODN, numBFDNTestMACP, numFPGA, 0x53,  0x0022, outMsg);
        if (res){
            WrapInfMes("Ошибка сброса 0x53");  return-1; }
    }
    return 0;
}

 /**
 * @brief HrdwrNet::StartGTS_BFDN
 * @return 0 - ок -1 - неок
 * Установка времени во все плис и 1 укр старта ГТС, Тсек, Ттрап, Тндн
 */
int HrdwrNet::StartGTS_BFDN_TestMACP(int numBFDNTestMACP)
{
    WrapInfMes("Загрузка времени Tgts, Tsek, Ttrap, Tndn");
    msg_t outMsg1 = msg_t();
    msg_t outMsg2 = msg_t();
    int res;
    int del = 0x1388;
    res = ReadWithWaitFor(UCODN, numBFDNTestMACP, FPGA0, TimeReg, 3, outMsg1);
    if (res){
        WrapInfMes("Ошибка чтения времени из DD0 БФДН11");  return -1; }
    if (res) return -1;
    int time1 = outMsg1.data[1];
    if (time1 + del < 0x10000)
        outMsg1.data[1] = (time1 & 0xff00) + del;
    else
    {
        outMsg1.data[1] = del - ((0x10000 - time1) & 0x0ff00);
        outMsg1.data[2] = outMsg1.data[2] + 1;
    }
    outMsg1.data[0] = 0;
    // старт ГТС
    res = WriteWithWaitFor(l1::UKR, nUKR, l3UKR::BC, 0xE4, outMsg1.data, outMsg2);
    QList<quint16> Tsek, Tndn;
    Tsek.append(outMsg1.data);
    Tsek[0] += 0xB; // для сдвига в 0 данных
    Tndn.append(Tsek);
    Tndn[0] += 0x129;
    int colFPGA;
    if (numBFDNTestMACP == 1) colFPGA = 7;
    if (numBFDNTestMACP == 3) colFPGA = 3;
    for(quint16 i = 1; i < colFPGA; i++){
        res = WriteWithWaitFor(UCODN, numBFDNTestMACP, i, 0x53, 0x20, outMsg2);
        if (res){
            WrapInfMes("Ошибка сброса Tsek");  return -1; }
        res = WriteWithWaitFor(UCODN, numBFDNTestMACP, i, 0x21, Tsek, outMsg2);
        if (res){
            WrapInfMes("Ошибка записи времени Tсек");  return -1; }
        QList<quint16> Ttrap;
        Ttrap.append(Tsek);
//        if (i == 1)
            Ttrap[0] += 0x1;
        //    outMsg1.data[0] += 0x1AA; //для сумматора 14 АЕ
        res = WriteWithWaitFor(UCODN, numBFDNTestMACP, i, 0x51, Ttrap, outMsg2);
        if (res){
            WrapInfMes("Ошибка записи времени Ttrap");  return -1; }
        res = WriteWithWaitFor(UCODN, numBFDNTestMACP, i, 0x31, Tndn, outMsg2);
        if (res){
            WrapInfMes("Ошибка записи времени Tндн");  return -1; }
    }
    return 0;
}
/**
 * @brief HrdwrNet::ReadFromTramBFDN
 * Чтение данных из ловушки БФДН. Чтение выполняется строго блоками по 1536 данных. Данные 48 разрядов. (одно данное  = 3 16-ти разрядным словам)
 * @return
 */
int HrdwrNet::ReadFromTramBFDN_TestMACP(int numBFDNTestMACP, quint16 numFPGAr, int numMACP, int numCh)
{
    int res;
    bool ok;
    msg_t outMsg = msg_t();
    sigCh1.clear();
    WrapInfMes("Сброс 0x53");
    res = WriteWithWaitFor(UCODN, numBFDNTestMACP, numFPGAr, 0x53,  0x0002, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса 0x53");  return -1; }
    QFile file1(QString("./HwSignals/MACP/FPGA%3Channel%1Mux%2").arg(numCh).arg(numMACP - 1).arg(numFPGAr));
    QTextStream stream(&file1);
    stream.setCodec("UTF-8");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str;
    msg_t msg;
    for (int j = 0; j < 5; j ++)
    {
        WrapInfMes("Чтение ловушки");
        res = ReadWithWaitFor(UCODN, numBFDNTestMACP, numFPGAr, 0x50,  1536, msg);
        if (res){
            WrapInfMes("Ошибка чтения ловушки");  return -1; }
        for(int i = 0; i < 512; i++) //(1536/3)
        {
            str = QString("%1%2,\n").
                    //                arg((msg.data[i*3+2]) & 0xF , 1,16,QChar('0')).
                    arg(msg.data[i*3+1],4,16,QChar('0')).
                    arg(msg.data[i*3],4,16,QChar('0')).toUpper();
            stream << str;
            sigCh1.append(str.toULong(&ok,16));
        }
    }

    /*    WrapInfMes("Чтение ловушки");
    res = ReadWithWaitFor(UCODN, numBFDNTestMACP, numFPGAr, 0x50,  1536, msg);
    if (res){
        WrapInfMes("Ошибка чтения ловушки");  return -1; }
    for(int i = 0; i < 512; i++) //(1536/3)
    {
        str = QString("%1%2,\n").
//                arg((msg.data[i*3+2]) & 0xF , 1,16,QChar('0')).
                arg(msg.data[i*3+1],4,16,QChar('0')).
                arg(msg.data[i*3],4,16,QChar('0')).toUpper();
        stream << str;
        sigCh1.append(str.toULong(&ok,16));

    }
    */
    file1.close();
    return 0;
}
/**
 * @brief HrdwrNet::CompareRes
 * сравнение результатов работы Стенда с эталонными данными
 * @return 0 - данные равны; -1 - данные не равны
 */
int HrdwrNet::CompareRes_TestMACP(quint16 numMACP, quint16 numCh)
{
    int i;
    if (LoadEtalonFile_TestMACP(numMACP, sigCh1, etCh1)) return -1;
    for (i = 0 ; i< sigCh1.length(); i++){
        if (sigCh1.at(i) != etCh1.at(i)){
            emit ErrorSig(QString("Прочитанный сигнал не равен эталону!"));
            emit ErrorSig(QString("%1: Эталон = 0x%2, Имитатор = 0x%3.").arg(i).arg(etCh1[i],9,16,QChar('0')).arg(sigCh1.at(i),9,16,QChar('0')));
            return -1;
        }
    }    
    emit ErrorSig(QString("Данных для сравнения %1").arg(i));
    emit ErrorSig(QString("Прочитанный сигнал равен эталону. "));
    etCh1.clear();
    return 0;
}
/**
 * @brief HrdwrNet::LoadEtalonFile
 * загрузка данных из файлов эталона
 * @param fileStr - имя файла
 * @param sigl - количество данных для сравнения
 * @param ch массив, хранящий эталонные данные
 * @return
 */
int HrdwrNet::LoadEtalonFile_TestMACP(quint16 numMACP, QList<ulong> sigl, QList<ulong> &ch)
{
    bool ok;
    quint16 numMACP1 = ((numMACP-1) * 2) + 1;
    quint16 numMACP2 = ((numMACP-1) * 2) + 2;

    QString fileStr = QString("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_%3/data_in/InPutTime_EL%1_%2").arg(numMACP1).arg(numMACP2).arg(TrapsPar.shift);

    QFile etFile(fileStr);
    if (!etFile.open(QIODevice::ReadOnly | QIODevice::Text)){
       emit ErrorSig("Ошибка открытия файла с эталонными результатами"); return -1;}
    QTextStream tStream(&etFile);
    QString str1, str2;
    int lenF = sigl.length();
    for (int i = 0; i < lenF; i++) {
        str1 = tStream.readLine();
//        str2 = tStream.readLine();
//        ch.append(str2.mid(0, 8).toULong(&ok, 16));
        ch.append(str1.mid(0, 8).toULong(&ok, 16));
    }
    etFile.close();
    return 0;
/*
    quint16 numMACP1 = ((numMACP-1) * 2) + 1;
    quint16 numMACP2 = ((numMACP-1) * 2) + 2;

    QString fileStr1 = QString("./Data_model/Test31082020/14AE/Test31082020_Shift1/data_in/InPutTime_Test2_EL0%1").arg(numMACP1);
    bool ok;
    QFile etFile1(fileStr1);
    if (!etFile1.open(QIODevice::ReadOnly | QIODevice::Text)){
       emit ErrorSig("Ошибка открытия файла с эталонными результатами"); return -1;}
    QTextStream tStream1(&etFile1);
    QString str;
//    int lenF = 1024;
    int lenF = sigl.length();
    if ((numMACP != 3) && (numMACP != 7))
    {
        QString fileStr2 = QString("./Data_model/Test31082020/14AE/Test31082020_Shift1/data_in/InPutTime_Test2_EL0%1").arg(numMACP2);
        QFile etFile2(fileStr2);
        if (!etFile2.open(QIODevice::ReadOnly | QIODevice::Text)){
            emit ErrorSig("Ошибка открытия файла с эталонными результатами"); return -1;}
        QTextStream tStream2(&etFile2);
        for (int i = 0; i < lenF; i++) {
            str = tStream1.readLine();
            ch.append(str.mid(0, 8).toULong(&ok, 16));
            str = tStream2.readLine();
            ch.append(str.mid(0, 8).toULong(&ok, 16));
        }
    }
    else
    {
        for (int i = 0; i < lenF; i++) {
            str = tStream1.readLine();
            ch.append(str.mid(0, 8).toULong(&ok, 16));
            ch.append(0);
        }
    }
    return 0;
*/
}
