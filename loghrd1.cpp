#include "loghrd1.h"
#include<QFile>
#include <QTextStream>
#include<QTime>

#include <stdio.h>
#include "msg_t.h"
//#include "test_ukr.h"

LogHrd1::LogHrd1(QObject *parent) : QObject(parent)
{
}
/*
LogHrd1::~LogHrd1()
{
    stream<<endl;
    stream.flush();
    file.close();
}
*/

LogHrd1::LogHrd1(QString filename)
{
    fileName = filename;
    file.setFileName(fileName);
    stream.setDevice(&file);
#ifdef Hrd
    stream.setCodec("UTF-8");
#else
    stream.setCodec("Windows-1251");
#endif
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        emit sigErrorLog("Невозможно открыть файл "+ fileName);
        return;
    }
    else {
        QString str = QString("%1:%2:%3.%4: Старт Теста УКР").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
                arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
        stream << str<<endl;
        if (stream.status() != QTextStream::Ok)
            emit sigErrorLog("Ошибка Записи в файл "+ fileName);
    }    
}

void LogHrd1::ErrLog(QString format)
{
    QString str = QString("%1:%2:%3.%4: [Ошибка]").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
            arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
    stream << str;
    stream << format <<endl;
}

void LogHrd1::InfLog(QString format)
{
    QString str = QString("%1:%2:%3.%4:").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).
            arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
    stream << str;
    stream << format<<endl;
}

void LogHrd1::ErrWriteLog(const msg_t msg)
{
    ErrLog("Ошибка записи\n");
    InfLog(QString("AdrL1=%1, AdrL2=%2, AdrL3=%3, AdrReg=%4").arg(msg.dst1). arg(msg.dst2).arg(msg.dst3).arg(msg.addrReg));
    if (msg.type)
        for (int i = 0; i< 6; i++)
            InfLog(QString("<--\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
    else
        for (int i = 0; i< msg.dataLen + 6; i++)
            InfLog(QString("<--\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
}

void LogHrd1::ErrReadLog(const msg_t msg)
{
    ErrLog("Ошибка чтения\n");
    InfLog(QString("AdrL1=%1, AdrL2=%2, AdrL3=%3, AdrReg=%4").arg(msg.dst1). arg(msg.dst2).arg(msg.dst3).arg(msg.addrReg));
    if (msg.type)
        for (int i = 0; i< msg.dataLen + 6; i++)
            InfLog(QString("-->\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
    else
        for (int i = 0; i< 6; i++)
            InfLog(QString("-->\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
}

void LogHrd1::InfWriteLog(msg_t msg)
{    
    InfLog(QString("\t\tAdrL1=%1, AdrL2=%2, AdrL3=%3, AdrReg=%4").arg(msg.dst1). arg(msg.dst2).arg(msg.dst3).arg(msg.addrReg));
    if (msg.type)
        for (int i = 0; i< 6; i++)
            InfLog(QString("<--\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
    else
        for (int i = 0; i< msg.dataLen + 6; i++)
            InfLog(QString("<--\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
}

void LogHrd1::InfReadLog(const msg_t msg)
{
    InfLog(QString("\t\tAdrL1=%1, AdrL2=%2, AdrL3=%3, AdrReg=%4").arg(msg.dst1). arg(msg.dst2).arg(msg.dst3).arg(msg.addrReg));
    if (msg.type)
        for (int i = 0; i< msg.dataLen + 6; i++)
            InfLog(QString("-->\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
    else
        for (int i = 0; i< 6; i++)
            InfLog(QString("-->\t\tdata: 0x%1").arg(msg.masPac[i], 4, 16, QChar('0')));
}

void LogHrd1::ErrCommonLog(QString str)
{
    ErrLog(str);
}

void LogHrd1::InfCommonLog(QString str)
{
    InfLog(str);
}
