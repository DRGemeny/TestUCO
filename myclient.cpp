#include "myclient.h"
#include "ui_myclient.h"

#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QMessageBox>
#include "msg_t.h"
#include <QJsonObject>


myClient::myClient( QWidget *parent) :
    QMainWindow(parent),nextBlockSize(0),
    ui(new Ui::myClient),
    clientSettings("NIC", "Client"),//Переменная настроек приложения для сообщения.
    hrdwrNet()

{
    server1Connection = 0;
    ui->setupUi(this);
    UiSetStyle();     //Обрамление полей графической оболчки.

    connect(ui->FileListEdit,SIGNAL(textChanged(QString)),this,SLOT(SlotTextChangedFileList(QString)));
    connect(ui->FileListEdit_2,SIGNAL(textChanged(QString)),this,SLOT(SlotTextChangedFileList_2(QString)));
    connect(ui->FileListEdit_3,SIGNAL(textChanged(QString)),this,SLOT(SlotTextChangedFileList_3(QString)));
    connect(ui->radioButton,SIGNAL(toggled(bool)),this,SLOT(SlotToggRadioButton(bool)));
    connect(ui->radioButton_3,SIGNAL(toggled(bool)),this,SLOT(SlotToggGroupRadioButton(bool)));
    connect(ui->radioButton_4,SIGNAL(toggled(bool)),this,SLOT(SlotToggGroupRadioButton(bool)));
    connect(ui->radioButton_5,SIGNAL(toggled(bool)),this,SLOT(SlotToggGroupRadioButton(bool)));
    connect(ui->radioButton_6,SIGNAL(toggled(bool)),this,SLOT(SlotToggGroupRadioButton(bool)));
    connect(ui->radioButton_7,SIGNAL(toggled(bool)),this,SLOT(SlotToggGroupRadioButton(bool)));        
    connect(ui->lineEditNumFPGATrap,SIGNAL(textChanged(QString)),this,SLOT(SlotTextChangedNumFPGATrap(QString)));
    connect(ui->checkBox_4, SIGNAL(toggled(bool)), this, SLOT(SlotToggledChB_4(bool)));
    connect(ui->checkBox_3, SIGNAL(toggled(bool)), this, SLOT(SlotToggledChB_3_2(bool)));
    connect(ui->checkBox_2, SIGNAL(toggled(bool)), this, SLOT(SlotToggledChB_3_2(bool)));
    ReadSettings();   //Загрузка в поля графической оболчки предыдущих значений.

    QString hostName(ui->lineIPAdress->text());
    nPort = ui->lineIPAdress_2->text().toInt();
    localSocket = new QTcpSocket(this);//Инициализируем сокет для текущего ip-адреса. Для локальной системы - "127.0.0.1".
    connect(localSocket, SIGNAL(connectedServer()), this, SLOT(slotConnected()));//Устанавливаем соединение между сигналом подключения сокета к серверу и обработчиком сигнала.
    connect(localSocket, SIGNAL(connected()), SLOT(slotConnected()));//Устанавливаем соединение между сигналом подключения сокета к серверу и обработчиком сигнала.
    connect(localSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(slotError(QAbstractSocket::SocketError)));//Проверка на ошибку соединения.
    localSocket->connectToHost(hostName, nPort);
    if (localSocket->waitForConnected(3000))
        slotConnected();

    QDataStream in(localSocket);
    in.setVersion(QDataStream::Qt_5_1); //Всегда необходимо проверять номер релиза!!!!Должны совпадать на сервере и клиенте!!!!
    while(localSocket->bytesAvailable() < (int)sizeof(quint64))
    {
        localSocket->waitForReadyRead(3000);
        break;
    }
    in >> nextBlockSize;
    while(localSocket->bytesAvailable() < nextBlockSize)
    {
        localSocket->waitForReadyRead(3000);
        return;
    }
    in>>arrayMessageServer;//Записываем сообщение от сервера в массив
    if (arrayMessageServer != ""){
        QList <QByteArray> qBaList = arrayMessageServer.split('\n');
        statusBar()->showMessage(qBaList[1]);
    }

    server1Connection = 1;
    QString hostName_2(ui->lineIPAdress_4->text());
    nPort_2 = ui->lineIPAdress_3->text().toUInt();
    localSocket_2 = new QTcpSocket(this);//Инициализируем сокет для текущего ip-адреса. Для локальной системы - "127.0.0.1".
    connect(localSocket_2, SIGNAL(connectedServer()), this, SLOT(slotConnected()));//Устанавливаем соединение между сигналом подключения сокета к серверу и обработчиком сигнала.
    connect(localSocket_2, SIGNAL(connected()), SLOT(slotConnected()));//Устанавливаем соединение между сигналом подключения сокета к серверу и обработчиком сигнала.
    connect(localSocket_2, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(slotError(QAbstractSocket::SocketError)));//Проверка на ошибку соединения.
    localSocket_2->connectToHost(hostName_2, nPort_2);

    if (localSocket_2->waitForConnected(3000))
        slotConnected();

    QDataStream in_2(localSocket_2);
    in_2.setVersion(QDataStream::Qt_5_1); //Всегда необходимо проверять номер релиза!!!!Должны совпадать на сервере и клиенте!!!!
    while(localSocket_2->bytesAvailable() < (int)sizeof(quint64))
    {
        localSocket_2->waitForReadyRead(3000);
        break;
    }
    in_2 >> nextBlockSize_2;
    while(localSocket_2->bytesAvailable() < nextBlockSize_2)
    {
        localSocket_2->waitForReadyRead(3000);
        return;
    }
    in_2>>arrayMessageServer;//Записываем сообщение от сервера в массив
    if (arrayMessageServer != ""){
        if (server1Connection == 1){
            QList <QByteArray> qBaList = arrayMessageServer.split('\n');
            statusBar()->showMessage(qBaList[1]);
        }
    }

    connect(&hrdwrNet, SIGNAL(ErrorSig(QString, int)), this, SLOT(ShowRes(QString, int )));
    connect(&hrdwrNet, SIGNAL(ErrorSig(QString)), this, SLOT(ShowRes(QString)));
    connect(&hrdwrNet, SIGNAL(ShowMes(msg_t)), this, SLOT(ShowMesCl(msg_t)));
    connect(&hrdwrNet, SIGNAL(SigNumCycle(int)), this, SLOT(SlNumCycle(int)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)),this, SLOT(TabWChange(int)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotSendMessageC03ToServer()));//Передаём сообщение С03 по нажатию кнопки.
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotSendMessageC05ToServer()));//Передаём сообщение С05 по нажатию кнопки.
    connect(ui->ClearTBTEButt, SIGNAL(clicked()),this, SLOT(ClearTBTECl()));
    connect(ui->ClearTBTEButt_2, SIGNAL(clicked()),this, SLOT(ClearTBTECl()));
    connect(ui->ResLVDSButt, SIGNAL(clicked()),this, SLOT(ResLVDSCl()));

    connect(ui->TestBFDNButt, SIGNAL(clicked()),this, SLOT(SetupUKR()));
    connect(ui->TestBFDNButt_2, SIGNAL(clicked()),this, SLOT(LoadWCl()));
    connect(ui->TestBFDNButt_3, SIGNAL(clicked()),this, SLOT(TestBFDNCl_3()));
    connect(ui->TestBFDNButt_7, SIGNAL(clicked()),this, SLOT(TestBFDNCl_7()));
    connect(ui->ReadTrapBFDNButt, SIGNAL(clicked()),this, SLOT(ReadTrapBFDNButtCl()));
    connect(ui->TestMACP, SIGNAL(clicked()),this, SLOT(TestMACPCl()));

