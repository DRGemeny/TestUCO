#include "hrdwrnet.h"
#include "QTcpSocket"
#include <QThread>
#include "myclient.h"
#include <QTextStream>
#include<QTime>

/**
/** * @brief HrdwrNet::CycleStart Старт задачи с повторением. (перед стартом подать сброс LVDS)
/** * @param nCycle количество повторений цикла
 * dnKm - 0 читаем из БРУСА диаграму направленности, 1 - читаем карреляционную матрицу
 * numTest - номер теста по ПМ. 0 - без номера
/** */
void HrdwrNet::CycleStart(int nCycle, int dnKm, int numTest)
{
    if (vertOpticIn == 0 && horOpticIn == 0){
        emit ErrorSig("Не выбрана Vert или Hor составляющие для сравнения"); return; }
    int res;
    if (firstStart == 1){
        res = ResLVDSBFDN2();
        if(res) return;

        WrapInfMes("Загрузка MiBl БФДН 1.2");
        ResMibl(l2UCODN::BFDN12);
        if (LoadMibl(MiBlFileName, l2UCODN::BFDN12)) return;
        TestMiblLoad(l2UCODN::BFDN12);
        StartMibl(l2UCODN::BFDN12);

        WrapInfMes("Загрузка MiBl БФДН 2.1");
        ResMibl(l2UCODN::BFDN21);
        if (LoadMibl(MiBlFileName21, l2UCODN::BFDN21)) return;
        TestMiblLoad(l2UCODN::BFDN21);
        StartMibl(l2UCODN::BFDN21);
    }
    WrapInfMes("Настройка УКР");
    res = SetupUKR();
    if(res) return;
    WrapInfMes("Старт нулевых пакетов");
    res = StartZeroSig();
    if(res) return;


    QString str = QString("%1:%2:%3.%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
            arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());

    for(int i = 0; i < nCycle; i++)
    {
        WrapInfMes("Загрузка MiBl БФДН 1.1");
        ResMibl(l2UCODN::BFDN11);
        if(LoadMibl(MiBlFileName, l2UCODN::BFDN11))return;
        TestMiblLoad(l2UCODN::BFDN11);
        StartMibl(l2UCODN::BFDN11);

        WrapInfMes("Загрузка W");
        emit SigNumCycle(i);
        if (LoadW()) return;

        WrapInfMes("Запись времени старта");
        res = StartTestBFDN2_7(dnKm, nUKR);
        if(res) return;
/*        res = ReadFromTramType1BFDN2();
        if(res) return;
*/
        if (dnKm == 0){
            res  = ReadFromTramType2BRUSDN(numTest);
            ResComputingPart();
            if(res) return;
        }
        else if (dnKm == 1){
            res  = ReadFromTramType2BRUSKM(numTest);
            ResComputingPart();
            if(res) return;
        }
    }
    QString str1 = QString("%1:%2:%3.%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
            arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
    WrapInfMes("Старт Теста " + str);
    WrapInfMes("Стоп Теста " + str1);
    WrapInfMes(QString("Тест %1 завершился успешно.").arg(numTest));
    WrapInfMes("");
}

/**
 * @brief HrdwrNet::ReadFromTramType2BFDN2
 * Чтение ловушек БФДН2 ПЛИС 1
 */
void HrdwrNet::ReadFromTramType2BFDN2()
{
    int res;
    msg_t outMsg = msg_t();
    QList <unsigned short> Addr1 = {0x0000, 0x0000};
//  QList <unsigned short> Addr2 = {0x0007, 0xF000};

    WrapInfMes("Адрес Памяти 0x1A = 0");
    res = WriteWithWaitFor(l1::BRUS, 0, 0, 0x18,  Addr1, outMsg);
    if (res){
        WrapInfMes("Ошибка установка адреса памяти 0x1A"); return ; }

    WrapInfMes("Чтение пакета из 0x1C");
 //   res = WriteToFileBFDN2(0);
    if (res) {
        WrapInfMes("Ошибка чтения данных из 0x1C!!!"); return ; }

//    WrapInfMes("Адрес Памяти 0x1A = 7f000");
//    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x1A,  Addr2, outMsg);
//    if (res){
//        WrapInfMes("Ошибка установка адреса памяти 0x7f000"); return ; }

//    WrapInfMes("Чтение пакета из 0x1C");
//    res = WriteToFileBFDN2();
//    if (res) {
//        WrapInfMes("Ошибка чтения данных из 0x1C!!!"); return ; }
    WrapInfMes("Сравнение результатов");
//   res = CompareRes(4);
    sigCh1.clear();sigCh2.clear();
    etCh1.clear(); etCh2.clear();
    if (res) return ;
//    WrapInfMes("Тест закончен успешно");
    return ;
}
/**
 * @brief HrdwrNet::ReadFromTramType2BFDN2
 * Чтение ловушек в в БРУС
 */
int HrdwrNet::ReadFromTramType2BRUSKM(int numTest)
{
    int res;
    msg_t outMsg = msg_t();
    QList <unsigned short> Addr1 = {0x0000, 0x0000};
//  QList <unsigned short> Addr2 = {0x0007, 0xF000};

//    WrapInfMes("Адрес Памяти 0x1A = 0");
    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x1D,  Addr1, outMsg);
    if (res){
        WrapInfMes("Ошибка установка адреса памяти 0x1A"); return -1; }

    WrapInfMes("Чтение пакета из 0x1C");
    res = WriteToFileBFDN2KM(1);
    if (res == -1) {
        WrapInfMes("Ошибка чтения данных из 0x1C!!!"); return -1; }

    WrapInfMes("Сравнение результатов");
    res = CompareRes(5, numTest);
    sigCh1.clear();sigCh2.clear();
    etCh1.clear(); etCh2.clear();
    if (res) return -1;
//    WrapInfMes("Тест закончен успешно");
    return 0;
}
/**
 * @brief HrdwrNet::ReadFromTramType2BFDN2
 * Чтение ловушек в в БРУС
 */
