/***
 * Библиотека функций чтения и записи пакетов по сети в два соккета.
 * Функции посылают пакеты и ждут ответов от сервера.
*/

#ifndef LIBHRDWR_H
#define LIBHRDWR_H

#include <QObject>
#include <QTcpSocket>
#include "msg_t.h"
#include "loghrd1.h"
// коды сообщений между клиентом и сервером
enum {
    STR_MESSAGE = 0x0,
    ERR_MESSAGE = 0x1,
    C03_MESSAGE = 0x3,
    C04_MESSAGE = 0x4,
    C05_MESSAGE = 0x5,
    C06_MESSAGE = 0x6,
    C21_MESSAGE = 0x21,
    C22_MESSAGE = 0x22,
    MiBl_MESSAGE = 0x7,
    MiBl_MESSAGE_Clear = 0x9,
    Reset_LVDS_MESSAGE = 0x100,
    ID_DD_MESSAGE = 0x102,
    MiBl_ANSWER_Clear = 0xA,
};
// кодировки адресов первого уровня
enum l1 : unsigned short {
    BUK = 1, UCODN = 2, BRUS = 3, UEVM = 4, UKR = 5
};
//кодировки адресов второго уровня для БУКа
enum l2BUK : unsigned short {
    YAUK = 0, YAS1 = 2, YAS2 = 3
};
//кодировки адресов второго уровня для УЦОДНа
enum l2UCODN : unsigned short {
    BFDN11 = 1, BFDN12 = 2, BFDN21 = 3, BFDN13 = 4, BFDN14 = 5, BFDN22 = 6
};
//кодировки адресов второго уровня для УКРа
enum l2UKR : unsigned short {
    UKR1 = 1, UKR2 = 2, UKR3 = 3, UKR4 = 4, UKR5 = 5, UKR6 = 6,
    UKR7 = 7, UKR8 = 8, UKR9 = 9, UKR10 = 10, UKR11 = 11, UKR12 = 12,
    UKR13 = 13, UKR14 = 14, UKR15 = 15, UKR16 = 16, UKR17 = 17, UKR18 = 18, UKR19 = 19
};
//кодировки адресов третьего уровня для УКР
enum l3UKR : unsigned short {
    MACP1 = 1, MACP2 = 2, MACP3 = 3, MACP4 = 4, MACP5 = 5, MACP6 = 6, MACP7 = 7, BC = 0xF
};
//кодировки адресов третьего уровня для БФДН
enum l3BFDN : unsigned short {
    FPGA0 = 0, FPGA1 = 1, FPGA2 = 2, FPGA3 = 3, FPGA4 = 4, FPGA5 = 5, FPGA6 = 6, FPGA7 = 7
};
// часто встречаемые регистры из адресного пространства внутренних ресурсов устройств
enum : unsigned short {
    TimeReg = 0x4,
    SlaveReg = 0x61,
    MasterReg = 0x61,
    ResMibl = 0x62,
    SlaveReg_2 = 62,
    FIFOMibl = 0x60
};


class LibHrdwr : public QObject
{
    Q_OBJECT
public:
    explicit LibHrdwr(QObject *parent = nullptr);
    int WriteWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                         unsigned short addrReg, QList<unsigned short> data, msg_t &outMsg);
    int WriteWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                            unsigned short addrReg, unsigned short data, msg_t &outMsg);
    int ReadWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                         unsigned short addrReg, unsigned short readDataLen, msg_t &outMsg);
    int WriteWithWaitForSoc2(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                         unsigned short addrReg, QList<unsigned short> data, msg_t &outMsg);
    int WriteWithWaitForSoc2(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                            unsigned short addrReg, unsigned short data, msg_t &outMsg);
    int ReadWithWaitForSoc2(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                         unsigned short addrReg, unsigned short readDataLen, msg_t &outMsg);
    int ReadFromSocket(msg_t &outMsg, int call, int Ttimeout = 4000);
    int ReadFromSocket2(msg_t &outMsg, int call, int Ttimeout = 4000);

    int ReadHeadMessage(QByteArray inMessage);
protected:
    LogHrd1 *logHrd;
    QTcpSocket* localSocket;       //Указатель на QLocalSocket.
    QTcpSocket* localSocket_2;       //Указатель на QLocalSocket.

signals:
    void ErrorSig(QString str, int res);
    void ErrorSig(QString str);
    void ErrorSig3(QString str);
    void ShowMes(msg_t outMsg);
    void connectedServer();

public slots:
};

#endif // LIBHRDWR_H
