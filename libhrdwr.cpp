/***
 * Библиотека функций чтения и записи пакетов по сети в два соккета.
 * Функции посылают пакеты и ждут ответов от сервера.
*/


#include "libhrdwr.h"

LibHrdwr::LibHrdwr(QObject *parent) : QObject(parent)
{

}

/**
 * @brief HrdwrNet::WriteWithWaitFor
 * Запись пакета данных, ожидание ответного пакета
 * @param addrl1 - адрес первого уровня
 * @param addrl2 - адрес второго уровня
 * @param addrl3 - адрес третьего уровня
 * @param addrReg - адрес регистра
 * @param data - данные для записи
 * @param outMsg - ответный пакет
 * @return 0 - ок, -1 неок
 */
int LibHrdwr::WriteWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                        unsigned short addrReg, unsigned short data, msg_t &outMsg)
{
    int res;
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QList<unsigned short> lData;
    lData.append(data);
    msg_t inMsg = msg_t(3, addrl1, addrl2, addrl3, addrReg, msgType::write, lData);
    QByteArray packetC03 = inMsg.toByteArray();//Переменная для хранения передаваемого сообщения С03.
    logHrd->InfWriteLog(inMsg);
    emit ShowMes(inMsg);

    out<< quint64(0)<< packetC03;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени С03.
    res = ReadFromSocket(outMsg, 2);
    if (res == 0) {
        emit ShowMes(outMsg);
        return 0;
    }
    else if (res == 1)
        return 0;
    else
        return -1;
}
/**
 * @brief HrdwrNet::WriteWithWaitFor
 * Запись пакета данных, ожидание ответного пакета
 * @param addrl1 - адрес первого уровня
 * @param addrl2 - адрес второго уровня
 * @param addrl3 - адрес третьего уровня
 * @param addrReg - адрес регистра
 * @param data - данные для записи
 * @param outMsg - ответный пакет
 * @return 0 - ок, -1 неок
 */
int LibHrdwr::WriteWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                               unsigned short addrReg, QList<unsigned short> data, msg_t &outMsg)
{
    int res;
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QList<unsigned short> lData;
    lData.append(data);
    msg_t inMsg = msg_t(3, addrl1, addrl2, addrl3, addrReg, msgType::write, lData);
    QByteArray packetC03 = inMsg.toByteArray();//Переменная для хранения передаваемого сообщения С03.
    emit ShowMes(inMsg);

    out<< quint64(0)<< packetC03;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени С03.
    res = ReadFromSocket(outMsg, 2);
    if (res == 0) {
        emit ShowMes(outMsg);
        return 0;
    }
    else if (res == 1)
        return 0;
    else
        return -1;
}
/**
 * @brief HrdwrNet::ReadWithWaitFor
 * Считывание данных
 * @param addrl1 - адрес первого уровня
 * @param addrl2 - адрес второго уровня
 * @param addrl3 - адрес третьего уровня
 * @param addrReg - адрес регистра
 * @param readDataLen - длина, считываемых данных
 * @param outMsg - пакет с данными
 * @return 0 - ок, -1 неок
 */
int LibHrdwr::ReadWithWaitFor(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                     unsigned short addrReg, unsigned short readDataLen, msg_t &outMsg)
{
    int res;
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::ReadWrite);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QList<unsigned short> data;
    msg_t inMsg = msg_t(5, addrl1, addrl2, addrl3, addrReg, msgType::read, readDataLen, data);
    logHrd->InfWriteLog(inMsg);
    QByteArray packetC05 = inMsg.toByteArray();//Переменная для хранения передаваемого сообщения С05.
    emit ShowMes(inMsg);

    out<< quint64(0)<< packetC05;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени С03.
    res = ReadFromSocket(outMsg, 2);
    if (res == 0) {
        emit ShowMes(outMsg);
        return 0;
    }
    else if (res == 1)
        return 0;
    else
        return -1;
}
/**
 * @brief HrdwrNet::ReadFromSocket
 * ожидание данных из сокета
 * @param outMsg пакет со считанными данными
 * @param call 0 для вывода данных на вкладку c03-c04; 1 для вывода данных на вкладку c05-c06; 2 для вывода данных на вкладку TestBFDN
 * @return 0 - ок; 1 - текстовое сообщение; 2 - сообщение об ошибке; 3 - пустое сообщение
 */
