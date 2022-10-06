#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QMainWindow>

#include <QTabWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>
#include <QHostAddress>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QCloseEvent>
#include <QSpinBox>
#include <QSettings>
#include<QTime>
#include <QJsonArray>
#include <QJsonObject>
//#include "msg_t.h"
#include "hrdwrnet.h"

namespace Ui {
class myClient;
}

class myClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit myClient(QWidget *parent = nullptr);//Имя сервера, ip-адрес, № порта.

    void UiSetStyle();//Метод обрамление полей графической оболчки.

    //Методы для работы с настройками приложений.
    //Позволяют сохранять предыдущие значения в полях ввода сообщений.
    void WriteSettings();//Метод, сохраняющий текущие значения полей графической формы.
    void ReadSettings(); //Метод, загружающий сохранённые значения в поля графической формы.

    ~myClient();

private:

    Ui::myClient *ui;
    QSettings clientSettings;      //Переменная для работы с настройками приложений.
    QTcpSocket* localSocket;       //Указатель на QLocalSocket.
    QTcpSocket* localSocket_2;       //Указатель на QLocalSocket.
    QTextEdit* textEdit;           //Указатели на элементы интерфейса.
    quint64 nextBlockSize = 0;         //Размер принимаемого от сервера блока.
    quint64 nextBlockSize_2 = 0;         //Размер принимаемого от сервера блока.
    QByteArray arrayMessageServer; //Сообщение, передаваемое сервером.
    int numberMessage;             //Переменная, хранящая тип сообщения, передаваемого сервером.
    int curTEIndex;
    QTime time = QTime::currentTime();
    HrdwrNet hrdwrNet;
    int nPort = 2323;
    int nPort_2 = 2424;
    int server1Connection;


    bool ShowMess = 0;
    QList<quint16> UKRl = {0x1, 0x2};


    msg_t msgFromServer;

    void WriteMessageC03ToClientForm();//Метод формирования сообщения С 03 для рассылки в железо (визуализация на клиенте).
    void WriteMessageC05ToClientForm();//Метод формирования сообщения С 03 для рассылки в железо (визуализация на клиенте).

    void MessageC03FromClientToServer(QByteArray& outPacket); //Метод формирования шаблона сообщения С 03 для передачи по TCP от клиента к серверу.
    void MessageC05FromClientToServer(QByteArray& outPacket); //Метод формирования шаблона сообщения С 03 для передачи по TCP от клиента к серверу.

    //void MessageC03FromClientToServer(unsigned short dst1, unsigned short dst2, unsigned short dst3, unsigned short addrReg, unsigned short length,
    //                                            unsigned short tag,  unsigned short *data,QByteArray& outPacketC03);
    int ReadHeadMessage(QByteArray);//Метод определения типа сообщения.
    void ShowStringMessage(QByteArray arrayStringMessage);//Метод визуализации текстового сообщения в строке состояния.
    void ShowErrorMessage(QByteArray arrayStringMessage); //Метод визуализации сообщения - ошибки в строке состояния.

    int StartPackBFDN();
    void StartTestBFDN();

    int WriteWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                            unsigned short addrReg, unsigned short data, msg_t &outMsg);
    int WriteWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                                   unsigned short addrReg, QList<unsigned short> data, msg_t &outMsg);
    int ReadWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                         unsigned short addrReg, unsigned short readDataLen, msg_t &outMsg);
    int ReadFromSocket(msg_t &outMsg);
    int getGroupCheck();

private slots:
    void TabWChange(int newTab);
    void slotError(QAbstractSocket::SocketError);//Слот обработки ошибок сокета.
    void slotSendMessageC03ToServer();           // Слот передачи информации на сервер.
    void slotSendMessageC05ToServer();           // Слот передачи информации на сервер.
//    void slotSendMessageMiBlToServer();           // Слот передачи информации на сервер.
  //  void slotSendMessageResetLVDSToServer();      // Слот передачи информации на сервер.
    //void slotSendMessageReadID_DDToServer();      // Слот передачи информации на сервер.
    void slotConnected();                        // Слот обработки сигнала соединения с сервером.
    void slotIPConnected();

    void SlotTextChangedWFile(QString str);
    void SlotTextChangedFileList(QString str);
    void SlotTextChangedFileList_2(QString str);
    void SlotTextChangedFileList_3(QString str);
    void SlotToggRadioButton(bool);
    void SlotToggGroupRadioButton(bool);
    void SlotTextChangedNumFPGATrap(QString str);
    void SlotToggledChB_4(bool chb)
    {
        hrdwrNet.SetFirstStart(chb);
    }
    void SlotToggledChB_3_2(bool chb);

    // Слоты очистки форм по нажатию клавиши.
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void LoadWCl();
    void ClearTBTECl();
    void ResLVDSCl();
    void ShowRes(QString func);
    void ShowRes(QString func, int call);

    void SetupUKRCl();
    void TestBFDNCl_3();
    void TestBFDNCl_4();
    void TestBFDNCl_5();
    void TestBFDNCl_6();
    void TestBFDNCl_7();
    void TestResWCl();
    void ReadTrapBFDNButtCl();
    void ShowMesCl(msg_t msg);
    void TestMACPCl();

    void ResLVDSBFDN2Cl();
    void TestBFDN2Cl_7();
    void ReadTrapT1BFDN2Cl();
    void ReadTrapT2BFDN2Cl();
    void ReadTrapT3BFDN2Cl();
    void ReadFromTramType2BRUSCl();
    void ResComputingPartButCl();
    void CycleStartButtCl();
    void ReadBFDN2FPGA2ButCl();
    void SlNumCycle(int i);

    void Test1DosMButtCl();
    void Test2DosMButtCl();
    void Test3DosMButtCl();
    void Test4DosMButtCl();
};


static unsigned short CRC16 (const unsigned char *nData, unsigned short wLength)//Метод для работы с контрольной суммой (Каляев З.В.).
{
    static const unsigned short wCRCTable[] = {
        0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
        0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
        0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
        0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
        0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
        0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
        0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
        0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
        0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
        0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
        0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
        0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
        0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
        0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
        0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
        0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
        0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
        0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
        0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
        0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
        0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
        0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
        0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
        0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
        0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
        0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
        0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
        0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
        0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
        0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
        0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
        0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };
    unsigned char nTemp;
    unsigned short wCRCWord = 0xFFFF;
    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord ^= wCRCTable[nTemp];
    }
    return wCRCWord;
}

#endif // MYCLIENT_H