//    connect(ui->TestBFDN2MemButt,SIGNAL(clicked()),this,SLOT(TestDFDN2MemCl()));
    connect(ui->ResLVDSBFDN2Butt,SIGNAL(clicked()),this,SLOT(ResLVDSBFDN2Cl()));
    connect(ui->TestBFDNButt_8, SIGNAL(clicked()),this, SLOT(TestBFDNCl()));
    connect(ui->TestBFDNButt_9, SIGNAL(clicked()),this, SLOT(LoadWCl()));
//    connect(ui->TestBFDNButt_10, SIGNAL(clicked()),this, SLOT(TestBFDNCl_3()));
    connect(ui->TestBFDNButt_11, SIGNAL(clicked()),this, SLOT(TestBFDN2Cl_7()));
    connect(ui->ReadTrapBFDNButt_2, SIGNAL(clicked()),this, SLOT(ReadTrapT2BFDN2Cl()));
    connect(ui->ReadTrapBFDNButt_3, SIGNAL(clicked()),this, SLOT(ReadTrapT1BFDN2Cl()));
    connect(ui->ReadTrapBFDNButt_4, SIGNAL(clicked()),this, SLOT(ReadTrapT3BFDN2Cl()));
    connect(ui->ReadTrapBFDNButt_5, SIGNAL(clicked()),this, SLOT(ReadFromTramType2BRUSCl()));
    connect(ui->ResComputingPartBut, SIGNAL(clicked()),this, SLOT(ResComputingPartButCl()));
    connect(ui->CycleStartButt, SIGNAL(clicked()),this, SLOT(CycleStartButtCl()));
    connect(ui->ReadBFDN2FPGA2But, SIGNAL(clicked()),this, SLOT(ReadBFDN2FPGA2ButCl()));

    connect(ui->IPConnect,SIGNAL(clicked()),this,SLOT(slotIPConnected()));

    connect(ui->Test1DosMButt,SIGNAL(clicked()),this,SLOT(Test1DosMButtCl()));
    connect(ui->Test2DosMButt,SIGNAL(clicked()),this,SLOT(Test2DosMButtCl()));
    connect(ui->Test3DosMButt,SIGNAL(clicked()),this,SLOT(Test3DosMButtCl()));
    connect(ui->Test4DosMButt,SIGNAL(clicked()),this,SLOT(Test4DosMButtCl()));

    in>>arrayMessageServer;//Записываем сообщение от сервера в массив
    in_2>>arrayMessageServer;//Записываем сообщение от сервера в массив
    hrdwrNet.InitHrdwrNet();
    hrdwrNet.InitHrdwrFromUIl(UKRl, localSocket, localSocket_2);

    int curTabIndex = ui->tabWidget->currentIndex();
    QGridLayout * la = new QGridLayout();
    la->setColumnStretch(0, 200);
    la->setColumnStretch(1, 250);
    la->addLayout(ui->tabWidget->widget(curTabIndex)->layout(),0,0);
    la->addWidget(ui->TestBFDNTextEdit, 0, 1);
    ui->tabWidget->widget(curTabIndex)->setLayout(la);
    curTEIndex = curTabIndex;    

    ui->checkBox_4->setChecked(true);
    ShowRes("Для выполнения первого теста нажмите кнопку \"Test_1\"");
}