int HrdwrNet::ReadFromTramType2BRUSDN(int numTest)
{
    int res;
    msg_t outMsg = msg_t();
    QList <unsigned short> Addr1 = {0x0000, 0x0000};
//  QList <unsigned short> Addr2 = {0x0007, 0xF000};

//    WrapInfMes("Адрес Памяти 0x1A = 0");
    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x1D,  Addr1, outMsg);
    if (res){
        WrapInfMes("Ошибка установка адреса памяти 0x1A"); return -1; }

    WrapInfMes("    Чтение пакета из 0x1C");
    res = WriteToFileBFDN2DN(1);
    if (res) {
        WrapInfMes("Ошибка чтения данных из 0x1C!!!"); return -1; }

    WrapInfMes("    Сравнение результатов");
    res = CompareRes(4, numTest);
    sigCh1.clear();sigCh2.clear();
    etCh1.clear(); etCh2.clear();
    if (res) return -1;
    return 0;
}

/**
 * @brief HrdwrNet::ReadFromTramMaxBFDN
 * Чтение данных из ловушки БФДН2 ПЛИС 2.
 * Чтение выполняется строго блоками по 1536 данных. Данные 48 разрядов. (одно данное  = 3 16-ти разрядным словам)
 * @return
 */
int HrdwrNet::ReadFromTramType1BFDN2()
{
    int res;
    bool ok;
    msg_t outMsg = msg_t();
    // Номер КРП
    sigCh1.clear();
    WrapInfMes("Сброс 0x53");
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA2, 0x53,  0x0002, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса 0x53");  return -1; }
    QFile file1(QString("./HwSignals/BFDN2TrapFPGA%1").arg(TrapsPar.numFPGA));
    QTextStream stream(&file1);
    stream.setCodec("UTF-8");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str, str1;
    msg_t msg;
    for (int j = 0; j < 8; j++)
    {
        WrapInfMes("Чтение ловушки");
        res = ReadWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA2, 0x50,  1536, msg);
        if (res){
            WrapInfMes("Ошибка чтения ловушки");  return -1; }
        for(int i = 0; i < 512; i++) //(1536/3)
        {
            str = QString("%1%2%3,\n").
                    arg((msg.data[i*3+2]) & 0xF , 1,16,QChar('0')).
                    arg(msg.data[i*3+1],4,16,QChar('0')).
                    arg(msg.data[i*3],4,16,QChar('0')).toUpper();
            stream << str;
            str.chop(2);
            sigCh1.append(str.toULong(&ok,16));
        }
    }
    file1.close();
    res = CompareRes(4, 5);
    return 0;
}
/**
 * @brief HrdwrNet::ReadFromTramMaxBFDN
 * Чтение данных из ловушки БФДН2 ПЛИС 3.
 * Чтение выполняется строго блоками по 1536 данных. Данные 48 разрядов. (одно данное  = 3 16-ти разрядным словам)
 * @return
 */
int HrdwrNet::ReadFromTramType3BFDN2()
{
    int res;
    bool ok;
    msg_t outMsg = msg_t();
    // Номер КРП
    sigCh1.clear();
    WrapInfMes("Сброс 0x53");
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA3, 0x53,  0x0002, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса 0x53");  return -1; }
    QFile file1(QString("./HwSignals/BFDN2FPGA%1").arg(3));
    QTextStream stream(&file1);
    stream.setCodec("UTF-8");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str;
    msg_t msg;
    for (int j = 0; j<10; j++){
        WrapInfMes("Чтение ловушки");
        res = ReadWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA3, 0x50,  1536, msg);
        if (res){
            WrapInfMes("Ошибка чтения ловушки");  return -1; }
        for(int i = 0; i < 512; i++) //(1536/3)
        {
            str = QString("%1%2\n").
                    //arg((msg.data[i*3+2]) & 0xF , 1,16,QChar('0')).toUpper().
                    arg(msg.data[i*3+1],4,16,QChar('0')).toUpper().
                    arg(msg.data[i*3],4,16,QChar('0')).toUpper();
            stream << str;
            sigCh1.append(str.toULong(&ok,16));
        }
    }
    file1.close();
