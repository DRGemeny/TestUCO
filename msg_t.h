#ifndef MSG_T_H
#define MSG_T_H


#include <QLibrary>
#include <QTextEdit>

enum msgType { write = 0, read = 1};

class msg_t
{
public:    
    unsigned short numMes; // номер сообщения на Клиенте
    unsigned short dst3;
    unsigned short dst2;
    unsigned short dst1;
    unsigned short addrReg;
    unsigned short type;
    unsigned short tag = 0xEEEE;
    unsigned short reserve;
    QList<unsigned short> data;
    unsigned short dataLen; // Реальное количество данных
    unsigned short crc;

    QList<unsigned short> listPac;
    unsigned short *masPac;

public:
    msg_t (unsigned short numMes1, unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
           unsigned short addrReg, msgType type, QList<unsigned short> data);
    msg_t (unsigned short numMes1, unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                  unsigned short addrReg1, msgType type1, unsigned short dataLenMsg, QList<unsigned short> data1);

    msg_t (int len, unsigned short* buf);
    msg_t (QByteArray *ba);
    msg_t ();
    QByteArray toByteArray();
    void ShowMesTextEdit(QTextEdit *tE);
    void ShowMesTextEditMas(QTextEdit *tE);
};

#endif // MSG_T_H
