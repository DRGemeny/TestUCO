#include "hrdwrnet.h"
#include "QTcpSocket"
#include <QThread>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "myclient.h"
#include "TimTest_01_cmn.h"
#include <QTextStream>
HrdwrNet::HrdwrNet()
{

}

/**
 * @brief HrdwrNet::ResLVDS
 * Сброс Каналов LVDS и сброс КРП ловушек в БФДН1
 */
void HrdwrNet::ResLVDSBFDN1()
{
    msg_t outMsg = msg_t();
    msg_t outMsg1 = msg_t();
    int res = 0;
    WrapInfMes("Сброс LVDS");
    res = WriteWithWaitFor(UCODN, BFDN11, FPGA0, 0x1,  0x07F0, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса LVDS"); return ; }

    for(quint16 i = 1; i < 7; i++){
        WrapInfMes(QString("  Сброс КРП %1").arg(i));
        res = WriteWithWaitFor(UCODN, BFDN11, i, 0x53,  0x0001, outMsg);
        if (res){
            WrapInfMes(QString("  Ошибка сброса КРП %1").arg(i));
            return;
        }
        WrapInfMes(QString("  Статус КРП %1").arg(i));
        res = ReadWithWaitFor(UCODN, BFDN11, i, 0x41, 1, outMsg1);
        if (res){
            WrapInfMes(QString("  Ошибка чтения статуса КРП %1").arg(i));
            return;
        }
        emit ErrorSig(QString(" 0x%1\n").arg(outMsg1.data[0],4,16,QChar('0')));
        if (outMsg1.data[0] && 0x0001)
            WrapInfMes(QString("  КРП %1 откалиброван").arg(i));
        else if (outMsg1.data[0] && 0x0006)
            WrapInfMes(QString("  Ошибка калибровки КРП %1").arg(i));
    }
}
/**
 * @brief HrdwrNet::SetupUKR
 * Статр пакетов в МАЦП УКР, настройка ГТС в МАЦП УКР
 */
int HrdwrNet::SetupUKR()
{
    msg_t outMsg = msg_t();
    int res = 0;
    WrapInfMes("    Старт Пакетов");
    res = StartPackBFDN();
    if (res) return -1;
    WrapInfMes("    Мультиплексор 0xE5 = 0x2");
    foreach (quint16 nUkr, UKRlist) {
        res = WriteWithWaitFor(UKR, nUkr, l3UKR::BC, 0xE5,  0x2, outMsg);
        if (res){
            WrapInfMes("Ошибка переключения мультиплексора E5."); return -1; }
    }
    // Настройка ГТС
    WrapInfMes("    Настройка ГТС");
    res = SetupGTS();
    if (res){
        WrapInfMes("Ошибка настройки ГТС.");  return -1; }
    return 0;
}
/**
 * @brief HrdwrNet::LoadWwr
 * Загрузка файла c коэффициентами W
 */
void HrdwrNet::LoadWwr()
{
    WrapInfMes("    Загрузка W");
    LoadW();
}
/**
 * @brief HrdwrNet::ResMibl
 * Сброс Микроблейза, сброс регистра Мастер Микроблейза
 */
void HrdwrNet::ResMibl(int addrBFDN)
{
    msg_t outMsg = msg_t();
    int res;
    WrapInfMes("    Сброс Mibl");
    res = WriteWithWaitFor(UCODN, addrBFDN, FPGA0, 0x62,  1, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса Mibl");  return; }

    WrapInfMes("    Рукопожатие");
    QList <unsigned short> Addr61 = {0x3600, 0x0000};
    WriteWithWaitFor(UCODN, addrBFDN, FPGA0, 0x61,  Addr61, outMsg);

    msg_t outMsg1 = msg_t();
    WrapInfMes("    Чтение регистра Мастер");
    ReadWithWaitFor(UCODN, addrBFDN, FPGA0, 0x61, 1, outMsg1);
    if (res){
        WrapInfMes("Ошибка чтения регистра Мастер");  return; }
    emit ErrorSig(QString("    RgMaster(0x61) = 0x%1").arg(outMsg1.data[0],4,16,QChar('0')));
    if (outMsg1.data[0] != 0x3600)
    {
        emit ErrorSig("Ошибка!!!");
        logHrd->InfCommonLog("Ошибка!!!");
        return ;
    }
    WrapInfMes("    Сброс регистра Мастер");
    Addr61 = {0x0000, 0x0000};
    res = WriteWithWaitFor(UCODN, addrBFDN, FPGA0, 0x61,  Addr61, outMsg);
    if (res){
        WrapInfMes("    Ошибка сброса регистра Мастер");  return; }
}
/**
 * @brief HrdwrNet::LoadMibl
 * Загрузка программы Микроблейза
 */
int HrdwrNet::LoadMibl(QString filename, int nBFDN)
{
    WrapInfMes("    Загрузка Mb");
    return LoadMiBl(filename, nBFDN);
}
/**
 * @brief HrdwrNet::TestMiblLoad
 * Чтение длины, загруженной в Микроблейз программы. Длину спросить у Бутенкова
 */
void HrdwrNet::TestMiblLoad(int addrBFDN)
{
    int res;
    msg_t outMsg1 = msg_t();
    WrapInfMes("    Чтение регистра Мастер");
    res = ReadWithWaitFor(UCODN, addrBFDN, FPGA0, 0x61, 1, outMsg1);
    if (res){
        WrapInfMes("Ошибка чтения регистра Мастер");  return; }
    quint16 rgSlave = outMsg1.data[0];
    emit ErrorSig(QString("    RgMaster(0x61) = 0x%1").arg(rgSlave,4,16,QChar('0')));
    int nerr;
    int nlin;
    nerr = ((rgSlave & SlaveFlg) & 0x0000E000UL) >> 13;
    nlin = (rgSlave & SlaveFlg) & 0x00001FFFUL;
    emit ErrorSig(QString("    Количество строк = 0x%1").arg(nlin,4,16,QChar('0')));
    emit ErrorSig(QString("    Код ошибки = 0x%1").arg(nerr,4,16,QChar('0')));
}
/**
 * @brief HrdwrNet::StartMibl
 * "Рукоотжатие" и подача старта для Микроблейз
 */
void HrdwrNet::StartMibl(int addrBFDN)
{
    int res;
    msg_t outMsg = msg_t();
    WrapInfMes("    Отжатие");
    QList <quint16> Addr61 = {0xAA00, 0x0000};
    res = WriteWithWaitFor(UCODN, addrBFDN, FPGA0, 0x61,  Addr61, outMsg);
    if (res){
        WrapInfMes("Ошибка отжатия");  return; }

    WrapInfMes("    Старт MiBl по ключу");
    Addr61 = {0xBAA0, 0x00BB};
    res = WriteWithWaitFor(UCODN, addrBFDN, FPGA0, 0x61,  Addr61, outMsg);
    if (res){
        WrapInfMes("Ошибка старта MiBl");  return; }
}
/**
 * @brief HrdwrNet::StartTestBFDN7
 * Установка мультиплексора Ловушки БФДН
 * Подача сброса в регистр 0х53
 * Установка времени старта ГТС, Тсек, Тндн
 */
void HrdwrNet::StartTestBFDN7()
{
    int res;
    msg_t outMsg = msg_t();
    quint16 dataMux;
    for(quint16 i = 1; i < 7; i++){
        //if (i == 1) dataMux = 0x0150;
        if (i < 3) dataMux = 0x0150;
        else dataMux = 0x0170;
        WrapInfMes("Установка мультиплексора КРП 0x52");
        if (TrapsPar.in)
            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x52,  0, outMsg);// для входного сигнала
        else
            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x52,  dataMux, outMsg); // для результата
        if (res){
            WrapInfMes("Ошибка установк мультиплексора КРП 0x52");  return; }
    }
    StartGTS_BFDN();
    QThread::msleep(5500);
    WrapInfMes("    Результат в ловушке");
}
/**
 * @brief HrdwrNet::StartGTS_BFDN
 * @return 0 - ок -1 - неок
 * Установка времени старта ГТС, Тсек, Ттрап, Тндн
 */