//    res = CompareRes(3);
    return 0;
}
/**
 * @brief HrdwrNet::StartTestBFDN2_7
 * настройка ловушек во всех БФДН и запуск ловушек по времени (StartGTS_BFDN2)
 */
int HrdwrNet::StartTestBFDN2_7(int dnKm, quint16 nUKRStart)
{
    int res;
    msg_t outMsg = msg_t();
    int timeForStart;
    QList <unsigned short> Addr1 = {0x0000, 0x0000};
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA2, 0x52,  0x170, outMsg);
    if (res){
        WrapInfMes("Ошибка установк мультиплексора КРП2 0x52 в БФДН21");  return -1; }
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA3, 0x52,  0x150, outMsg);
    if (res){
        WrapInfMes("Ошибка установк мультиплексора КРП3 0x52 в БФДН21");  return -1; }
    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x19, 0, outMsg);
    if (res){
        WrapInfMes("Ошибка переключения мультиплексора 19.");    return -1;}
    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x1D,  Addr1, outMsg);
    if (res){
        WrapInfMes("Ошибка установка адреса памяти 0x1A"); return -1; }
    //    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA2, 0x52,  0, outMsg);// для входного сигнала

    res = StartGTS_BFDN2(dnKm, timeForStart);
    if (res) return -1;
    QThread::msleep((timeForStart*1000) + 2000);
    WrapInfMes("    Результат в ловушке");
    return 0;
}

/**
 * @brief HrdwrNet::StartGTS_BFDN2
 * @return 0 - ок -1 - неок
 * Установка времени старта ГТС, Тсек, Ттрап, Тндн, TtrapBFDN2
 */
int HrdwrNet::StartGTS_BFDN2(int dnKm, int& timeForStart)
{
    WrapInfMes("    Загрузка времени Tgts, Tsek, Ttrap, Tndn");
    msg_t outMsg1 = msg_t();
    msg_t outMsg2 = msg_t();
    QList<quint16> Tsek, Tkm, TkmMibl, Tndn, TtrapBRUS2, TtrapBFDN2T2, TtrapBFDN2T3, TtekMibl;
    QList<quint16> TtrapBFDN2;
    int res;
    int del = 0x1f40; //8сек
//    int del = 0x1388; //5сек
//    int del = 0x9c4;
//    int del = 0x4E2;
    res = ReadWithWaitFor(UCODN, BFDN11, FPGA0, TimeReg, 3, outMsg1);
    if (res){
        WrapInfMes("Ошибка чтения времени из DD0 БФДН11");  return -1; }

//    QString str = QString("%1:%2:%3.%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
  //          arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
    int startHour = QTime::currentTime().hour();
    int startMin = QTime::currentTime().minute();
    int startSec = QTime::currentTime().second();

    int time1 = outMsg1.data[1];
    if (time1 + del < 0x10000)
        outMsg1.data[1] = (time1 & 0xff00) + del;
    else
    {
        outMsg1.data[1] = del - ((0x10000 - time1) & 0x0ff00);
        outMsg1.data[2] = outMsg1.data[2] + 1;
    }
    TtekMibl.append(outMsg1.data[2]);
    TtekMibl.append(outMsg1.data[1]);
    TtekMibl.append(0);
    TtekMibl.append(outMsg1.data[0]);

    //outMsg1.data[0] = 0;
    outMsg1.data[0] = 0x2;
    // старт ГТС
    foreach (int nUkr, UKRlist) {
        res = WriteWithWaitFor(l1::UKR, nUkr, l3UKR::BC, 0xE4, outMsg1.data, outMsg2);
        if (res){
            WrapInfMes("Ошибка старта GTS");  return -1; }
    }

//        res = WriteWithWaitFor(l1::UKR, 1, l3UKR::BC, 0xE4, outMsg1.data, outMsg2);
//        if (res){
//            WrapInfMes("Ошибка чтения времени из DD0 БФДН11");  return -1; }
    Tsek.append(outMsg1.data);
    Tsek[0] += 0xA;
    Tndn.append(Tsek);
    Tndn[0] += 0x129;

    int nsek = 0; // номер секции для захвата
    Tkm.append(Tsek);
    Tkm[0] += 0x1A4 + (0x80 * nsek);// время захвата первой секции для КМ n*0x80 - прибавка для чтения n-той секции
    TkmMibl.append(Tkm[2]);
    TkmMibl.append(Tkm[1]);
    TkmMibl.append(0);
    TkmMibl.append(Tkm[0] + 0x100);

    for(quint16 i = 1; i < 7; i++){
        QList<quint16> Ttrap;
        Ttrap.append(Tsek);
            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x53, 0x20, outMsg2);
            if (res){
                WrapInfMes("Ошибка сброса Tsek");  return -1; }
            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x21, Tsek, outMsg2);
            if (res){
                WrapInfMes("Ошибка записи времени Tсек");  return -1; }
            //if (i == 1){
            if (TrapsPar.in)
                Ttrap[0] += 0x0;
            else
                Ttrap[0] += 0x1AA;
            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x31, Tndn, outMsg2);
            if (res){
                WrapInfMes("Ошибка записи времени Tндн");  return -1; }
            Ttrap[0] += 0x22A;
    }
    for(quint16 i = 1; i < 7; i++){
            res = WriteWithWaitFor(UCODN, BFDN12, i, 0x53, 0x20, outMsg2);
            if (res){
                WrapInfMes("Ошибка сброса Tsek");  return -1; }
            res = WriteWithWaitFor(UCODN, BFDN12, i, 0x21, Tsek, outMsg2);
            if (res){
                WrapInfMes("Ошибка записи времени Tсек");  return -1; }
            res = WriteWithWaitFor(UCODN, BFDN12, i, 0x31, Tndn, outMsg2);
            if (res){
            WrapInfMes("Ошибка записи времени Tндн");  return -1; }
    }

    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN11, FPGA1, 0x22, Tkm, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени Tkm BFDN21, FPGA2");  return -1; }
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN11, FPGA5, 0x22, Tkm, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени Tkm BFDN21, FPGA2");  return -1; }
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN12, FPGA1, 0x22, Tkm, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени Tkm BFDN21, FPGA2");  return -1; }
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN12, FPGA5, 0x22, Tkm, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени Tkm BFDN21, FPGA2");  return -1; }

    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN11, FPGA0, 0x60, TkmMibl, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени TkmMibl в Microblaze");  return -1; }
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN11, FPGA0, 0x60, TtekMibl, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени TkmMibl в Microblaze");  return -1; }
    QList<quint16> flMibl = {0xCFF0, 0x00CC};
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN11, FPGA0, 0x61, flMibl, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени TkmMibl в Microblaze");  return -1; }


    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA2, 0x53, 0x20, outMsg2);
    if (res){
        WrapInfMes("Ошибка сброса Tsek BFDN21, FPGA2");  return -1; }
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA2, 0x21, Tsek, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени Tсек BFDN21, FPGA2");  return -1; }

