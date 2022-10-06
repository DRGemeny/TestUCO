#ifndef HRDWRNET_H
#define HRDWRNET_H

#define SlaveFlg 0x0000FFFFUL

#include <QAbstractSocket>
#include <QPushButton>
#include <QHostAddress>
#include "loghrd1.h"
#include "libhrdwr.h"

#define EmptyFifoFl 0x01

struct MAC1Prog  { // данные для программирования одного ГТС
    unsigned int nMACP;
    unsigned int VPhase;
    unsigned int HPhase;
    QList<unsigned short> lVPhase;
    QList<unsigned short> lHPhase;
};

struct GTSProg  { // данные для программирования всех ГТС
    unsigned int CoefFreq;
    unsigned int StartFreq;
    QList<MAC1Prog> mac1Prog;
};

/**
 * @brief The TrapsPar struct Настройки ловушки
 */
struct TrapsPar1
{
    // Входной сигнал - тру, Выходной - фолс
    bool in = true;
    // Сдвиг сигнала на 1 значение - тру, на 3 - фолс
    int shift = 0;
    //номер ПЛИС для считывания ловушки (1-7)
    quint16 numFPGA = 1;
};

class HrdwrNet: /*public QObject , */public LibHrdwr
{
    Q_OBJECT
public:
    void setNUKR(quint16 nUKR1) {nUKR = nUKR1;}
    void setWFileName(QString wFn) {WFileName = wFn;}
    void setWFileName1(QString wFn) {WFileName = TestFolder + wFn;}
    void setMiBlFn(QString MiBlFn) {MiBlFileName = MiBlFn;}
    void setMiBlFn_21(QString MiBlFn) {MiBlFileName21 = MiBlFn;}
    void SetlocalSocket(QTcpSocket* localSocket1) {localSocket = localSocket1;}
    void SetNumUkrForWrite(QString NumUkrForWrite) {this->NumUkrForWrite = NumUkrForWrite.toUShort();}
    void SetTestA(bool testA) {this->testA = testA;}
    void SetVertHorOpticCabel(bool vert, bool hor) {vertOpticIn = vert; horOpticIn = hor;}
    void SetFirstStart(bool frststrt) {firstStart = frststrt;}
    void SetGtsProg(QString fnm) { gtsProg.append(LoadGTSPars(TestFolder + "/Shift_2/" + fnm));}
    void SetGtsProg1()
    {
        gtsProg.clear();
        gtsProg.append(LoadGTSPars(TestFolder + "/Shift_2/Parametres_UCR_4"));
        gtsProg.append(LoadGTSPars(TestFolder + "/Shift_2/Parametres_UCR_22"));
    }
    void SetTrapsParIn(bool inPar) {TrapsPar.in = inPar;}
    void SetTrapsParShift(int shiftPar) {TrapsPar.shift = shiftPar;}
    void SetTrapsParNFPGA(QString nFPGAPar) {TrapsPar.numFPGA = nFPGAPar.toUInt();}
    void SetTestFolder(QString nTestFold) {TestFolder = nTestFold;}

    HrdwrNet();
    QString StandartTestFolder = "./Data_model/TEST_UCODN/";
    void InitHrdwrNet()
    {
        logHrd = new LogHrd1("log.txt");
        SetGtsProg1();
        firstStart = 0;
    }

    void InitHrdwrFromUIl(QList<quint16> UKRl, QTcpSocket* localSocket1, QTcpSocket* localSocket2)
    {
        UKRlist.clear();
        UKRlist.append(UKRl);
        localSocket = localSocket1;
        localSocket_2 = localSocket2;
    }

    GTSProg LoadGTSPars(QString fileName);
    void StartTestUKR();
    int OnUKR();

    void ResLVDSBFDN1();
    int SetupUKR();
    void LoadWwr();

    //Mibl
    void ResMibl(int addrBFDN);
    int LoadMibl(QString filename, int nBFDN);
    void TestMiblLoad(int addrBFDN);
    void StartMibl(int addrBFDN);

    void StartTestBFDN7();
    void ResWPack();
    void StartTrapBFDN();
    int ReadFromTramBFDN();
    int SimpleWrite();

    int TestMACP(int numBFDNTestMACP);

    int TestBFDN2();
    int ResLVDSBFDN2();
    int StartTestBFDN2_7(int dnKm, quint16 nUKRStart);
    void ReadFromTramType2BFDN2();
    int ReadFromTramType1BFDN2();
    int ReadFromTramType3BFDN2();
    int ReadFromTramType2BRUSKM(int numTest);
    int ReadFromTramType2BRUSDN(int numTest);
    int ReadBFDN2FPGA2ButCl();
    int ResComputingPart();
    void CycleStart(int nCycle, int dnKm, int numTest);


private:
    // реальнвй адрес УКР Используется для его настройки
    quint16 nUKR;
    QList <quint16> UKRlist;
    // адрес, использеумый в тесте УКР для настройки ловушек. По сути это номер входа, куда подключена 12ти канальная оптика от УКР_1 к БВДН11
    quint16 NumUkrForWrite;

//    GTSProg gtsProg;// данные для программирования всех ГТС
    QList<GTSProg> gtsProg;// данные для программирования всех ГТС
    unsigned short nMACP; // Номер МАЦП
    quint16 numOptCh;
    quint16 numPhisicalOptCh;
    QList <ulong> sigCh1;
    QList <ulong> sigCh2;
    QList <ulong> etCh1;
    QList <quint16> etCh2;
    QString WFileName;
    QString MiBlFileName;
    QString MiBlFileName21;
    TrapsPar1 TrapsPar;
    QString TestFolder;
    bool testA;
    bool vertOpticIn; // при подключении к БРУС только оптического кабеля с вертикальной составляющей
    bool horOpticIn;
    bool firstStart;

    int Test_RXon();
    void RemoveTrash(QList<ulong> *ch);
    int CompareRes(int numTrap, int numTest);
    int LoadEtalonFile(QString fileStr, QList<ulong> sigl, QList<ulong> &ch);
    int StartPackBFDN();
    int StartZeroSig();
    int LoadW();
    int LoadWFromFiles(QByteArray* arrayFile);
    int LoadMiBl(QString fileName, int addrBFDN);
    int SetupGTS();
    int StartGTS_BFDN();
    void WrapInfMes(QString str);

    QList<unsigned short> MakeDataList(int data);
    int TestTimesMibl();
    int StartGTS_BFDN_TestMACP(int numBFDNTestMACP);
    int ReadFromTramBFDN_TestMACP(int numBFDNTestMACP, quint16 numFPGAr, int numMACP, int numCh);
    int CompareRes_TestMACP(quint16 numMACP, quint16 numCh);
    int LoadEtalonFile_TestMACP(quint16 numMACP, QList<ulong> sigl, QList<ulong> &ch);

    int StartMemBFDN2();
    int WriteToFileBFDN2KM(int BRUSBFDN);
    int WriteToFileBFDN2DN(int BRUSBFDN);
    int CompareResBFDN2();
    int StartGTS_BFDN2(int dnKm, int& timeForStart);
    int CompareBRUS();

    //test
    void func1();
    void print1(char *ear1[]);

signals:
    void SigNumCycle(int i);

};

#endif // HRDWRNET_H