int HrdwrNet::StartGTS_BFDN()
{
    WrapInfMes("Загрузка времени Tgts, Tsek, Ttrap, Tndn");
    msg_t outMsg1 = msg_t();
    msg_t outMsg2 = msg_t();
    int res;
    int del = 0x1388;
    res = ReadWithWaitFor(UCODN, BFDN11, FPGA0, TimeReg, 3, outMsg1);
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
    WriteWithWaitFor(l1::UKR, nUKR, l3UKR::BC, 0xE4, outMsg1.data, outMsg2);
    QList<quint16> Tsek, Tndn;
    Tsek.append(outMsg1.data);
//    Tsek[0] += 0xA1; // для сдвига в 300 данных
    Tsek[0] += 0xC; // для сдвига в 0 данных//////////////////////////////////////////////////////////////////////////////////////
    Tndn.append(Tsek);
    Tndn[0] += 0x129;
    for(quint16 i = 1; i < 7; i++){
        res = WriteWithWaitFor(UCODN, BFDN11, i, 0x53, 0x20, outMsg2);
        if (res){
            WrapInfMes("Ошибка сброса Tsek");  return -1; }
        res = WriteWithWaitFor(UCODN, BFDN11, i, 0x21, Tsek, outMsg2);
        if (res){
            WrapInfMes("Ошибка записи времени Tсек");  return -1; }
        QList<quint16> Ttrap;
        Ttrap.append(Tsek);
         if (i < 3){
        //if (i == 1){
            if (TrapsPar.in)
                Ttrap[0] += 0x0;
            else
                Ttrap[0] += 0x1AA;
        }
        else
            Ttrap[0] += 0x22A;
        //    outMsg1.data[0] += 0x1AA; //для сумматора 14 АЕ
        res = WriteWithWaitFor(UCODN, BFDN11, i, 0x51, Ttrap, outMsg2);
        if (res){
            WrapInfMes("Ошибка записи времени Ttrap");  return -1; }
        res = WriteWithWaitFor(UCODN, BFDN11, i, 0x31, Tndn, outMsg2);
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
int HrdwrNet::ReadFromTramBFDN()
{
    int res;
    bool ok;
    msg_t outMsg = msg_t();
    // Номер КРП
//    for(quint16 i = 1; i < 2; i++){
        sigCh1.clear();
        WrapInfMes("Сброс 0x53");
        res = WriteWithWaitFor(UCODN, BFDN11, TrapsPar.numFPGA, 0x53,  0x0002, outMsg);
        if (res){
            WrapInfMes("Ошибка сброса 0x53");  return -1; }
        QFile file1(QString("./HwSignals/BFDNTrapFPGA%1").arg(TrapsPar.numFPGA));
        QTextStream stream(&file1);
        stream.setCodec("UTF-8");
        file1.open(QIODevice::WriteOnly | QIODevice::Text);
        QString str;
        msg_t msg;
        WrapInfMes("Чтение ловушки");
        res = ReadWithWaitFor(UCODN, BFDN11, TrapsPar.numFPGA, 0x50,  1536, msg);
        if (res){
            WrapInfMes("Ошибка чтения ловушки");  return -1; }
        for(int i = 0; i < 512; i++) //(1536/3)
        {
            str = QString("%1%2%3 \n").
                    arg((msg.data[i*3+2]) & 0xF , 1,16,QChar('0')).
                    arg(msg.data[i*3+1],4,16,QChar('0')).
                    arg(msg.data[i*3],4,16,QChar('0'));
            stream << str;
            sigCh1.append(str.toULong(&ok,16));
        }

        WrapInfMes("Чтение ловушки");
        res = ReadWithWaitFor(UCODN, BFDN11, TrapsPar.numFPGA, 0x50,  1536, msg);
        if (res){
            WrapInfMes("Ошибка чтения ловушки");  return -1; }
        for(int i = 0; i < 512; i++) //(1536/3)
        {
            str = QString("%1%2%3 \n").
                    arg((msg.data[i*3+2]) & 0xF , 1,16,QChar('0')).
                    arg(msg.data[i*3+1],4,16,QChar('0')).
                    arg(msg.data[i*3],4,16,QChar('0'));
            stream << str;
            sigCh1.append(str.toULong(&ok,16));
        }
        file1.close();
//        res = CompareRes(1);
  //  }
    return 0;
}
/**
 * @brief HrdwrNet::CompareRes
 * сравнение результатов работы Стенда с эталонными данными
 * @return 0 - данные равны; -1 - данные не равны
 */
int HrdwrNet::CompareRes(int numTrap, int numTest)
{
    int i;
    if (sigCh1.length() == 0) {
        emit ErrorSig("Сигнал из вычислительного блока нулевой длины!");
        return -1;
    }
    //для DD3 BFDN2
    if (numTrap == 3){
        if (TrapsPar.shift == 0)
            if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_0/data_out/DN_vh_S7_17", sigCh1, etCh1)) return -1;
        if (TrapsPar.shift == 1)
            if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_1/data_out/DN_vh_S7_17", sigCh1, etCh1)) return -1;
        if (TrapsPar.shift == 2)
            if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_2/data_out/DN_vh_S7_17", sigCh1, etCh1)) return -1;
        if (TrapsPar.shift == 3)
            if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_3/data_out/DN_vh_S7_17", sigCh1, etCh1)) return -1;
    }
    //для BRUS
    if (numTrap == 4 || numTrap == 5 || numTrap == 6){
        bool fl;
        int lenComp;
        QString fileName;
        if (vertOpticIn && horOpticIn) lenComp  = sigCh1.length();
        else lenComp = sigCh1.length() / 2;
        for (int j = 2; j < 3; j++)
        {
            if (numTrap == 4){
                fileName = TestFolder + QString("/Shift_%1/data_out/DN_vh_S7_17").arg(j);
            }
            else if (numTrap == 5)
                fileName = TestFolder + QString("/Shift_%1/CM/Corr_Matrix_Vert_AE1_182_S7_BRUS").arg(j);
            fl = 1;
            if (LoadEtalonFile(fileName, sigCh1, etCh1)) return -1;
            for (i = 0 ; i< lenComp; i++)
            {
                if(vertOpticIn && horOpticIn){
                    if (sigCh1.at(i) != etCh1.at(i)){
                        emit ErrorSig(QString("_______________________________________________"));
                        emit ErrorSig(QString("Прочитанный сигнал не равен эталону!"));
                        emit ErrorSig(QString("%1: Эталон = 0x%2, Имитатор = 0x%3.").arg(i).arg(etCh1[i],9,16,QChar('0')).arg(sigCh1.at(i),9,16,QChar('0')));
                        etCh1.clear();
                        fl = 0;
                        break;
                    }
                }
                else if(vertOpticIn) {
                    if (sigCh1.at(i*2) != etCh1.at(i*2)){
                        etCh1.clear();
                        fl = 0;
                        break;
                    }
                }
                else if(horOpticIn)
                    if (sigCh1.at(i * 2 + 1) != etCh1.at(i * 2 + 1)){
                        etCh1.clear();
                        fl = 0;
                        break;
                    }
            }
//            if (numTest == 3) {fl =1; i = 5120;}
            if (!fl) {
                etCh1.clear();
                continue;
            }
            emit ErrorSig(QString("_______________________________________________"));
            emit ErrorSig(QString("Данных для сравнения %1").arg(i));
            emit ErrorSig(QString("Прочитанный сигнал равен эталону."));
            if (j != 2) {
                emit ErrorSig(QString("Сдвиг данных не 2!!!"));
                return -1;
            }
            else
                WrapInfMes(QString("Сдвиг данных %1").arg(j));
            etCh1.clear();
            emit ErrorSig(QString("_______________________________________________"));
            return 0;
        }
        if (!fl){
            emit ErrorSig(QString("Данне не соответствуют эталону!"));
            emit ErrorSig(QString("_______________________________________________"));
            return -1;
        }
    }
    else
    {
        if (TrapsPar.in){
            if (TrapsPar.shift == 0){
                if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_0/data_in", sigCh1, etCh1)) return -1;}
            if (TrapsPar.shift == 1){
                if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_1/data_in", sigCh1, etCh1)) return -1;}
            if (TrapsPar.shift == 2){
                if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_2/data_in", sigCh1, etCh1)) return -1;}
            if (TrapsPar.shift == 3){
                if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_3/data_in", sigCh1, etCh1)) return -1;}
        }
        else {
            if (testA){
                if (TrapsPar.shift == 0)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_0/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
                if (TrapsPar.shift == 1)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_1/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
                if (TrapsPar.shift == 2)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_2/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
                if (TrapsPar.shift == 3)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_3_07092020/Shift_3/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
            }
            else {
                if (TrapsPar.shift == 0)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_0/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
                if (TrapsPar.shift == 1)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_1/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
                if (TrapsPar.shift == 2)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_2/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
                if (TrapsPar.shift == 3)
                    if (LoadEtalonFile("./Data_model/14AE/Test2_CL_4_4_UKR_1_2_07092020/Shift_3/Spectr_Sum/SpSum_vh_S7_8", sigCh1, etCh1)) return -1;
            }
        }
    }

    for (i = 0 ; i< sigCh1.length(); i++)
    {
        if (sigCh1.at(i) != etCh1.at(i)){
            emit ErrorSig(QString("Прочитанный сигнал не равен эталону!"));
            emit ErrorSig(QString("%1: Эталон = 0x%2, Имитатор = 0x%3.").arg(i).arg(etCh1[i],9,16,QChar('0')).arg(sigCh1.at(i),9,16,QChar('0')));
            etCh1.clear();
            sigCh1.clear();
            return -1;
        }
    }
    emit ErrorSig(QString("Данных для сравнения %1").arg(i));
    emit ErrorSig(QString("Прочитанный сигнал равен эталону. "));
    etCh1.clear();
    sigCh1.clear();
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
int HrdwrNet::LoadEtalonFile(QString fileStr, QList<ulong> sigl, QList<ulong> &ch)
{
    bool ok;
    QFile etFile(fileStr);
    if (!etFile.open(QIODevice::ReadOnly | QIODevice::Text)){
       emit ErrorSig("Ошибка открытия файла с эталонными результатами"); return -1;}
    QTextStream tStream(&etFile);
    QString str;
    int lenF = sigl.length();
    int lengthTetr;
    // Входные данные длиной 32 бит, выходные 36 бит
    if (TrapsPar.in) lengthTetr = 8;
    else lengthTetr = 9;
    for (int i = 0; i < lenF; i++) {
        str = tStream.readLine();
        ch.append(str.mid(0, lengthTetr).toULong(&ok, 16));
    }
    return 0;
}
/**
 * @brief HrdwrNet::LoadMiBl
 * Отправка по TCP программы Микроблейз, ожидание ответа
 */
int HrdwrNet::LoadMiBl(QString fileName, int addrBFDN)
{
    //Блок для передачи формируется аналогично тому, как это делается на сервере.
    //Поскольку заранее размер блока неизвестен (параметр string может быть любой длины),
    //вначале создаём объект array класса QByteArray.
    QByteArray arrayBlock;
    arrayBlock.clear();
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QByteArray packetC21;//Переменная для хранения передаваемой метки сообщения С21.
    packetC21.clear();
    packetC21.append(QString("0x%1\n0x%2\n").arg(0x9,4,16,QChar('0')).arg(addrBFDN,4,16,QChar('0')));//Формируем метку С9 и номер БФДН
    // packetC21.
    QFile  inFile1(fileName);

    QByteArray arrayFile;
    arrayFile.clear();
    if (!inFile1.open(QIODevice::ReadOnly))
    {
        emit ErrorSig(QString("Ошибка открытия файла " + fileName));
        return -1;
    }
    arrayFile = inFile1.readAll();
    arrayFile.prepend(packetC21);
    inFile1.close();

    out<< quint64(0) << arrayFile;
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени.

    msg_t outMsg = msg_t();
    ReadFromSocket(outMsg, 2, 30000);
    return 0;
}
/**
 * @brief HrdwrNet::LoadW
 * Отправка по TCP коэффициентов W, ожидание ответа. Разбор коэффициентов на блоки памяти выполняет Сервер.
 */
int HrdwrNet::LoadW()
{
    //Блок для передачи формируется аналогично тому, как это делается на сервере.
    //Поскольку заранее размер блока неизвестен (параметр string может быть любой длины),
    //вначале создаём объект array класса QByteArray.
    QByteArray arrayBlock;
    arrayBlock.clear();
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);
    QByteArray packetC21;//Переменная для хранения передаваемой метки сообщения С21.
    packetC21.clear();
    packetC21.append(QString("0x%1\n").arg(0x21,4,16,QChar('0')));//Формируем метку С21 для передачи по TCP от клиента к серверу.
    // packetC21.    
    QByteArray arrayFile;

    LoadWFromFiles(&arrayFile);

    arrayFile.prepend(packetC21);
    out<< quint64(0) << arrayFile;
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени.
    msg_t outMsg = msg_t();
    ReadFromSocket(outMsg, 2, 30000);
    arrayFile.clear();
    return 0;
}

int HrdwrNet::LoadWFromFiles(QByteArray* arrayFile)
{
    QString fileStr1 = WFileName + QString("Wvh_CL_4_22");
    QFile  inFile1(fileStr1);
    if (!inFile1.open(QIODevice::ReadOnly)) {
        emit ErrorSig(QString("Ошибка открытия файла: " + fileStr1));
        return -1;
    }
    QByteArray qBaFile1 = inFile1.readAll();
    inFile1.close();

    QString fileStr2 = WFileName + QString("/Wvh_CL_22_22");
    QFile  inFile2(fileStr2);
    if (!inFile2.open(QIODevice::ReadOnly)) {
        emit ErrorSig(QString("Ошибка открытия файла: " + fileStr2));
        return -1;
    }
    QByteArray qBaFile2 = inFile2.readAll();
    inFile1.close();

    // БФДН 11 dd 1
    arrayFile->append(qBaFile1);
    //dd 2-6
    for (int i = 1; i < 6; ++i)
        arrayFile->append(qBaFile2);
    // БФДН 12 dd 1
    arrayFile->append(qBaFile1);
    //dd 2-6
    for (int i = 1; i < 6; ++i)
        arrayFile->append(qBaFile2);
    // БФДН 21 dd 2
    arrayFile->append(qBaFile2);
    int len = arrayFile->length();
    len++;
}

/**
 * @brief HrdwrNet::ResWPack
 * Сброс вычислительной части, регистра Тсек. Необходим при сбое загрузки W
 */
void HrdwrNet::ResWPack()
{
    int res;
    msg_t outMsg = msg_t();
    WrapInfMes("  Сброс Регистра T секций 0x53");
    res = WriteWithWaitFor(UCODN, BFDN11, FPGA1, 0x53,  0x0020, outMsg);
    if (res){
        WrapInfMes("  Сброс Регистра T секций 0x53");  return; }

    WrapInfMes("  Сброс Вычислительной части 0x53");
    res = WriteWithWaitFor(UCODN, BFDN11, FPGA0, 0x53,  0x0040, outMsg);
    if (res){
        WrapInfMes("  Сброс Вычислительной части 0x53");  return; }
/*
    emit ErrorSig("  Сброс адреса КРП");
    logHrd->InfCommonLog("Сброс адреса КРП");
    res = WriteWithWaitFor(UCODN, BFDN11, FPGA0, 0x53,  0x0002, outMsg);
*/}

/**
 * @brief HrdwrNet::RemoveTrash
 * удаляет невалидный сигнал, приходящий в БРУС
 * @param ch
 */
void HrdwrNet::RemoveTrash(QList<ulong> *ch)
{
    int packLength = 265;
    QList<ulong> packList;
    for(int i = 0; i < ch->length() / packLength; i++)
    {
        for(int j = 0; j < packLength; j++)
        {
            if ((j > 7) && (j < (packLength - 1) && ((i * packLength) + j < ch->length())))
                packList.append(ch->at((i * packLength) + j));
        }
    }
    ch->clear();
    ch->append(packList);
}
/**
 * @brief HrdwrNet::Test_RXon
 * тестировние оптических каналов в БРУС
 * @return
 */
int HrdwrNet::Test_RXon()
{
    msg_t msg;
    int res;
    res = ReadWithWaitFor(l1::BRUS, 0, 0, 0x10, 1, msg);
    if (res){
        emit ErrorSig("Ошибка чтения RXon", res);
        return -1;
    }
    emit ErrorSig(QString("  RXon = %1").arg(msg.data[0],4,16,QChar('0')));
    return 0;
}
/**
 * @brief HrdwrNet::SetupGTS
 * Загрузка параметров ГТС.
 * @return 0-ок; -1 - неок;
 */
int HrdwrNet::SetupGTS()
{
    msg_t outMsg = msg_t();
    int res;
    int counter = 0;
    foreach (quint16 nUkr, UKRlist) {
        QList<unsigned short> inData = MakeDataList(gtsProg[counter].StartFreq);
        res = WriteWithWaitFor(l1::UKR, nUkr, l3UKR::BC, 0xE0,  inData, outMsg);
        if (res) return -1;
        inData = MakeDataList(gtsProg[counter].CoefFreq);
        res = WriteWithWaitFor(l1::UKR, nUkr, l3UKR::BC, 0xE1,  inData, outMsg);
        if (res) return -1;
        for (int i=0; i< gtsProg[counter].mac1Prog.length(); i++) {
            unsigned short nMACPf = static_cast<unsigned short>(gtsProg[counter].mac1Prog[i].nMACP);
            inData = MakeDataList(gtsProg[counter].mac1Prog[i].VPhase);
            res = WriteWithWaitFor(l1::UKR, nUkr, nMACPf, 0xE2,  inData, outMsg);
            if (res) return -1;
            inData = MakeDataList(gtsProg[counter].mac1Prog[i].HPhase);
            res = WriteWithWaitFor(l1::UKR, nUkr, nMACPf, 0xE3,  inData, outMsg);
            if (res) return -1;
        }
        counter++;
    }

/*    for (quint16 j = 1; j < nUKRSetUpGTS + 1; ++j)
    {
        QList<unsigned short> inData = MakeDataList(gtsProg.StartFreq);
        res = WriteWithWaitFor(l1::UKR, j, l3UKR::BC, 0xE0,  inData, outMsg);
        if (res) return -1;
        inData = MakeDataList(gtsProg.CoefFreq);
        res = WriteWithWaitFor(l1::UKR, j, l3UKR::BC, 0xE1,  inData, outMsg);
        if (res) return -1;

        for (int i=0; i< gtsProg.mac1Prog.length(); i++) {
            unsigned short nMACPf = static_cast<unsigned short>(gtsProg.mac1Prog[i].nMACP);

            inData = MakeDataList(gtsProg.mac1Prog[i].VPhase);
            res = WriteWithWaitFor(l1::UKR, j, nMACPf, 0xE2,  inData, outMsg);
            if (res) return -1;

            inData = MakeDataList(gtsProg.mac1Prog[i].HPhase);
            res = WriteWithWaitFor(l1::UKR, j, nMACPf, 0xE3,  inData, outMsg);
            if (res) return -1;
        }
    }
*/    return 0;
}
/**
 * @brief HrdwrNet::StartPackBFDN
 * Старт пакетов данных в МАЦП
 * @return
 */
int HrdwrNet::StartPackBFDN()
{
    msg_t outMsg1 = msg_t();
    msg_t outMsg2 = msg_t();
    msg_t outMsgTmp = msg_t();
    int res;
    int del = 0xA00;// прибавка ко времени
    // чтение пакета из БФДН11, КБМ
    res = ReadWithWaitFor(UCODN, BFDN11, FPGA0, TimeReg, 3, outMsg1);
    if (res){
        WrapInfMes("  Ошибка чтения времени из БФДН11, КБМ.");  return -1; }
    outMsgTmp = outMsg1;
    if (res) return -1;
    int time1 = outMsg1.data[1];
    // рассчет времени в соответствии с пакетированием
    if (time1 + 0xA00 < 0x10000)
        outMsg1.data[1] = (time1 & 0xff00) + del;
    else
    {
        outMsg1.data[1] = del - ((0x10000 - time1) & 0x0ff00);
        outMsg1.data[2] = outMsg1.data[2] + 1;
    }
    //    outMsg1.data[0] = 0; // обнуление младшей части
    outMsg1.data[0] = 2; // обнуление младшей части
    //запись времени в выбранный МАЦП
    //    QList <unsigned short> Addr64 = {0, 1,2};
    foreach (quint16 nUkr, UKRlist) {
        res = WriteWithWaitFor(UKR, nUkr, l3UKR::BC, 0xE8, outMsg1.data, outMsg2);
        if (res) {
            WrapInfMes(QString("Ошибка записи времени старта пакетов в МАЦП УКР %1!").arg(nUkr));
            return -1;
        }
    }
/*
    for (quint16 i = 1; i < nUKRStartPack+1; ++i) {
        res = WriteWithWaitFor(UKR, i, l3UKR::BC, 0xE8, outMsg1.data, outMsg2);
        if (res) {
            WrapInfMes(QString("Ошибка записи времени старта пакетов в МАЦП УКР %1!").arg(i));
            return -1;
        }
    }
*/    return 0;
}

GTSProg HrdwrNet::LoadGTSPars(QString fileName){

    bool ok;
    GTSProg gtsProg;
    QFile filePar(fileName);
    if (!filePar.open(QFile::ReadOnly))
    {
        WrapInfMes("Ошибка открытия файла параметров ГТС: " + fileName);
        return gtsProg;
    }
    QTextStream strT(&filePar);
    gtsProg.StartFreq = strT.readLine().toUInt(&ok, 16);
    gtsProg.CoefFreq = strT.readLine().toUInt(&ok, 16);
    int countMACP = 0;
    while(!strT.atEnd())
    {
        MAC1Prog* strprg = new MAC1Prog();
        strprg->nMACP = ++countMACP;
        strprg->VPhase = strT.readLine().toUInt(&ok, 16);
        strprg->HPhase = strT.readLine().toUInt(&ok, 16);
        gtsProg.mac1Prog.append(*strprg);
        delete strprg;
    }
    return gtsProg;
}

/**
 * @brief HrdwrNet::MakeDataList
 * хз
 * @param data
 * @return
 */
QList<unsigned short> HrdwrNet::MakeDataList(int data){
    QList<unsigned short> list;
    unsigned short tmp1 = data&0x0000FFFF;
    list.append(tmp1);
    tmp1 = static_cast<unsigned short>((data & 0xFFFF0000) >> 16);
    list.append(tmp1);
    return list;
}
/**
 * @brief HrdwrNet::OnUKR
 * Включение УКР по каналу RS
 * @return
 */
int HrdwrNet::OnUKR()
{
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QByteArray outPacketC03;
    quint16 r = 0x41;
    outPacketC03.append(QString("0x%1").arg(r,4,16,QChar('0')));
    r = 0x1;
    outPacketC03.append(QString("%1").arg(r,4,16,QChar('0')));
    out<< quint64(0)<< outPacketC03;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени С03.
}

/**
 * @brief TestTimesMibl
 * @return Тест Времени для Микроблейза
 */
int HrdwrNet::TestTimesMibl()
{
    unsigned int flagEmpty;//флаг заполненности FIFO2
    unsigned int tempWord;
    int res;
    unsigned int n=0;
    int p;
    unsigned int numbWord;
    msg_t outMsg1 = msg_t();

    WrapInfMes("Чтение регистра SlaveReg_2");
    if (ReadWithWaitFor(UCODN, BFDN11, FPGA0, SlaveReg_2, 1, outMsg1)){
        WrapInfMes("Ошибка чтения регистра SlaveReg_2");
        return -1;
    }
    flagEmpty = outMsg1.data[0] & EmptyFifoFl; // 0 - FIFO 2 пусто, 1 - заполнено
    if (!flagEmpty) {
        emit ErrorSig(QString("Пустое FIFO RSlaveReg_2 = 0x%1\n").arg(outMsg1.data[0],4,16,QChar('0')));
        return -1;
    }

    if (ReadWithWaitFor(UCODN, BFDN11, FPGA0, FIFOMibl, 2, outMsg1)){
        WrapInfMes("Ошибка чтения FIFO");
        return -1;
    }
    emit ErrorSig(QString("Количество слов в FIFO = 0x%1\n").arg(outMsg1.data[0],4,16,QChar('0')));

    QFile outFile1("MiblTimex.txt");// имя выходного файла
    // открываем файл для записи
    p = outFile1.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream1(&outFile1);//

    char buf[16];// массив для прочитанного слова из FIFO2
    int tempCountlast = 0;// счетчик для вычисления последней позиции в строке
    int tempCountfull = 0;// счетчик для вычисления всех обращений к FIFO2
    int temp11=0;//счетчик количества строк в отбивке
    outStream1 << _Out_Zag ;// записываем в выходной файл шапку для таблицы
    outStream1 << "| " ;
    while (n<numbWord) {// цикл по всем прочитанным данным
        //читаем регистр RgSlave_r
        WrapInfMes("Чтение регистра SlaveReg_2");
        if (ReadWithWaitFor(UCODN, BFDN11, FPGA0, SlaveReg_2, 1, outMsg1)){
            WrapInfMes("Ошибка чтения регистра SlaveReg_2"); return -1;}

        flagEmpty = outMsg1.data[0] & EmptyFifoFl; // 0 - FIFO 2 пусто, 1 - заполнено
        if (flagEmpty) {//поверяем FIFO2 на пустоту
            if (ReadWithWaitFor(UCODN, BFDN11, FPGA0, FIFOMibl, 2, outMsg1)){
                WrapInfMes("Ошибка чтения FIFO");
                return -1; }
            tempWord = outMsg1.data[0];
            sprintf(buf, "%04x", tempWord);//выводим прочитанное слово в массив buf в указанном формате
            if (tempCountlast > 2) {// файл состоит из 10 строк по 4 значения
                outStream1 << buf<<" | " << "\n";// переходим на новую строку
                tempCountlast=0;// обнуление счетчика для вычисления последней позиции в строке
                temp11++;// наращиваем щетчик строк
                if ((temp11!=16)&(n!=numbWord-1)){outStream1 << "| " ;}
                if (temp11 == 16){
                    outStream1 << "\n------------------\n" << "\n";// отбивка 11 строк выходного файла
                    outStream1 << _Out_Zag ;// записываем в выходной файл шапку после отбивки
                    outStream1 << "| " ;
                    temp11=0;// обнуляем щетчик строк
                }
            }
            else {
                outStream1 << buf << " | ";// данные в строке разделяются |
                tempCountlast++;// наращивание счетчика для вычисления последней позиции в строке
            }
            outStream1.flush();// сброс данных из буфера
            n++;// наращивание счетчика цикла
        }
        tempCountfull++;// наращивание счетчика обращений к FIFO2
        printf("All reading =(%d): Read word =(%d)\r",tempCountfull,n);// выводим на консоль количество обращений к FIFO2 и количество считанных данных

    }// конец цикла while
    printf("\n");
    outFile1.close();// закрытие выходного файла
    return 0;
}
/**
 * @brief HrdwrNet::WrapInfMes
 * оболочка для выводана экран и в лог
 */
void HrdwrNet::WrapInfMes(QString str)
{
    emit ErrorSig(str);
    logHrd->ErrCommonLog(str);
}

int HrdwrNet::StartZeroSig()
{
    msg_t outMsg1 = msg_t();
    msg_t outMsg2 = msg_t();
    msg_t outMsgTmp = msg_t();
    int res;
    int del = 0xA00;// прибавка ко времени
    // чтение пакета из БФДН11, КБМ
    res = ReadWithWaitFor(UCODN, BFDN11, FPGA0, TimeReg, 3, outMsg1);
    if (res){
        WrapInfMes("  Ошибка чтения времени из БФДН11, КБМ.");  return -1; }
    int startHour = QTime::currentTime().hour();
    int startMin = QTime::currentTime().minute();
    int startSec = QTime::currentTime().second();
    outMsgTmp = outMsg1;
    if (res) return -1;
    int time1 = outMsg1.data[1];
    // рассчет времени в соответствии с пакетированием
    if (time1 + 0xA00 < 0x10000)
        outMsg1.data[1] = (time1 & 0xff00) + del;
    else
    {
        outMsg1.data[1] = del - ((0x10000 - time1) & 0x0ff00);
        outMsg1.data[2] = outMsg1.data[2] + 1;
    }
    //    outMsg1.data[0] = 0; // обнуление младшей части
    outMsg1.data[0] = 0; // обнуление младшей части
    //запись времени в БФДН 12
    for (int i = 1; i < 7; ++i)
    {
        res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN11, i, 0x40, outMsg1.data, outMsg2);
        if (res) {
            WrapInfMes(QString("Ошибка записи в региста 0x40 БФДН11 ПЛИС %1!").arg(i));
            return -1;
        }
        res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN12, i, 0x40, outMsg1.data, outMsg2);
        if (res) {
            WrapInfMes(QString("Ошибка записи в региста 0x40 БФДН12 ПЛИС %1!").arg(i));
            return -1;
        }
    }
    //запись времени в БФДН 12
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA2, 0x40, outMsg1.data, outMsg2);
    if (res) {
        WrapInfMes("Ошибка записи в региста 0x40 БФДН21 ПЛИС 2!");
        return -1;
    }
    int timeForStart;
    int stopTimeHour = QTime::currentTime().hour();
    int stopTimeMin = QTime::currentTime().minute();
    int stopTimeSek = QTime::currentTime().second();
    if ((startHour < stopTimeHour) || (startMin < stopTimeMin))
        timeForStart = (del/1000) - ((stopTimeSek + 60) - startSec);
    else
        timeForStart = (del/1000) - (stopTimeSek - startSec);
    QThread::msleep((timeForStart*1000) + 2000);
    return 0;
}