//    for (int i = 0x31; i < 0x39; i++)
//    {
        res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA2, 0x31, Tndn, outMsg2);
        if (res){
            WrapInfMes("Ошибка записи времени Tндн");  return -1; }
//    }

    if (dnKm == 0) {
        TtrapBRUS2.append(Tsek);
        TtrapBRUS2[0] += 0x350;
//        TtrapBRUS2[0] += 0x250; //для ДН было для DOS-M
    }
    else if (dnKm == 1){
        TtrapBRUS2.append(Tkm);
        TtrapBRUS2[0] += 0x540; //для КМ
    }
    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x1E, TtrapBRUS2, outMsg2);
    if (res){
        WrapInfMes("Ошибка записи времени в БРУС");  return -1; }

//    QString str1 = QString("%1:%2:%3.%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
  //          arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
//    WrapInfMes("Старт " + str);
  //  WrapInfMes("Стоп " + str1);
    int stopTimeHour = QTime::currentTime().hour();
    int stopTimeMin = QTime::currentTime().minute();
    int stopTimeSek = QTime::currentTime().second();
    if ((startHour < stopTimeHour) || (startMin < stopTimeMin))
        timeForStart = (del/1000) - ((stopTimeSek + 60) - startSec);
    else
        timeForStart = (del/1000) - (stopTimeSek - startSec);
    //WrapInfMes(QString("Время на запись ""стартов"" %1").arg(timeForStart));
    return 0;
}

///**
// * @brief HrdwrNet::StartGTS_BFDN2
// * @return 0 - ок -1 - неок
// * Установка времени старта ГТС, Тсек, Ттрап, Тндн, TtrapBFDN2
// */
//int HrdwrNet::StartGTS_BFDN2(int dnKm, int& timeForStart)
//{
//    WrapInfMes("    Загрузка времени Tgts, Tsek, Ttrap, Tndn");
//    msg_t outMsg1 = msg_t();
//    msg_t outMsg2 = msg_t();
//    QList<quint16> Tsek, Tkm, TkmMibl, Tndn, TtrapBRUS2, TtrapBFDN2T2, TtrapBFDN2T3, TtekMibl;
//    QList<quint16> TtrapBFDN2;
//    int res;
//    int del = 0x1f40; //8сек
////    int del = 0x1388; //5сек
////    int del = 0x9c4;
////    int del = 0x4E2;
//    res = ReadWithWaitFor(UCODN, BFDN11, FPGA0, TimeReg, 3, outMsg1);
//    if (res){
//        WrapInfMes("Ошибка чтения времени из DD0 БФДН11");  return -1; }

