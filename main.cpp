#include "myclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

  //myClient myClnt("My Client",hostName,nPort);   //Указывается ip-адрес сервера и номер порта в командной строке.
  //myClient myClnt("My Client","127.0.0.1",2323); //ip-адрес локальной машины.
    myClient myClnt; //ip-адрес БУК."192.168.31.2"
    myClnt.show();
    return a.exec();
}