myClient::~myClient()
{
    WriteSettings();//Сохраняем настройки приложения для сообщения.
    delete ui;
}

/**
 * @brief myClient::UiSetStyle Метод обрамление полей графической оболчки.
 */
void myClient::UiSetStyle()
{
    ui->ReadTrapBFDNButt_2->setVisible(false);
    ui->ReadTrapBFDNButt_3->setVisible(false);
    ui->ReadTrapBFDNButt_4->setVisible(false);

    // C03-C04
    ui->lineEdit->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_2->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_3->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_4->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_5->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_6->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->textEdit->setStyleSheet(QString("QTextEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->textEdit_2->setStyleSheet(QString("QTextEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->textEdit_3->setStyleSheet(QString("QTextEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    // C05-C06
    ui->lineEdit_7->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_8->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_9->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_10->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_11->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->lineEdit_12->setStyleSheet(QString("QLineEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->textEdit_4->setStyleSheet(QString("QTextEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
    ui->textEdit_5->setStyleSheet(QString("QTextEdit {border-width: 2px; border-style: solid; border-color: gray; border-radius: 5px;}"));
}

/**
  * @brief myClient::ReadSettings Метод чтения настроек приложения для сообщений.
  */
void myClient::ReadSettings()
{
    clientSettings.beginGroup("/Settings");
        //C03-C04
        ui->lineEdit->setText(clientSettings.value("/C03dst1", "").toString());
        ui->lineEdit_2->setText(clientSettings.value("/C03dst2", "").toString());
        ui->lineEdit_3->setText(clientSettings.value("/C03dst3", "").toString());
        ui->lineEdit_4->setText(clientSettings.value("/C03addr", "").toString());
        ui->lineEdit_5->setText(clientSettings.value("/C03length", "").toString());
        ui->lineEdit_6->setText(clientSettings.value("/C03tag", "").toString());
        ui->textEdit->setText(clientSettings.value("/C03Data", "").toString());
        //C05-C06
        ui->lineEdit_7->setText(clientSettings.value("/C05dst1", "").toString());
        ui->lineEdit_8->setText(clientSettings.value("/C05dst2", "").toString());
        ui->lineEdit_9->setText(clientSettings.value("/C05dst3", "").toString());
        ui->lineEdit_10->setText(clientSettings.value("/C05addr", "").toString());
        ui->lineEdit_11->setText(clientSettings.value("/C05length", "").toString());
        ui->lineEdit_12->setText(clientSettings.value("/C05tag", "").toString());
        ui->FileListEdit->setText(clientSettings.value("/MiblFN", "").toString());
        ui->FileListEdit_2->setText(clientSettings.value("/MiblFN21", "").toString());
        ui->FileListEdit_3->setText(clientSettings.value("/TestFolder", "").toString());

        ui->lineIPAdress->setText(clientSettings.value("/IpAdress", "").toString());
        ui->lineIPAdress_4->setText(clientSettings.value("/IpAdress2", "").toString());
        ui->lineIPAdress_2->setText(clientSettings.value("/Port", "").toString());
        ui->lineIPAdress_3->setText(clientSettings.value("/Port2", "").toString());

        ui->radioButton->setChecked(clientSettings.value("/TrapIn", "").toBool());
        ui->radioButton_2->setChecked(!(clientSettings.value("/TrapIn", "").toBool()));
        int shift = clientSettings.value("/ShiftData", "").toInt();
        if (shift == 0) ui->radioButton_3->setChecked(true);
        if (shift == 1) ui->radioButton_4->setChecked(true);
        if (shift == 2) ui->radioButton_5->setChecked(true);
        if (shift == 3) ui->radioButton_6->setChecked(true);
        ui->lineEditNumFPGATrap->setText(clientSettings.value("/NumFPGATrap", "").toString());
        ui->lineEditNumUKRTrap->setText(clientSettings.value("/NumUKRTrap", "").toString());
        ui->checkBox->setChecked(clientSettings.value("/TestA", "").toBool());

        ui->checkBox_2->setChecked(clientSettings.value("/VertOptic", "").toBool());
        ui->checkBox_3->setChecked(clientSettings.value("/HorOptic", "").toBool());


        clientSettings.endGroup();
}

/**
 * @brief myClient::WriteSettings Метод записи настроек приложения для сообщений.
 */
void myClient::WriteSettings()
{
    clientSettings.beginGroup("/Settings");
        //C03-C04
        clientSettings.setValue("C03dst1", ui->lineEdit->text());
        clientSettings.setValue("C03dst2", ui->lineEdit_2->text());
        clientSettings.setValue("C03dst3", ui->lineEdit_3->text());
        clientSettings.setValue("C03addr", ui->lineEdit_4->text());
        clientSettings.setValue("C03length", ui->lineEdit_5->text());
        clientSettings.setValue("C03tag", ui->lineEdit_6->text());
        clientSettings.setValue("C03Data", ui->textEdit->toPlainText());
        //C05-C06
        clientSettings.setValue("C05dst1", ui->lineEdit_7->text());
        clientSettings.setValue("C05dst2", ui->lineEdit_8->text());
        clientSettings.setValue("C05dst3", ui->lineEdit_9->text());
        clientSettings.setValue("C05addr", ui->lineEdit_10->text());
        clientSettings.setValue("C05length", ui->lineEdit_11->text());
        clientSettings.setValue("C05tag", ui->lineEdit_12->text());

        clientSettings.setValue("MiblFN", ui->FileListEdit->text());
        clientSettings.setValue("MiblFN21", ui->FileListEdit_2->text());
        clientSettings.setValue("TestFolder", ui->FileListEdit_3->text());

        clientSettings.setValue("IpAdress", ui->lineIPAdress->text());
        clientSettings.setValue("IpAdress2", ui->lineIPAdress_4->text());
        clientSettings.setValue("Port", ui->lineIPAdress_2->text());
        clientSettings.setValue("Port2", ui->lineIPAdress_3->text());

         clientSettings.setValue("TrapIn", ui->radioButton->isChecked());

         clientSettings.setValue("ShiftData", getGroupCheck());

         clientSettings.setValue("NumFPGATrap", ui->lineEditNumFPGATrap->text());
         clientSettings.setValue("NumUKRTrap", ui->lineEditNumUKRTrap->text());
         clientSettings.setValue("TestA", ui->checkBox->isChecked());

         clientSettings.setValue("VertOptic", ui->checkBox_2->isChecked());
         clientSettings.setValue("HorOptic", ui->checkBox_3->isChecked());

    clientSettings.endGroup();
}

void myClient::ClearTBTECl(){ ui->TestBFDNTextEdit->clear(); }


void myClient::Test1DosMButtCl()
{
    ui->FileListEdit_3->setText("Test1_CL_4_22_08102020");
    hrdwrNet.SetGtsProg1();
    hrdwrNet.CycleStart(ui->lineEditCycle->text().toInt(), ui->radioButtonCM->isChecked(), 1);
    ShowRes("Для выполнения второго теста нажмите кнопку \"Test_2\"");
}
void myClient::Test2DosMButtCl()
{
    ui->FileListEdit_3->setText("Test2_CL_4_22_UCR_1_13_08102020");
    hrdwrNet.SetGtsProg1();
    hrdwrNet.CycleStart(ui->lineEditCycle->text().toInt(), ui->radioButtonCM->isChecked(), 2);
    ShowRes("Для выполнения третьего теста нажмите кнопку \"Test_3\"");
}
void myClient::Test3DosMButtCl()
{
    ui->FileListEdit_3->setText("Test3_CL_4_22_08102020");
    hrdwrNet.SetGtsProg1();
    hrdwrNet.CycleStart(ui->lineEditCycle->text().toInt(), ui->radioButtonCM->isChecked(), 3);
    ShowRes("Для выполнения четвертого теста, переместите оптический кабель на БОР в разъем x18, затем нажмите кнопку \"Test_4\"");
}
void myClient::Test4DosMButtCl()
{
    ui->FileListEdit_3->setText("Test4_CL_4_22_08102020");
    hrdwrNet.SetGtsProg1();
    hrdwrNet.CycleStart(ui->lineEditCycle->text().toInt(), ui->radioButtonCM->isChecked(), 4);
}

void myClient::CycleStartButtCl()
{
    hrdwrNet.SetGtsProg1();
    hrdwrNet.CycleStart(ui->lineEditCycle->text().toInt(), ui->radioButtonCM->isChecked(), 5);
}

void myClient::ResComputingPartButCl()
{
    hrdwrNet.ResComputingPart();
}

void myClient::ReadBFDN2FPGA2ButCl()
{
    hrdwrNet.SetNumUkrForWrite(ui->lineEditNumUKRTrap->text());
    hrdwrNet.SetGtsProg("Test3ParAnt.json");
    hrdwrNet.setWFileName("./Data_model/14AE/Test3_DOS_M_CL_13_UKR_25_21092020/Shift_0/W_DN/Wvh_CL_13");
    hrdwrNet.TestMACP(3);
}
void myClient::ReadFromTramType2BRUSCl()
{
    hrdwrNet.SetVertHorOpticCabel(ui->checkBox_2->isChecked(), ui->checkBox_3->isChecked());
    hrdwrNet.ReadFromTramType2BRUSKM(0);
}
void myClient::ReadTrapT3BFDN2Cl()
{
    hrdwrNet.ReadFromTramType3BFDN2();
}
void myClient::ReadTrapT2BFDN2Cl()
{
    hrdwrNet.ReadFromTramType2BFDN2();
}

void myClient::ReadTrapT1BFDN2Cl()
{
    hrdwrNet.ReadFromTramType1BFDN2();
}

void myClient::TestBFDN2Cl_7()
{
    hrdwrNet.StartTestBFDN2_7(0, 1);
}

void myClient::ResLVDSBFDN2Cl()
{
    hrdwrNet.ResLVDSBFDN2();
}

void myClient::TestMACPCl()
{
    hrdwrNet.SetNumUkrForWrite(ui->lineEditNumUKRTrap->text());
    hrdwrNet.TestMACP(1);
}

void myClient::TestResWCl()
{
    hrdwrNet.ResWPack();
}

void myClient::ResLVDSCl()
{
//    hrdwrNet.ResLVDSBFDN1();
    hrdwrNet.ResLVDSBFDN2();
}

void myClient::SetupUKRCl()
{
    hrdwrNet.SetupUKR();
}

void myClient::TestBFDNCl_3()
{
//    int addrBFDN = 1;
//    hrdwrNet.ResMibl(addrBFDN);
//    hrdwrNet.LoadMibl(addrBFDN);
//    hrdwrNet.TestMiblLoad(addrBFDN);
//    hrdwrNet.StartMibl(addrBFDN);
}
void myClient::TestBFDNCl_4()
{
//    hrdwrNet.LoadMibl(1);
}
void myClient::TestBFDNCl_5()
{
    hrdwrNet.TestMiblLoad(1);
}
void myClient::TestBFDNCl_6()
{
    hrdwrNet.StartMibl(1);
}
void myClient::TestBFDNCl_7()
{
    hrdwrNet.StartTestBFDN7();
}

void myClient::ReadTrapBFDNButtCl()
{
    hrdwrNet.SetTestA(ui->checkBox->isChecked());
    hrdwrNet.ReadFromTramBFDN();
}

void myClient::LoadWCl()
{
    hrdwrNet.LoadWwr();
}


/**
 * @brief  myClient::WriteMessageC03ToClientForm Метод формирования сообщения С 03 для рассылки в железо (визуализация на клиенте).
 */
void myClient::WriteMessageC03ToClientForm()
{
    //Формируется универсальное сообщение, идентичное сообщению на сервере.
    bool ok;
    unsigned short* packet;
    packet = new unsigned short;
    packet[0] = static_cast<unsigned short>(((ui->lineEdit->text().toUShort(&ok,16)) << 12) | ((ui->lineEdit_2->text().toUShort(&ok,16)) << 4) | (ui->lineEdit_3->text().toUShort(&ok,16)));//Первое слово - адрес 1-го уровня.
    packet[1] = static_cast<unsigned short>((0 << 12) | (ui->lineEdit_4->text().toUShort(&ok,16)));//Второе слово - адрес 2-го уровня.
    QString data = ui->textEdit->toPlainText();
    QStringList strList = data.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    unsigned short lengthData = static_cast<unsigned short>(strList.length());
    packet[2] = lengthData;//Третье слово - размер данных.
    packet[3] = ui->lineEdit_6->text().toUShort(&ok,16);//Четвёртое слово - ID сообщения.
    packet[4] = 0x0000;//Пятое слово - резерв.
    int lengthPacket = lengthData +6;//Длина пакета.
    //Данные.
    for (int i = 0; i < lengthData; i++) {
        packet[i + 5] = strList[i].toUShort(&ok, 16);
    }
    packet[lengthPacket-1] = CRC16(reinterpret_cast<unsigned char*>(packet), static_cast<unsigned short>((lengthPacket * 2) - 2));//Последнее слово - CRC.
    //Визуализация сообщения C03 в поле textEdit_2 вкладки Tab.
    QString valueInHex="";
    valueInHex=valueInHex + QString("0x%1").arg(C03_MESSAGE)+ "\n";
    for(int i=0; i < lengthPacket; i++) {
        valueInHex = valueInHex + QString("0x%1").arg(packet[i],4,16,QChar('0')).toUpper() + "\n";
    }
    ui->textEdit_2->setText(valueInHex);
}


/**
 * @brief myClient::WriteMessageC05ToClientForm Метод формирования сообщения С 05 для рассылки в железо (визуализация на клиенте).
 */
void myClient::WriteMessageC05ToClientForm()
{
    //Формируется универсальное сообщение, идентичное сообщению на сервере.
    bool ok;
    unsigned short* packet;
    packet = new unsigned short;
    QString valueInHex="";
    valueInHex=valueInHex + QString("0x%1").arg(C05_MESSAGE)+ "\n";
    packet[0] = static_cast<unsigned short>(((ui->lineEdit_7->text().toUShort(&ok,16)) << 12) | ((ui->lineEdit_8->text().toUShort(&ok,16)) << 4) | (ui->lineEdit_9->text().toUShort(&ok,16)));//Первое слово - адрес 1-го уровня.
    packet[1] = static_cast<unsigned short>((1 << 12) | (ui->lineEdit_10->text().toUShort(&ok,16)));//Второе слово - адрес 2-го уровня.
    int lengthPacket = 6;//Длина пакета.
    packet[2] = ui->lineEdit_11->text().toUShort(&ok,16);//Третье слово - размер данных.
    packet[3] = ui->lineEdit_12->text().toUShort(&ok,16);//Четвёртое слово - ID сообщения.
    packet[4] = 0x0000;//Пятое слово - резерв.
    packet[5] = CRC16(reinterpret_cast<unsigned char*>(packet), static_cast<unsigned short>((lengthPacket * 2) - 2));//Шестое слово - CRC.
    //Визуализация сообщения C05 в поле textEdit_4 вкладки Tab_2.
    for(int i=0; i < lengthPacket; i++) {
        valueInHex = valueInHex + QString("0x%1").arg(packet[i],4,16,QChar('0')).toUpper() + "\n";
    }
    ui->textEdit_4->setText(valueInHex);
}

/**
 * @brief myClient::MessageC03FromClientToServer Метод формирования шаблона сообщения С03 для передачи по TCP от клиента к серверу.
 * @param outPacketC03 - сообщение С03 для передачи по ТСР.
 */
void myClient::MessageC03FromClientToServer(QByteArray& outPacketC03)
{
    QString data = ui->textEdit->toPlainText();
    QStringList strList = data.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    unsigned short lengthData = static_cast<unsigned short>(strList.length());
    outPacketC03 ="";
    outPacketC03.append(QString("0x%1").arg(C03_MESSAGE,4,16,QChar('0')));
    outPacketC03.append("\n");
    outPacketC03.append(ui->lineEdit->text()+"\n");
    outPacketC03.append(ui->lineEdit_2->text()+"\n");
    outPacketC03.append(ui->lineEdit_3->text()+"\n");
    outPacketC03.append(ui->lineEdit_4->text()+"\n");
    outPacketC03.append(ui->lineEdit_5->text()+"\n");
    outPacketC03.append(ui->lineEdit_6->text()+"\n");
    for (int i = 0; i < lengthData; i++) {
        outPacketC03.append(strList[i]+"\n");
    }
}


/**
 * @brief myClient::MessageC05FromClientToServer Метод формирования шаблона сообщения С05 для передачи по TCP от клиента к серверу.
 * @param outPacketC03 - сообщение С05 для передачи по ТСР.
 */
void myClient::MessageC05FromClientToServer(QByteArray& outPacketC05)
{
     outPacketC05 ="";
     outPacketC05.append(QString("0x%1").arg(C05_MESSAGE,4,16,QChar('0')));
     outPacketC05.append("\n");
     outPacketC05.append(ui->lineEdit_7->text()+"\n");
     outPacketC05.append(ui->lineEdit_8->text()+"\n");
     outPacketC05.append(ui->lineEdit_9->text()+"\n");
     outPacketC05.append(ui->lineEdit_10->text()+"\n");
     outPacketC05.append(ui->lineEdit_11->text()+"\n");
     outPacketC05.append(ui->lineEdit_12->text()+"\n");
}

/**
 * @brief myClient::ReadHeadMessage Метод определения типа сообщения.
 * @param inMessage - входное сообщение.
 * @return - тип сообщения.
 */
int myClient::ReadHeadMessage(QByteArray inMessage)
{
    QByteArray arrNumMess;
    int numMes;
    bool ok;
    arrNumMess = inMessage.mid(2,1);
    numMes = arrNumMess.toInt(&ok,16);
    return numMes;
}
/**
 * @brief myClient::ShowStringMessage Метод визуализации текстового сообщения в строке состояния.
 * @param arrayStringMessage - сообщение для вывода в строке состояния.
 */
void myClient::ShowStringMessage(QByteArray arrayStringMessage)
{
    QByteArray arrStr = arrayStringMessage.mid(3);
    statusBar()->setStyleSheet("color:green");
    statusBar()->showMessage(time.toString() + "  " + arrStr);
}
/**
 * @brief myClient::ShowErrorMessage Метод визуализации сообщения - ошибки в строке состояния.
 * @param arrayErrorMessage -  сообщение-ошибка для вывода в строке состояния.
 */
void myClient::ShowErrorMessage(QByteArray arrayErrorMessage)
{
    QByteArray arrErr = arrayErrorMessage.mid(3);
    statusBar()->setStyleSheet("color: red");
    statusBar()->showMessage(time.toString() + "  " + arrErr);
}

// Слот обработки ошибок сокета.
void myClient::slotError(QAbstractSocket::SocketError error)
{
    QString servStr;
    if (server1Connection) servStr = "Ошибка Сервера 2: ";
    else servStr = "Ошибка Сервера 1: ";
    QString strError =
        servStr + (error == QAbstractSocket::HostNotFoundError ?
                     "Сервер не найден." :
                     error == QAbstractSocket::RemoteHostClosedError ?
                     "Сервер закрыт." :
                     error == QAbstractSocket::ConnectionRefusedError ?
                     "В соединении отказано." :
                     QString(localSocket->errorString()));
        statusBar()->setStyleSheet("color: Red");
        statusBar()->showMessage(strError);
        statusBar()->setStyleSheet("color: Black");
        ui->TestBFDNTextEdit->append(strError);
}

// Слот передачи информации на сервер.
void myClient::slotSendMessageC03ToServer()
{
    //Блок для передачи формируется аналогично тому, как это делается на сервере.
    //Поскольку заранее размер блока неизвестен (параметр string может быть любой длины),
    //вначале создаём объект array класса QByteArray.
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);
    QByteArray packetC03;//Переменная для хранения передаваемого сообщения С03.
    MessageC03FromClientToServer(packetC03);//, Формируем сообщение С03 для передачи по TCP от клиента к серверу.
    WriteMessageC03ToClientForm();//Отображаем переданное сообщение С03 на экране.
    out<< quint64(0)<< packetC03;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени С03.

    ui->textEdit_3->clear();
    msg_t outMsg = msg_t();
    int res = hrdwrNet.ReadFromSocket(outMsg, 0, 3000);
    if (!res) {
        outMsg.ShowMesTextEditMas(ui->textEdit_3);
        return;
    }
}

// Слот передачи информации на сервер.
void myClient::slotSendMessageC05ToServer()
{
    //Блок для передачи формируется аналогично тому, как это делается на сервере.
    //Поскольку заранее размер блока неизвестен (параметр string может быть любой длины),
    //вначале создаём объект array класса QByteArray.
    QByteArray arrayBlock;
    //На его основе создаём выходной поток.
    QDataStream out(&arrayBlock, QIODevice::WriteOnly);
    //Устанавливаем версию сериализации данных потока.
    out.setVersion(QDataStream::Qt_5_1);

    QByteArray packetC05;//Переменная для хранения передаваемого сообщения С05.
    MessageC05FromClientToServer(packetC05);//, Формируем сообщение С05 для передачи по TCP от клиента к серверу.
    WriteMessageC05ToClientForm();//Отображаем переданное сообщение С05 на экране.
    out<< quint64(0)<< packetC05;//Записываем сообщение в поток.
    out.device()->seek(0);
    out << quint64(arrayBlock.size() - sizeof(quint64));
    localSocket->write(arrayBlock);//Передаем сообщени С05.

    ui->textEdit_5->clear();
    msg_t outMsg = msg_t();
    int res = hrdwrNet.ReadFromSocket(outMsg, 1, 3000);
    if (!res) {
        outMsg.ShowMesTextEditMas(ui->textEdit_5);
        return;
    }
}

/**
 * @brief myClient::slotIPConnected Слот кнопки для подключения двух серверов
 */
void myClient::slotIPConnected()
{
    // коннект 1 сервера
    QString hostName(ui->lineIPAdress->text());
    nPort = ui->lineIPAdress_2->text().toUInt();
    localSocket = new QTcpSocket(this);//Инициализируем сокет для текущего ip-адреса. Для локальной системы - "127.0.0.1".
    localSocket->connectToHost(hostName, nPort);
    if (localSocket->waitForConnected(3000))
        slotConnected();
    QDataStream in(localSocket);
    in.setVersion(QDataStream::Qt_5_1); //Всегда необходимо проверять номер релиза!!!!Должны совпадать на сервере и клиенте!!!!
    while(localSocket->bytesAvailable() < (int)sizeof(quint64))
    {
        localSocket->waitForReadyRead(3000);
        break;
    }
    in >> nextBlockSize;
    while(localSocket->bytesAvailable() < nextBlockSize)
    {
        localSocket->waitForReadyRead(3000);
        return;
    }
    in>>arrayMessageServer;//Записываем сообщение от сервера в массив
    if (arrayMessageServer != ""){
        QList <QByteArray> qBaList = arrayMessageServer.split('\n');
        ui->TestBFDNTextEdit->append("Сервер 1:" + qBaList[1]);
    }
    else
        ui->TestBFDNTextEdit->append("Сервер 1 недоступен");
    // коннект 2 сервера
    server1Connection = 1;
    QString hostName_2(ui->lineIPAdress_4->text());
    nPort_2 = ui->lineIPAdress_3->text().toUInt();
    localSocket_2 = new QTcpSocket(this);//Инициализируем сокет для текущего ip-адреса. Для локальной системы - "127.0.0.1".
    localSocket_2->connectToHost(hostName_2, nPort_2);
    if (localSocket_2->waitForConnected(3000))
        slotConnected();
    QDataStream in_2(localSocket_2);
    in_2.setVersion(QDataStream::Qt_5_1); //Всегда необходимо проверять номер релиза!!!!Должны совпадать на сервере и клиенте!!!!
    while(localSocket_2->bytesAvailable() < (int)sizeof(quint64))
    {
        localSocket_2->waitForReadyRead(3000);
        break;
    }
    in_2 >> nextBlockSize_2;
    while(localSocket_2->bytesAvailable() < nextBlockSize_2)
    {
        localSocket_2->waitForReadyRead(3000);
        return;
    }
    in_2>>arrayMessageServer;//Записываем сообщение от сервера в массив
    if (arrayMessageServer != ""){
        if (server1Connection == 1){
            QList <QByteArray> qBaList = arrayMessageServer.split('\n');
            ui->TestBFDNTextEdit->append("Сервер 2:" + qBaList[1]);
        }
        else
            ui->TestBFDNTextEdit->append("Сервер 2 недоступен");
    }
    hrdwrNet.InitHrdwrFromUIl(UKRl, localSocket, localSocket_2);
}

// Слот обработки сигнала соединения с сервером
void myClient::slotConnected()
{
    if (server1Connection == 1)
        statusBar()->showMessage("Получил подключённый сигнал.");
}

// Слоты очистки форм по нажатию клавиши.
void myClient::on_pushButton_3_clicked()
{
   ui->textEdit_2->clear();
   ui->textEdit_3->clear();
}

void myClient::on_pushButton_4_clicked()
{
    ui->textEdit_4->clear();
    ui->textEdit_5->clear();
}

void myClient::ShowRes(QString func)
{
    ui->TestBFDNTextEdit->setFontPointSize(14);
    ui->TestBFDNTextEdit->setFontWeight(QFont::Bold);
    ui->TestBFDNTextEdit->append("      " + func);
    ui->TestBFDNTextEdit->repaint();
    ui->TestBFDNTextEdit->setFontPointSize(10);
    ui->TestBFDNTextEdit->setFontWeight(QFont::Normal);
}

void myClient::ShowRes(QString func, int call)
{
    QTextEdit *tE;
    if (call == 0){
        tE = ui->textEdit_3;
        tE->clear();
    }
    if (call == 1){
        tE = ui->textEdit_5;
        tE->clear();
    }
    if (call == 2)
        tE = ui->TestBFDNTextEdit;
    tE->setFontPointSize(14);
    tE->setFontWeight(QFont::ExtraBold);
    tE->append("      " + func);
    tE->setFontPointSize(10);
    tE->setFontWeight(QFont::Normal);
    tE->repaint();
}

void myClient::ShowMesCl(msg_t msg)
{
    if (ShowMess)
        msg.ShowMesTextEdit(ui->TestBFDNTextEdit);
//    ui->TestBFDNTextEdit->repaint();
}

void myClient::TabWChange(int newTab)
{
    if ((newTab == 4) && (newTab != curTEIndex))
    {
        QLayout *la2 = ui->tabWidget->widget(newTab-1)->layout();
        la2->removeWidget(ui->tabWidget->widget(newTab-1));
        delete la2;
        QGridLayout * la = new QGridLayout();
        la->setColumnStretch(0, 200);
        la->setColumnStretch(1, 250);
        la->addLayout(ui->verticalLayout_3, 0, 0);
        la->addWidget(ui->TestBFDNTextEdit, 0, 1);
        ui->tabWidget->widget(newTab)->setLayout(la);
        curTEIndex = 4;
    }
    if ((newTab == 3)&&(newTab != curTEIndex))
    {
        QLayout *la2 = ui->tabWidget->widget(newTab+1)->layout();
        la2->removeWidget(ui->tabWidget->widget(newTab+1));
        delete la2;
        QGridLayout * la = new QGridLayout();
        la->setColumnStretch(0, 200);
        la->setColumnStretch(1, 250);
        la->addLayout(ui->tabWidget->widget(newTab)->layout(),0,0);
        la->addWidget(ui->TestBFDNTextEdit, 0, 1);
        ui->tabWidget->widget(newTab)->setLayout(la);
        curTEIndex = 3;
    }    
}

void myClient::SlNumCycle(int i)
{
    ui->lineEdit_14->setText(QString::number(i));
    ui->lineEdit_14->repaint();
}

void myClient::SlotTextChangedWFile(QString str)
{
    hrdwrNet.setWFileName(str);
}

void myClient::SlotTextChangedFileList(QString str)
{
    hrdwrNet.setMiBlFn(str);
}
void myClient::SlotTextChangedFileList_2(QString str)
{
    hrdwrNet.setMiBlFn_21(str);
}
void myClient::SlotTextChangedFileList_3(QString str)
{
    hrdwrNet.SetTestFolder(hrdwrNet.StandartTestFolder +  str);
    hrdwrNet.setWFileName1("/Shift_2/W_DN/");
}


void myClient::SlotToggRadioButton(bool)
{
    hrdwrNet.SetTrapsParIn(ui->radioButton->isChecked());
}

int myClient::getGroupCheck(){
    if (ui->radioButton_3->isChecked()) return 0;
    if (ui->radioButton_4->isChecked()) return 1;
    if (ui->radioButton_5->isChecked()) return 2;
    if (ui->radioButton_6->isChecked()) return 3;
    if (ui->radioButton_7->isChecked()) return 4;
}

void myClient::SlotToggGroupRadioButton(bool)
{
    hrdwrNet.SetTrapsParIn(getGroupCheck());
}

void myClient::SlotTextChangedNumFPGATrap(QString str)
{
    hrdwrNet.SetTrapsParNFPGA(str);
}
void myClient::SlotToggledChB_3_2(bool chb)
{
    hrdwrNet.SetVertHorOpticCabel(ui->checkBox_2->isChecked(), ui->checkBox_3->isChecked());
}