////    QString str = QString("%1:%2:%3.%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
//  //          arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
//    int startHour = QTime::currentTime().hour();
//    int startMin = QTime::currentTime().minute();
//    int startSec = QTime::currentTime().second();

//    int time1 = outMsg1.data[1];
//    if (time1 + del < 0x10000)
//        outMsg1.data[1] = (time1 & 0xff00) + del;
//    else
//    {
//        outMsg1.data[1] = del - ((0x10000 - time1) & 0x0ff00);
//        outMsg1.data[2] = outMsg1.data[2] + 1;
//    }
//    TtekMibl.append(outMsg1.data[2]);
//    TtekMibl.append(outMsg1.data[1]);
//    TtekMibl.append(0);
//    TtekMibl.append(outMsg1.data[0]);

//    //outMsg1.data[0] = 0;
//    outMsg1.data[0] = 0x2;
//    // старт ГТС
//    foreach (int nUkr, UKRlist) {
//        res = WriteWithWaitFor(l1::UKR, nUkr, l3UKR::BC, 0xE4, outMsg1.data, outMsg2);
//        if (res){
//            WrapInfMes("Ошибка старта GTS");  return -1; }
//    }

////        res = WriteWithWaitFor(l1::UKR, 1, l3UKR::BC, 0xE4, outMsg1.data, outMsg2);
////        if (res){
////            WrapInfMes("Ошибка чтения времени из DD0 БФДН11");  return -1; }
//    Tsek.append(outMsg1.data);
//    Tsek[0] += 0xA;
//    Tndn.append(Tsek);
//    Tndn[0] += 0x129;
//    for(quint16 i = 1; i < 7; i++){
//        QList<quint16> Ttrap;
//        Ttrap.append(Tsek);
//            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x53, 0x20, outMsg2);
//            if (res){
//                WrapInfMes("Ошибка сброса Tsek");  return -1; }
//            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x21, Tsek, outMsg2);
//            if (res){
//                WrapInfMes("Ошибка записи времени Tсек");  return -1; }
//            //if (i == 1){
//            if (TrapsPar.in)
//                Ttrap[0] += 0x0;
//            else
//                Ttrap[0] += 0x1AA;
//            res = WriteWithWaitFor(UCODN, BFDN11, i, 0x31, Tndn, outMsg2);
//            if (res){
//                WrapInfMes("Ошибка записи времени Tндн");  return -1; }
//            Ttrap[0] += 0x22A;
//    }
//    for(quint16 i = 1; i < 7; i++){
//            res = WriteWithWaitFor(UCODN, BFDN12, i, 0x53, 0x20, outMsg2);
//            if (res){
//                WrapInfMes("Ошибка сброса Tsek");  return -1; }
//            res = WriteWithWaitFor(UCODN, BFDN12, i, 0x21, Tsek, outMsg2);
//            if (res){
//                WrapInfMes("Ошибка записи времени Tсек");  return -1; }
//            res = WriteWithWaitFor(UCODN, BFDN12, i, 0x31, Tndn, outMsg2);
//            if (res){
//            WrapInfMes("Ошибка записи времени Tндн");  return -1; }
//    }

//    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA2, 0x53, 0x20, outMsg2);
//    if (res){
//        WrapInfMes("Ошибка сброса Tsek BFDN21, FPGA2");  return -1; }
//    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA2, 0x21, Tsek, outMsg2);
//    if (res){
//        WrapInfMes("Ошибка записи времени Tсек BFDN21, FPGA2");  return -1; }

////    for (int i = 0x31; i < 0x39; i++)
////    {
//        res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA2, 0x31, Tndn, outMsg2);
//        if (res){
//            WrapInfMes("Ошибка записи времени Tндн");  return -1; }
////    }

//    if (dnKm == 0) {
//        TtrapBRUS2.append(Tsek);
//        TtrapBRUS2[0] += 0x350;
////        TtrapBRUS2[0] += 0x250; //для ДН было для DOS-M
//    }
//    else if (dnKm == 1){
//        TtrapBRUS2.append(Tkm);
//        TtrapBRUS2[0] += 0x500; //для КМ
//    }
//    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x1E, TtrapBRUS2, outMsg2);
//    if (res){
//        WrapInfMes("Ошибка записи времени в БРУС");  return -1; }

////    QString str1 = QString("%1:%2:%3.%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
//  //          arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
////    WrapInfMes("Старт " + str);
//  //  WrapInfMes("Стоп " + str1);
//    int stopTimeHour = QTime::currentTime().hour();
//    int stopTimeMin = QTime::currentTime().minute();
//    int stopTimeSek = QTime::currentTime().second();
//    if ((startHour < stopTimeHour) || (startMin < stopTimeMin))
//        timeForStart = (del/1000) - ((stopTimeSek + 60) - startSec);
//    else
//        timeForStart = (del/1000) - (stopTimeSek - startSec);
//    //WrapInfMes(QString("Время на запись ""стартов"" %1").arg(timeForStart));
//    return 0;
//}

