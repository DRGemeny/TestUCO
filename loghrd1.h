#ifndef LOGHRD1_H
#define LOGHRD1_H

#include <QObject>
#include <QString>
#include<QFile>
#include<QTextStream>
#include "msg_t.h"

class LogHrd1 : public QObject
{
    Q_OBJECT
public:
    QString fileName;
    QFile file;
    QTextStream stream;

public:
    LogHrd1(QString filename);    
    explicit LogHrd1(QObject *parent = nullptr);
//    ~LogHrd1();
    void ErrLog(QString format);
    void InfLog(QString format);

public slots:
    void ErrWriteLog(const msg_t msg);
    void ErrReadLog(const msg_t msg);
    void ErrCommonLog(QString str);
    void InfWriteLog(msg_t msg);
    void InfReadLog(const msg_t msg);
    void InfCommonLog(QString str);
signals:
    void sigErrorLog(QString str);

};
#endif // LOGHRD1_H