int LibHrdwr::ReadFromSocket(msg_t &outMsg, int call, int Ttimeout)
//int HrdwrNet::ReadFromSocket(msg_t &outMsg, int call)
{
    msg_t msgFromServer;
    int numberMessage;             //Переменная, хранящая тип сообщения, передаваемого сервером.
    QByteArray arrayMessageServer; //Сообщение, передаваемое сервером.
    quint64 nextBlockSize;
    QDataStream in(localSocket);
    in.setVersion(QDataStream::Qt_5_1); //Всегда необходимо проверять номер релиза!!!!Должны совпадать на сервере и клиенте!!!!
    while(localSocket->bytesAvailable() < (int)sizeof(quint64))
    {
        if (!(localSocket->waitForReadyRead(Ttimeout))){
            emit ErrorSig("Ответное сообщение от сервера не получено");
            break;
        }
    }
    in >> nextBlockSize;

    while(localSocket->bytesAvailable() < nextBlockSize)
    {
        if (!(localSocket->waitForReadyRead(Ttimeout)))
            break;
    }
    in>>arrayMessageServer;//Записываем сообщение от сервера в массив
    if (arrayMessageServer.isEmpty())
    {
        emit ErrorSig("Сообщение от сервера не получено.", call);
        return 3;
    }
    numberMessage = ReadHeadMessage(arrayMessageServer);//Определяем тип сообщения
    switch (numberMessage) {
    case MiBl_ANSWER_Clear:
        emit ErrorSig("    " + arrayMessageServer.mid(7).chopped(1), call);
        logHrd->ErrCommonLog(arrayMessageServer);
        return 1;
    case STR_MESSAGE:
//        emit ErrorSig(arrayMessageServer.mid(7).chopped(1), call);
        logHrd->ErrCommonLog(arrayMessageServer);
        return 1;
    case C22_MESSAGE:
        emit ErrorSig("    " + arrayMessageServer.mid(7).chopped(1), call);
        logHrd->ErrCommonLog(arrayMessageServer);
        return 1;
    case ERR_MESSAGE:
        emit ErrorSig(arrayMessageServer.mid(7).chopped(1), call);
        logHrd->ErrCommonLog(arrayMessageServer);
        return 2;
    case C04_MESSAGE:
        msgFromServer = msg_t(&arrayMessageServer);
        logHrd->InfReadLog(msgFromServer);
        break;
    case C06_MESSAGE:
        msgFromServer = msg_t(&arrayMessageServer);
        logHrd->InfReadLog(msgFromServer);
        break;
    default:
        break;
    }
//    nextBlockSize = 0;
    outMsg = msgFromServer;
    return 0;
}

/**
 * @brief HrdwrNet::WriteWithWaitFor
 * Запись пакета данных, ожидание ответного пакета
 * @param addrl1 - адрес первого уровня
 * @param addrl2 - адрес второго уровня
 * @param addrl3 - адрес третьего уровня
 * @param addrReg - адрес регистра
 * @param data - данные для записи
 * @param outMsg - ответный пакет
 * @return 0 - ок, -1 неок
 */
int LibHrdwr::WriteWithWaitForSoc2(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                        unsigned short addrReg, unsigned short data, msg_t &outMsg)
{
    int res;
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QList<unsigned short> lData;
    lData.append(data);
    msg_t inMsg = msg_t(3, addrl1, addrl2, addrl3, addrReg, msgType::write, lData);
    QByteArray packetC03 = inMsg.toByteArray();//Переменная для хранения передаваемого сообщения С03.
    logHrd->InfWriteLog(inMsg);
    emit ShowMes(inMsg);

    out<< quint64(0)<< packetC03;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket_2->write(arrayBlock);//Передаем сообщени С03.
    res = ReadFromSocket2(outMsg, 2);
    if (res == 0) {
//        emit ShowMes(outMsg);
        return 0;
    }
    else if (res == 1)
        return 0;
    else
        return -1;
}
/**
 * @brief HrdwrNet::WriteWithWaitFor
 * Запись пакета данных, ожидание ответного пакета
 * @param addrl1 - адрес первого уровня
 * @param addrl2 - адрес второго уровня
 * @param addrl3 - адрес третьего уровня
 * @param addrReg - адрес регистра
 * @param data - данные для записи
 * @param outMsg - ответный пакет
 * @return 0 - ок, -1 неок
 */
int LibHrdwr::WriteWithWaitForSoc2(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                               unsigned short addrReg, QList<unsigned short> data, msg_t &outMsg)
{
    int res;
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QList<unsigned short> lData;
    lData.append(data);
    msg_t inMsg = msg_t(3, addrl1, addrl2, addrl3, addrReg, msgType::write, lData);
    QByteArray packetC03 = inMsg.toByteArray();//Переменная для хранения передаваемого сообщения С03.
    emit ShowMes(inMsg);

    out<< quint64(0)<< packetC03;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket_2->write(arrayBlock);//Передаем сообщени С03.
    res = ReadFromSocket2(outMsg, 2);
    if (res == 0) {
//        emit ShowMes(outMsg);
        return 0;
    }
    else if (res == 1)
        return 0;
    else
        return -1;
}
/**
 * @brief HrdwrNet::ReadWithWaitFor
 * Считывание данных
 * @param addrl1 - адрес первого уровня
 * @param addrl2 - адрес второго уровня
 * @param addrl3 - адрес третьего уровня
 * @param addrReg - адрес регистра
 * @param readDataLen - длина, считываемых данных
 * @param outMsg - пакет с данными
 * @return 0 - ок, -1 неок
 */