/**
 * @brief HrdwrNet::TestBFDN2
 * тестирование БФДН2, когда сигнал из ДД7 БФДН1 подается БФДН2.
 * Эталоном для сравнения является счетчик га 256
 * @return
*/
int HrdwrNet::TestBFDN2()
{
    int res;
    msg_t outMsg = msg_t();
    QList <unsigned short> Addr1 = {0x0000, 0x0000};

    WrapInfMes("Мультиплексор 0x19 = 0");
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x19, 0 , outMsg);
    if (res){
        WrapInfMes("Ошибка переключения мультиплексора 19."); return -1; }

   WrapInfMes("Адрес Памяти 0x1A = 0");
   res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x1A,  Addr1, outMsg);
   if (res){
       WrapInfMes("Ошибка установка адреса памяти 0x1A"); return -1; }

   WrapInfMes("Старт памяти");
   res = StartMemBFDN2();
   if (res){
       WrapInfMes("Ошибка записи времени в память"); return -1;}
   QThread::msleep(7000);

   WrapInfMes("Адрес Памяти 0x1A = 0");
   res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x1A,  Addr1, outMsg);
   if (res){
       WrapInfMes("Ошибка установка адреса памяти 0x1A"); return -1; }

   WrapInfMes("Чтение пакета из 0x1C");
//   res = WriteToFileBFDN2(0);
   if (res) {
       WrapInfMes("Ошибка чтения данных из 0x1C!!!"); return -1; }

   WrapInfMes("Сравнение результатов");
   res = CompareResBFDN2();
   sigCh1.clear();sigCh2.clear();
   etCh1.clear(); etCh2.clear();
   if (res) return -1;
   WrapInfMes("Тест закончен успешно");
   return 0;
}


int HrdwrNet::StartMemBFDN2()
{
    msg_t outMsg1 = msg_t();
    msg_t outMsg2 = msg_t();
    int res;
    int del = 0x1500;
    res = ReadWithWaitFor(UCODN, BFDN11, FPGA0, TimeReg, 3, outMsg1);
//    res = ReadWithWaitFor(l1::BRUS, 0, 0, TimeReg, 3, outMsg1);
    if (res) return -1;
    int time1 = outMsg1.data[1];
    if (time1 + 0x1500 < 0x10000)
        outMsg1.data[1] = (time1 & 0xff00) + del;
    else
    {
        outMsg1.data[1] = del - ((0x10000 - time1) & 0x0ff00);
        outMsg1.data[2] = outMsg1.data[2] + 1;
    }
    outMsg1.data[0] = 0;
    // Старт Мем
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x1B, outMsg1.data, outMsg2);
    if (res) return -1;
    return 0;
}

int HrdwrNet::WriteToFileBFDN2KM(int BRUSBFDN)
{
    int res;
    int globNum = 0;
    bool ok;
    QString str1 = "SigBFDN2.txt";
    int sigLenFormHrd = 25088;

    if (BRUSBFDN == 0) str1 = "SigBFDN2.txt";
    else str1 = "SigBRUS.txt";

    QFile file1(str1);
    QTextStream stream(&file1);
    stream.setCodec("UTF-8");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str;

    QString str2 = "SigBRUS_light.txt";
    QFile file2(str2);
    QTextStream stream2(&file2);
    stream2.setCodec("UTF-8");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str_light;
    int sigCount = 0;

//    int dataNum = 1998;
    int dataNum = 999;
    for(int j = 0; j < 247; j++)
//    for(int j = 0; j < 227; j++)
    {
        msg_t msg;
        if (BRUSBFDN == 0)
            res = ReadWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x1C,  dataNum, msg);
        else
            res = ReadWithWaitForSoc2(l1::BRUS, 0, 0, 0x1F,  dataNum, msg);
        if (res) {
            WrapInfMes(QString("Ошибка чтения памяти!!! Итерация %1").arg(j));
            return -1;
        }
        for(int i = 0; i < dataNum/3; i++) //(999/3)
        {
            globNum = j * (dataNum/3) + i;
            str = QString("%4: 0x%1 %2 %3 \n").arg(
                    msg.data[i*3+2],4,16,QChar('0')).
                    arg(msg.data[i*3+1],4,16,QChar('0')).
                    arg(msg.data[i*3],4,16,QChar('0')).
                    arg(globNum);
            stream << str;
            if (BRUSBFDN != 0)
            {
                if (msg.data[i*3+2] == 0xC) {
                    str_light = QString("%2%3\n").arg(
                                msg.data[i*3+1],4,16,QChar('0')).toUpper().
                            arg(msg.data[i*3],4,16,QChar('0')).toUpper();
                    stream2 << str_light;
                    ulong tmp = str_light.toULong(&ok, 16);
                    sigCh1.append(tmp);
                    sigCount++;
                }
            }
        }
    }
    file1.close();
    file2.close();
    if (sigCh1.isEmpty()) {WrapInfMes("Данные с генератора не получены"); return -2;}
    RemoveTrash(&sigCh1);

    QString str3 = "SigBRUS_right.txt";
    QFile file3(str3);
    QTextStream stream3(&file3);
    stream3.setCodec("UTF-8");
    file3.open(QIODevice::WriteOnly | QIODevice::Text);
    foreach (ulong sig, sigCh1) {
        str_light = QString("%1\n").arg( sig,8,16,QChar('0')).toUpper();
        stream3 << str_light;
    }
    file3.close();
    return 0;
}

int HrdwrNet::WriteToFileBFDN2DN(int BRUSBFDN)
{
    int res;
    int globNum = 0;
    bool ok;
    QString str1 = "SigBFDN2.txt";
    QList <ulong> sigV;
    QList <ulong> sigH;
    int sigLenFormHrd = 5120;
    if ((vertOpticIn == 0) || (horOpticIn == 0))
        sigLenFormHrd = sigLenFormHrd / 2;

    if (BRUSBFDN == 0) str1 = "SigBFDN2.txt";
    else str1 = "SigBRUS.txt";

    QFile file1(str1);
    QTextStream stream(&file1);
    stream.setCodec("UTF-8");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str;

    QString str2 = "SigBRUS_light.txt";
    QFile file2(str2);
    QTextStream stream2(&file2);
    stream2.setCodec("UTF-8");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    QString str_light;
    int sigCount = 0;

  //  int dataNum = 999;
//    for(int j = 0; j < 50; j++)
    int dataNum = 1650;
    for(int j = 0; j < 31; j++)
    {
        msg_t msg;
        if (BRUSBFDN == 0)
            res = ReadWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x1C,  dataNum, msg);
        else
            res = ReadWithWaitForSoc2(l1::BRUS, 0, 0, 0x1F,  dataNum, msg);
        if (res) {
            WrapInfMes(QString("Ошибка чтения памяти!!! Итерация %1").arg(j));
            return -1;
        }
        for(int i = 0; i < dataNum/3; i++) //(999/3)
        {
            globNum = j * (dataNum/3) + i;
            str = QString("%4: 0x%1 %2 %3 \n").arg(
                    msg.data[i*3+2],4,16,QChar('0')).
                    arg(msg.data[i*3+1],4,16,QChar('0')).
                    arg(msg.data[i*3],4,16,QChar('0')).
                    arg(globNum);
            stream << str;

            if ((BRUSBFDN != 0) && (sigCount < sigLenFormHrd)) {
                if (msg.data[i*3+2] == 0xE) {
                    str_light = QString("%2%3\n").arg(
                                msg.data[i*3+1],4,16,QChar('0')).toUpper().
                            arg(msg.data[i*3],4,16,QChar('0')).toUpper();
                    stream2 << str_light;
                    ulong tmp = str_light.toULong(&ok, 16);
                    sigH.append(tmp);
                    sigCount++;
                }
                if (msg.data[i*3+2] == 0xF) {
                    str_light = QString("%2%3\n").arg(
                                msg.data[i*3+1],4,16,QChar('0')).toUpper().
                            arg(msg.data[i*3],4,16,QChar('0')).toUpper();
                    stream2 << str_light;
                    ulong tmp = str_light.toULong(&ok, 16);
                    sigV.append(tmp);
                    sigCount++;
                }
            }
        }
    }
    int lenSig = 0;
    if (vertOpticIn) lenSig = sigV.length();
    else lenSig = sigH.length();
    for(int i = 0; i < lenSig; i++)
    {
        if (vertOpticIn)
            sigCh1.append(sigV.at(i));
        else
            sigCh1.append(0);
        if (horOpticIn)
            sigCh1.append(sigH.at(i));
        else
            sigCh1.append(0);
    }
    sigV.clear();
    sigH.clear();
    file1.close();
    file2.close();
    return 0;
}

int HrdwrNet::CompareResBFDN2()
{
    int i = 0;
    quint16 startCounter = sigCh1.at(0) & 0x3FFFF;
    quint16 counter;
    quint16 lo1, hi1, hi2, lo2;
    for (i = 0 ; i< sigCh1.length()/2; i++)
    {
        counter = (i + startCounter) % 256;
        lo1 = sigCh1.at(i*2) & 0x3FFFF;
        hi1 = (sigCh1.at(i*2) & 0xFFFFC0000)>>18;
        if ((hi1 != counter) || (lo1 != counter)){
            WrapInfMes("Прочитанный сигнал Vert не равен эталону!");
            WrapInfMes(QString("%1: Эталон = 0x%2; Память Hi = 0x%3; Память Lo = 0x%4").arg(i).
                       arg(counter,4,16,QChar('0')).arg(hi1,5,16,QChar('0')).arg((lo1,5,16,QChar('0'))));
            return -1;
        }
        lo2 = sigCh1.at((i*2)+1) & 0x3FFFF;
        hi2 = (sigCh1.at((i*2)+1) & 0xFFFFC0000)>>18;
        if ((hi2 != counter) || (lo2 != counter)){
            WrapInfMes("Прочитанный сигнал Hor не равен эталону!");
            WrapInfMes(QString("%1: Эталон = 0x%2; Память Hi = 0x%3; Память Lo = 0x%4").arg(i).
                       arg(counter,4,16,QChar('0')).arg(hi2,5,16,QChar('0')).arg((lo2,5,16,QChar('0'))));
            return -1;
        }
    }
    emit ErrorSig(QString("Данных для сравнения %1").arg(i*2));
    emit ErrorSig(QString("Прочитанный сигнал равен эталону. "));
    return 0;
}
/**
 * @brief HrdwrNet::ResLVDSBFDN2
 * Сброс Каналов LVDS и КРП
 */