int LibHrdwr::ReadWithWaitForSoc2(unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
                     unsigned short addrReg, unsigned short readDataLen, msg_t &outMsg)
{
    int res;
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::ReadWrite);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QList<unsigned short> data;
    msg_t inMsg = msg_t(5, addrl1, addrl2, addrl3, addrReg, msgType::read, readDataLen, data);
    logHrd->InfWriteLog(inMsg);
    QByteArray packetC05 = inMsg.toByteArray();//Переменная для хранения передаваемого сообщения С05.
    emit ShowMes(inMsg);

    out<< quint64(0)<< packetC05;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket_2->write(arrayBlock);//Передаем сообщени С03.
    res = ReadFromSocket2(outMsg, 2);
    if (res == 0) {
        emit ShowMes(outMsg);
        return 0;
    }
    else if (res == 1)
        return 0;
    else
        return -1;
}
/**
 * @brief HrdwrNet::ReadFromSocket
 * ожидание данных из сокета
 * @param outMsg пакет со считанными данными
 * @param call 0 для вывода данных на вкладку c03-c04; 1 для вывода данных на вкладку c05-c06; 2 для вывода данных на вкладку TestBFDN
 * @return 0 - ок; 1 - текстовое сообщение; 2 - сообщение об ошибке; 3 - пустое сообщение
 */
int LibHrdwr::ReadFromSocket2(msg_t &outMsg, int call, int Ttimeout)
{
        msg_t msgFromServer;
        int numberMessage;             //Переменная, хранящая тип сообщения, передаваемого сервером.
        QByteArray arrayMessageServer; //Сообщение, передаваемое сервером.
        quint64 nextBlockSize;
        QDataStream in(localSocket_2);
        in.setVersion(QDataStream::Qt_5_1); //Всегда необходимо проверять номер релиза!!!!Должны совпадать на сервере и клиенте!!!!
        while(localSocket_2->bytesAvailable() < (int)sizeof(quint64))
        {
            if (!(localSocket_2->waitForReadyRead(Ttimeout))){
                emit ErrorSig("Ответное сообщение от сервера не получено");
                break;
            }
        }
        in >> nextBlockSize;

        while(localSocket_2->bytesAvailable() < nextBlockSize)
        {
            if (!(localSocket_2->waitForReadyRead(Ttimeout)))
                break;
        }
        in>>arrayMessageServer;//Записываем сообщение от сервера в массив
        if (arrayMessageServer.isEmpty())
        {
            emit ErrorSig("Сообщение от сервера не получено.", call);
            return 3;
        }
        numberMessage = ReadHeadMessage(arrayMessageServer);//Определяем тип сообщения
        switch (numberMessage) {
        case MiBl_ANSWER_Clear:
            emit ErrorSig(arrayMessageServer.mid(7).chopped(1), call);
            logHrd->ErrCommonLog(arrayMessageServer);
            return 1;
        case STR_MESSAGE:
            emit ErrorSig(arrayMessageServer.mid(7).chopped(1), call);
            logHrd->ErrCommonLog(arrayMessageServer);
            return 1;
        case C22_MESSAGE:
            emit ErrorSig(arrayMessageServer.mid(7).chopped(1), call);
            logHrd->ErrCommonLog(arrayMessageServer);
            return 1;
        case ERR_MESSAGE:
            emit ErrorSig(arrayMessageServer.mid(7).chopped(1), call);
            logHrd->ErrCommonLog(arrayMessageServer);
            return 2;
        case C04_MESSAGE:
            msgFromServer = msg_t(&arrayMessageServer);
            logHrd->InfReadLog(msgFromServer);
            break;
        case C06_MESSAGE:
            msgFromServer = msg_t(&arrayMessageServer);
            logHrd->InfReadLog(msgFromServer);
            break;
        default:
            break;
        }
        nextBlockSize = 0;
        outMsg = msgFromServer;
        return 0;
}

/**
 * @brief myClient::ReadHeadMessage Метод определения типа сообщения.
 * @param inMessage - входное сообщение.
 * @return - тип сообщения.
 */
int LibHrdwr::ReadHeadMessage(QByteArray inMessage)
{
    QByteArray arrNumMess;
    int numMes;
    bool ok;
    arrNumMess = inMessage.mid(2,4);
//    arrNumMess = inMessage.mid(2,1);
    numMes = arrNumMess.toInt(&ok,16);
    return numMes;
}