int HrdwrNet::ResLVDSBFDN2()
{
    msg_t outMsg = msg_t();
    msg_t outMsg1 = msg_t();
    int res = 0;
    WrapInfMes("Сброс LVDS BFDN11");
    res = WriteWithWaitFor(UCODN, BFDN11, FPGA0, 0x1,  0x07F0, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса LVDS BFDN11"); return -1; }

    WrapInfMes("Сброс LVDS BFDN12");
    res = WriteWithWaitFor(UCODN, BFDN12, FPGA0, 0x1,  0x07F0, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса LVDS BFDN12"); return -1; }

    WrapInfMes("Сброс LVDS BFDN21");
    res = WriteWithWaitFor(UCODN, l2UCODN::BFDN21, FPGA0, 0x1,  0x07F0, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса LVDS BFDN21"); return -1; }

    WrapInfMes("Сброс памяти");
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA1, 0x18,  0x001, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса памяти."); return -1; }

    for(quint16 i = 1; i < 7; i++){
        WrapInfMes(QString("    Сброс КРП %1").arg(i));
        res = WriteWithWaitFor(UCODN, BFDN11, i, 0x53,  0x0001, outMsg);
        if (res){
            WrapInfMes(QString("Ошибка сброса КРП %1").arg(i));
            return -1;
        }
        WrapInfMes(QString("    Статус КРП %1").arg(i));
        res = ReadWithWaitFor(UCODN, BFDN11, i, 0x41, 1, outMsg1);
        if (res){
            WrapInfMes(QString("Ошибка чтения статуса КРП %1").arg(i));
            return -1;
        }
        emit ErrorSig(QString("    0x%1").arg(outMsg1.data[0],4,16,QChar('0')));
        if (outMsg1.data[0] && 0x0001)
            WrapInfMes(QString("    КРП %1 откалиброван").arg(i));
        else if (outMsg1.data[0] && 0x0006)
            WrapInfMes(QString("   Ошибка калибровки КРП %1").arg(i));
    }
    WrapInfMes("    Сброс памяти БРУС");
    res = WriteWithWaitForSoc2(l1::BRUS, 0, 0, 0x18,  0x0101, outMsg);
    if (res){
        WrapInfMes("Ошибка сброса памяти."); return -1; }
    WrapInfMes("    ");
    return 0;
}
/**
 * @brief HrdwrNet::ResComputingPart
 * Сброс вычислительной части
 */
int HrdwrNet::ResComputingPart()
{
    WrapInfMes("Сброс вычислительной части");
    msg_t outMsg = msg_t();
    int res = 0;
    for (int j = 1; j < 7; ++j) {
        for (int i = 0; i < 2; i++)
        {
            res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN11, j, 0x53,  0x0072, outMsg);
            if (res){
                WrapInfMes(QString("  Ошибка сброса BFDN11, FPGA%1").arg(j));
                return -1;
            }
        }
    }
    for (int j = 1; j < 7; ++j) {
        for (int i = 0; i < 2; i++)
        {
            res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN12, j, 0x53,  0x0072, outMsg);
            if (res){
                WrapInfMes(QString("  Ошибка сброса BFDN11, FPGA%1").arg(j));
                return -1;
            }
        }
    }
    for (int j = 2; j < 4; ++j) {
        for (int i = 0; i < 2; i++)
        {
            res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, j, 0x53,  0x0072, outMsg);
            if (res){
                WrapInfMes(QString("  Ошибка сброса BFDN21, FPGA%1").arg(j));
                return -1;
            }
        }
    }
    // сброс модуля моделирования
//    for (int j = 1; j < 7; ++j) {
//        for (int i = 0; i < 3; i++)
//        {
//            res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN12, j, 0x53,  0x0072, outMsg);
//            if (res){
//                WrapInfMes(QString("  Ошибка сброса BFDN12, FPGA%1").arg(j));
//                return -1;
//            }
//        }
//    }
    res = WriteWithWaitFor(l1::UCODN, l2UCODN::BFDN21, FPGA3, 0x12,  0x0100, outMsg);
    if (res){
        WrapInfMes("  Ошибка сброса BFDN21, FPGA3");
        return -1;
    }
    return 0;
}
