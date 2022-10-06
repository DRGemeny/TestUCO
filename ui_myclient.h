/********************************************************************************
** Form generated from reading UI file 'myclient.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLIENT_H
#define UI_MYCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myClient
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QTextEdit *textEdit;
    QLabel *label_9;
    QLabel *label_10;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QPushButton *pushButton_3;
    QWidget *tab_2;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QLabel *label_11;
    QLineEdit *lineEdit_8;
    QLabel *label_12;
    QLineEdit *lineEdit_9;
    QLabel *label_13;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLabel *label_14;
    QLineEdit *lineEdit_12;
    QLabel *label_15;
    QPushButton *pushButton_2;
    QLabel *label_17;
    QLabel *label_18;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_5;
    QPushButton *pushButton_4;
    QWidget *tab_4;
    QLineEdit *FileListEdit;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *FileListEdit_2;
    QLineEdit *FileListEdit_3;
    QLabel *label_25;
    QPushButton *IPConnect;
    QLineEdit *lineIPAdress_2;
    QLabel *IP_lable;
    QLabel *IP_lable_4;
    QLineEdit *lineIPAdress_3;
    QLineEdit *lineIPAdress;
    QLabel *IP_lable_2;
    QLabel *IP_lable_3;
    QLineEdit *lineIPAdress_4;
    QWidget *tab_5;
    QTextEdit *TestBFDNTextEdit;
    QPushButton *ClearTBTEButt;
    QPushButton *ResLVDSButt;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_7;
    QLineEdit *lineEditNumFPGATrap;
    QLabel *label_20;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *TestBFDNButt;
    QPushButton *TestBFDNButt_2;
    QPushButton *TestBFDNButt_3;
    QPushButton *TestBFDNButt_7;
    QPushButton *ReadTrapBFDNButt;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_21;
    QLineEdit *lineEditNumUKRTrap;
    QPushButton *TestMACP;
    QCheckBox *checkBox;
    QWidget *tab_7;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *ResLVDSBFDN2Butt;
    QPushButton *TestBFDNButt_8;
    QPushButton *TestBFDNButt_9;
    QPushButton *TestBFDNButt_11;
    QPushButton *ReadTrapBFDNButt_5;
    QPushButton *ClearTBTEButt_2;
    QPushButton *ResComputingPartBut;
    QPushButton *ReadBFDN2FPGA2But;
    QLineEdit *lineEdit_14;
    QLabel *label_22;
    QGroupBox *groupBox_4;
    QLineEdit *lineEditCycle;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *Test1DosMButt;
    QPushButton *Test2DosMButt;
    QPushButton *Test3DosMButt;
    QPushButton *Test4DosMButt;
    QPushButton *CycleStartButt;
    QGroupBox *groupBox_5;
    QRadioButton *radioButtonDN;
    QRadioButton *radioButtonCM;
    QPushButton *ReadTrapBFDNButt_4;
    QPushButton *ReadTrapBFDNButt_2;
    QPushButton *ReadTrapBFDNButt_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myClient)
    {
        if (myClient->objectName().isEmpty())
            myClient->setObjectName(QStringLiteral("myClient"));
        myClient->resize(1312, 750);
        centralWidget = new QWidget(myClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QFont font;
        font.setFamily(QStringLiteral("Arimo"));
        font.setPointSize(17);
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 251, 31));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 40, 241, 41));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 530, 271, 60));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(230, 250, 81, 31));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 251, 31));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 170, 251, 31));
        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 120, 241, 41));
        lineEdit_3 = new QLineEdit(tab);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(10, 200, 241, 41));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(280, 10, 251, 31));
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(280, 40, 241, 41));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(280, 90, 251, 31));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(280, 170, 251, 31));
        lineEdit_5 = new QLineEdit(tab);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(280, 120, 241, 41));
        lineEdit_6 = new QLineEdit(tab);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(280, 200, 241, 41));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(140, 280, 256, 221));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(620, 0, 211, 41));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(970, 0, 211, 41));
        textEdit_2 = new QTextEdit(tab);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(570, 50, 321, 511));
        textEdit_3 = new QTextEdit(tab);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(920, 50, 321, 511));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(780, 580, 251, 41));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 10, 241, 31));
        lineEdit_7 = new QLineEdit(tab_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(10, 40, 241, 41));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 90, 241, 31));
        lineEdit_8 = new QLineEdit(tab_2);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(10, 120, 241, 41));
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 170, 241, 31));
        lineEdit_9 = new QLineEdit(tab_2);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(10, 200, 241, 41));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(280, 10, 241, 31));
        lineEdit_10 = new QLineEdit(tab_2);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(280, 40, 241, 41));
        lineEdit_11 = new QLineEdit(tab_2);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(280, 120, 241, 41));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(280, 90, 241, 31));
        lineEdit_12 = new QLineEdit(tab_2);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(280, 200, 241, 41));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(280, 170, 251, 31));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 530, 271, 60));
        label_17 = new QLabel(tab_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(620, 0, 211, 41));
        label_18 = new QLabel(tab_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(970, 0, 211, 41));
        textEdit_4 = new QTextEdit(tab_2);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));
        textEdit_4->setGeometry(QRect(570, 50, 321, 511));
        textEdit_5 = new QTextEdit(tab_2);
        textEdit_5->setObjectName(QStringLiteral("textEdit_5"));
        textEdit_5->setGeometry(QRect(920, 50, 321, 511));
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(780, 580, 251, 41));
        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        FileListEdit = new QLineEdit(tab_4);
        FileListEdit->setObjectName(QStringLiteral("FileListEdit"));
        FileListEdit->setGeometry(QRect(10, 70, 451, 29));
        label_23 = new QLabel(tab_4);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 40, 161, 21));
        label_24 = new QLabel(tab_4);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(10, 120, 151, 21));
        FileListEdit_2 = new QLineEdit(tab_4);
        FileListEdit_2->setObjectName(QStringLiteral("FileListEdit_2"));
        FileListEdit_2->setGeometry(QRect(10, 150, 451, 29));
        FileListEdit_3 = new QLineEdit(tab_4);
        FileListEdit_3->setObjectName(QStringLiteral("FileListEdit_3"));
        FileListEdit_3->setGeometry(QRect(10, 220, 451, 29));
        label_25 = new QLabel(tab_4);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 190, 151, 21));
        IPConnect = new QPushButton(tab_4);
        IPConnect->setObjectName(QStringLiteral("IPConnect"));
        IPConnect->setGeometry(QRect(660, 210, 281, 41));
        lineIPAdress_2 = new QLineEdit(tab_4);
        lineIPAdress_2->setObjectName(QStringLiteral("lineIPAdress_2"));
        lineIPAdress_2->setGeometry(QRect(880, 70, 61, 29));
        IP_lable = new QLabel(tab_4);
        IP_lable->setObjectName(QStringLiteral("IP_lable"));
        IP_lable->setGeometry(QRect(660, 30, 101, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        IP_lable->setFont(font1);
        IP_lable->setFrameShadow(QFrame::Raised);
        IP_lable_4 = new QLabel(tab_4);
        IP_lable_4->setObjectName(QStringLiteral("IP_lable_4"));
        IP_lable_4->setGeometry(QRect(880, 110, 101, 41));
        IP_lable_4->setFont(font1);
        IP_lable_4->setFrameShadow(QFrame::Raised);
        lineIPAdress_3 = new QLineEdit(tab_4);
        lineIPAdress_3->setObjectName(QStringLiteral("lineIPAdress_3"));
        lineIPAdress_3->setGeometry(QRect(880, 150, 61, 29));
        lineIPAdress = new QLineEdit(tab_4);
        lineIPAdress->setObjectName(QStringLiteral("lineIPAdress"));
        lineIPAdress->setGeometry(QRect(660, 70, 201, 29));
        IP_lable_2 = new QLabel(tab_4);
        IP_lable_2->setObjectName(QStringLiteral("IP_lable_2"));
        IP_lable_2->setGeometry(QRect(880, 30, 101, 41));
        IP_lable_2->setFont(font1);
        IP_lable_2->setFrameShadow(QFrame::Raised);
        IP_lable_3 = new QLabel(tab_4);
        IP_lable_3->setObjectName(QStringLiteral("IP_lable_3"));
        IP_lable_3->setGeometry(QRect(660, 110, 101, 41));
        IP_lable_3->setFont(font1);
        IP_lable_3->setFrameShadow(QFrame::Raised);
        lineIPAdress_4 = new QLineEdit(tab_4);
        lineIPAdress_4->setObjectName(QStringLiteral("lineIPAdress_4"));
        lineIPAdress_4->setGeometry(QRect(660, 150, 201, 29));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        TestBFDNTextEdit = new QTextEdit(tab_5);
        TestBFDNTextEdit->setObjectName(QStringLiteral("TestBFDNTextEdit"));
        TestBFDNTextEdit->setGeometry(QRect(580, 60, 701, 511));
        QFont font2;
        font2.setFamily(QStringLiteral("Terminus"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        TestBFDNTextEdit->setFont(font2);
        ClearTBTEButt = new QPushButton(tab_5);
        ClearTBTEButt->setObjectName(QStringLiteral("ClearTBTEButt"));
        ClearTBTEButt->setGeometry(QRect(470, 60, 84, 31));
        ClearTBTEButt->setFont(font);
        ResLVDSButt = new QPushButton(tab_5);
        ResLVDSButt->setObjectName(QStringLiteral("ResLVDSButt"));
        ResLVDSButt->setGeometry(QRect(0, 140, 131, 31));
        ResLVDSButt->setFont(font);
        groupBox = new QGroupBox(tab_5);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 470, 151, 71));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(10, 10, 131, 20));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 40, 131, 20));
        groupBox_2 = new QGroupBox(tab_5);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 470, 141, 161));
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 70, 121, 20));
        radioButton_5->setChecked(false);
        radioButton_6 = new QRadioButton(groupBox_2);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(10, 100, 131, 20));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 40, 131, 20));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 10, 121, 20));
        radioButton_3->setChecked(false);
        radioButton_7 = new QRadioButton(groupBox_2);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(10, 130, 131, 20));
        lineEditNumFPGATrap = new QLineEdit(tab_5);
        lineEditNumFPGATrap->setObjectName(QStringLiteral("lineEditNumFPGATrap"));
        lineEditNumFPGATrap->setGeometry(QRect(300, 510, 161, 29));
        label_20 = new QLabel(tab_5);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(300, 475, 171, 31));
        layoutWidget = new QWidget(tab_5);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 180, 243, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TestBFDNButt = new QPushButton(layoutWidget);
        TestBFDNButt->setObjectName(QStringLiteral("TestBFDNButt"));
        TestBFDNButt->setFont(font);

        verticalLayout->addWidget(TestBFDNButt);

        TestBFDNButt_2 = new QPushButton(layoutWidget);
        TestBFDNButt_2->setObjectName(QStringLiteral("TestBFDNButt_2"));
        TestBFDNButt_2->setFont(font);

        verticalLayout->addWidget(TestBFDNButt_2);

        TestBFDNButt_3 = new QPushButton(layoutWidget);
        TestBFDNButt_3->setObjectName(QStringLiteral("TestBFDNButt_3"));
        TestBFDNButt_3->setFont(font);

        verticalLayout->addWidget(TestBFDNButt_3);

        TestBFDNButt_7 = new QPushButton(layoutWidget);
        TestBFDNButt_7->setObjectName(QStringLiteral("TestBFDNButt_7"));
        TestBFDNButt_7->setFont(font);

        verticalLayout->addWidget(TestBFDNButt_7);

        ReadTrapBFDNButt = new QPushButton(layoutWidget);
        ReadTrapBFDNButt->setObjectName(QStringLiteral("ReadTrapBFDNButt"));
        ReadTrapBFDNButt->setFont(font);

        verticalLayout->addWidget(ReadTrapBFDNButt);

        groupBox_3 = new QGroupBox(tab_5);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(250, 180, 281, 161));
        layoutWidget1 = new QWidget(groupBox_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 30, 251, 122));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget1);
        label_21->setObjectName(QStringLiteral("label_21"));

        verticalLayout_2->addWidget(label_21);

        lineEditNumUKRTrap = new QLineEdit(layoutWidget1);
        lineEditNumUKRTrap->setObjectName(QStringLiteral("lineEditNumUKRTrap"));

        verticalLayout_2->addWidget(lineEditNumUKRTrap);

        TestMACP = new QPushButton(layoutWidget1);
        TestMACP->setObjectName(QStringLiteral("TestMACP"));

        verticalLayout_2->addWidget(TestMACP);

        checkBox = new QCheckBox(tab_5);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(480, 510, 91, 20));
        tabWidget->addTab(tab_5, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        layoutWidget_2 = new QWidget(tab_7);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(30, 149, 248, 211));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ResLVDSBFDN2Butt = new QPushButton(layoutWidget_2);
        ResLVDSBFDN2Butt->setObjectName(QStringLiteral("ResLVDSBFDN2Butt"));

        verticalLayout_3->addWidget(ResLVDSBFDN2Butt);

        TestBFDNButt_8 = new QPushButton(layoutWidget_2);
        TestBFDNButt_8->setObjectName(QStringLiteral("TestBFDNButt_8"));
        TestBFDNButt_8->setFont(font);

        verticalLayout_3->addWidget(TestBFDNButt_8);

        TestBFDNButt_9 = new QPushButton(layoutWidget_2);
        TestBFDNButt_9->setObjectName(QStringLiteral("TestBFDNButt_9"));
        TestBFDNButt_9->setFont(font);

        verticalLayout_3->addWidget(TestBFDNButt_9);

        TestBFDNButt_11 = new QPushButton(layoutWidget_2);
        TestBFDNButt_11->setObjectName(QStringLiteral("TestBFDNButt_11"));
        TestBFDNButt_11->setFont(font);

        verticalLayout_3->addWidget(TestBFDNButt_11);

        ReadTrapBFDNButt_5 = new QPushButton(layoutWidget_2);
        ReadTrapBFDNButt_5->setObjectName(QStringLiteral("ReadTrapBFDNButt_5"));
        ReadTrapBFDNButt_5->setFont(font);

        verticalLayout_3->addWidget(ReadTrapBFDNButt_5);

        ClearTBTEButt_2 = new QPushButton(tab_7);
        ClearTBTEButt_2->setObjectName(QStringLiteral("ClearTBTEButt_2"));
        ClearTBTEButt_2->setGeometry(QRect(470, 60, 84, 31));
        ClearTBTEButt_2->setFont(font);
        ResComputingPartBut = new QPushButton(tab_7);
        ResComputingPartBut->setObjectName(QStringLiteral("ResComputingPartBut"));
        ResComputingPartBut->setGeometry(QRect(300, 150, 251, 37));
        ReadBFDN2FPGA2But = new QPushButton(tab_7);
        ReadBFDN2FPGA2But->setObjectName(QStringLiteral("ReadBFDN2FPGA2But"));
        ReadBFDN2FPGA2But->setGeometry(QRect(650, 290, 251, 41));
        lineEdit_14 = new QLineEdit(tab_7);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(472, 100, 81, 29));
        lineEdit_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_22 = new QLabel(tab_7);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(390, 104, 71, 21));
        groupBox_4 = new QGroupBox(tab_7);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(300, 190, 261, 341));
        lineEditCycle = new QLineEdit(groupBox_4);
        lineEditCycle->setObjectName(QStringLiteral("lineEditCycle"));
        lineEditCycle->setGeometry(QRect(10, 10, 241, 35));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditCycle->sizePolicy().hasHeightForWidth());
        lineEditCycle->setSizePolicy(sizePolicy);
        lineEditCycle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBox_3 = new QCheckBox(groupBox_4);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(10, 90, 71, 20));
        checkBox_2 = new QCheckBox(groupBox_4);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(10, 70, 71, 20));
        checkBox_4 = new QCheckBox(groupBox_4);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(10, 50, 101, 20));
        checkBox_4->setChecked(false);
        layoutWidget2 = new QWidget(groupBox_4);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 120, 241, 211));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        Test1DosMButt = new QPushButton(layoutWidget2);
        Test1DosMButt->setObjectName(QStringLiteral("Test1DosMButt"));

        verticalLayout_4->addWidget(Test1DosMButt);

        Test2DosMButt = new QPushButton(layoutWidget2);
        Test2DosMButt->setObjectName(QStringLiteral("Test2DosMButt"));

        verticalLayout_4->addWidget(Test2DosMButt);

        Test3DosMButt = new QPushButton(layoutWidget2);
        Test3DosMButt->setObjectName(QStringLiteral("Test3DosMButt"));

        verticalLayout_4->addWidget(Test3DosMButt);

        Test4DosMButt = new QPushButton(layoutWidget2);
        Test4DosMButt->setObjectName(QStringLiteral("Test4DosMButt"));

        verticalLayout_4->addWidget(Test4DosMButt);

        CycleStartButt = new QPushButton(layoutWidget2);
        CycleStartButt->setObjectName(QStringLiteral("CycleStartButt"));

        verticalLayout_4->addWidget(CycleStartButt);

        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(120, 50, 131, 61));
        radioButtonDN = new QRadioButton(groupBox_5);
        radioButtonDN->setObjectName(QStringLiteral("radioButtonDN"));
        radioButtonDN->setGeometry(QRect(10, 10, 131, 20));
        radioButtonDN->setChecked(true);
        radioButtonCM = new QRadioButton(groupBox_5);
        radioButtonCM->setObjectName(QStringLiteral("radioButtonCM"));
        radioButtonCM->setGeometry(QRect(10, 30, 131, 20));
        radioButtonCM->setToolTipDuration(1);
        radioButtonCM->setInputMethodHints(Qt::ImhNone);
        ReadTrapBFDNButt_4 = new QPushButton(tab_7);
        ReadTrapBFDNButt_4->setObjectName(QStringLiteral("ReadTrapBFDNButt_4"));
        ReadTrapBFDNButt_4->setGeometry(QRect(20, 60, 246, 37));
        ReadTrapBFDNButt_4->setFont(font);
        ReadTrapBFDNButt_2 = new QPushButton(tab_7);
        ReadTrapBFDNButt_2->setObjectName(QStringLiteral("ReadTrapBFDNButt_2"));
        ReadTrapBFDNButt_2->setGeometry(QRect(20, 20, 246, 37));
        ReadTrapBFDNButt_2->setFont(font);
        ReadTrapBFDNButt_3 = new QPushButton(tab_7);
        ReadTrapBFDNButt_3->setObjectName(QStringLiteral("ReadTrapBFDNButt_3"));
        ReadTrapBFDNButt_3->setGeometry(QRect(20, 40, 246, 37));
        ReadTrapBFDNButt_3->setFont(font);
        tabWidget->addTab(tab_7, QString());

        horizontalLayout->addWidget(tabWidget);

        myClient->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1312, 27));
        myClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myClient);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        myClient->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        myClient->setStatusBar(statusBar);

        retranslateUi(myClient);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(myClient);
    } // setupUi

    void retranslateUi(QMainWindow *myClient)
    {
        myClient->setWindowTitle(QApplication::translate("myClient", "myClient", nullptr));
        label->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 1-\320\263\320\276 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        pushButton->setText(QApplication::translate("myClient", "\320\237\320\276\321\201\320\273\320\260\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        label_7->setText(QApplication::translate("myClient", "DATA", nullptr));
        label_2->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 2-\320\263\320\276 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        label_3->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 3-\320\263\320\276 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        label_4->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260", nullptr));
        label_5->setText(QApplication::translate("myClient", "\320\224\320\273\320\270\320\275\320\260 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_6->setText(QApplication::translate("myClient", "ID \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_9->setText(QApplication::translate("myClient", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 \320\24103", nullptr));
        label_10->setText(QApplication::translate("myClient", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 \320\24104", nullptr));
        pushButton_3->setText(QApplication::translate("myClient", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\204\320\276\321\200\320\274\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("myClient", "C03-C04", nullptr));
        label_8->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 1-\320\263\320\276 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        label_11->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 2-\320\263\320\276 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        label_12->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 3-\320\263\320\276 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        label_13->setText(QApplication::translate("myClient", "\320\220\320\264\321\200\320\265\321\201 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260", nullptr));
        label_14->setText(QApplication::translate("myClient", "\320\224\320\273\320\270\320\275\320\260 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_15->setText(QApplication::translate("myClient", "ID \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        pushButton_2->setText(QApplication::translate("myClient", "\320\237\320\276\321\201\320\273\320\260\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        label_17->setText(QApplication::translate("myClient", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 \320\24105", nullptr));
        label_18->setText(QApplication::translate("myClient", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 \320\24106", nullptr));
        pushButton_4->setText(QApplication::translate("myClient", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\204\320\276\321\200\320\274\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("myClient", "\320\24105-C06", nullptr));
        label_23->setText(QApplication::translate("myClient", "Mibl File BFDN11", nullptr));
        label_24->setText(QApplication::translate("myClient", "Mibl File BFDN21", nullptr));
        label_25->setText(QApplication::translate("myClient", "Test Folder", nullptr));
        IPConnect->setText(QApplication::translate("myClient", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        IP_lable->setText(QApplication::translate("myClient", "IP-\320\260\320\264\321\200\320\265\321\201 1:", nullptr));
        IP_lable_4->setText(QApplication::translate("myClient", "\320\237\320\276\321\200\321\202 2", nullptr));
        IP_lable_2->setText(QApplication::translate("myClient", "\320\237\320\276\321\200\321\202 1", nullptr));
        IP_lable_3->setText(QApplication::translate("myClient", "IP-\320\260\320\264\321\200\320\265\321\201 2:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("myClient", "Setup", nullptr));
        TestBFDNTextEdit->setHtml(QApplication::translate("myClient", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Terminus'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        ClearTBTEButt->setText(QApplication::translate("myClient", "Clear", nullptr));
        ResLVDSButt->setText(QApplication::translate("myClient", "Reset LVDS", nullptr));
        groupBox->setTitle(QString());
        radioButton->setText(QApplication::translate("myClient", "MACP Dada", nullptr));
        radioButton_2->setText(QApplication::translate("myClient", "Resault Data", nullptr));
        groupBox_2->setTitle(QString());
        radioButton_5->setText(QApplication::translate("myClient", "Shift2 Data", nullptr));
        radioButton_6->setText(QApplication::translate("myClient", "Shift3 Data", nullptr));
        radioButton_4->setText(QApplication::translate("myClient", "Shift1 Data", nullptr));
        radioButton_3->setText(QApplication::translate("myClient", "Shift0 Data", nullptr));
        radioButton_7->setText(QApplication::translate("myClient", "Shift4 Data", nullptr));
        label_20->setText(QApplication::translate("myClient", "Number FPGA Trap", nullptr));
        TestBFDNButt->setText(QApplication::translate("myClient", "MACP", nullptr));
        TestBFDNButt_2->setText(QApplication::translate("myClient", "W", nullptr));
        TestBFDNButt_3->setText(QApplication::translate("myClient", "Load MiBl", nullptr));
        TestBFDNButt_7->setText(QApplication::translate("myClient", "Start GTS, Trap, TSek", nullptr));
        ReadTrapBFDNButt->setText(QApplication::translate("myClient", "Read Trap BFDN", nullptr));
        groupBox_3->setTitle(QApplication::translate("myClient", "TestMACP", nullptr));
        label_21->setText(QApplication::translate("myClient", "Number UKR Trap", nullptr));
        TestMACP->setText(QApplication::translate("myClient", "TestMACP", nullptr));
        checkBox->setText(QApplication::translate("myClient", "Test \"a\"", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("myClient", "TestBFDN2", nullptr));
        ResLVDSBFDN2Butt->setText(QApplication::translate("myClient", "Reset LVDS", nullptr));
        TestBFDNButt_8->setText(QApplication::translate("myClient", "MACP", nullptr));
        TestBFDNButt_9->setText(QApplication::translate("myClient", "W", nullptr));
        TestBFDNButt_11->setText(QApplication::translate("myClient", "Start GTS, Trap, TSek", nullptr));
        ReadTrapBFDNButt_5->setText(QApplication::translate("myClient", "Read Trap BRUS ", nullptr));
        ClearTBTEButt_2->setText(QApplication::translate("myClient", "Clear", nullptr));
        ResComputingPartBut->setText(QApplication::translate("myClient", "ResComputingPart", nullptr));
        ReadBFDN2FPGA2But->setText(QApplication::translate("myClient", "Read UKR BFDN2 FPGA2", nullptr));
        label_22->setText(QApplication::translate("myClient", "Itaration", nullptr));
        groupBox_4->setTitle(QString());
        lineEditCycle->setText(QApplication::translate("myClient", "1", nullptr));
        checkBox_3->setText(QApplication::translate("myClient", "Hor", nullptr));
        checkBox_2->setText(QApplication::translate("myClient", "Vert", nullptr));
        checkBox_4->setText(QApplication::translate("myClient", "FirstStart", nullptr));
        Test1DosMButt->setText(QApplication::translate("myClient", "Test_1", nullptr));
        Test2DosMButt->setText(QApplication::translate("myClient", "Test_2", nullptr));
        Test3DosMButt->setText(QApplication::translate("myClient", "Test_3", nullptr));
        Test4DosMButt->setText(QApplication::translate("myClient", "Test_4", nullptr));
        CycleStartButt->setText(QApplication::translate("myClient", "   Cycle Start   ", nullptr));
        groupBox_5->setTitle(QString());
        radioButtonDN->setText(QApplication::translate("myClient", "DN", nullptr));
#ifndef QT_NO_TOOLTIP
        radioButtonCM->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        radioButtonCM->setText(QApplication::translate("myClient", "CM", nullptr));
        ReadTrapBFDNButt_4->setText(QApplication::translate("myClient", "Read Trap FPGA3 BFDN2", nullptr));
        ReadTrapBFDNButt_2->setText(QApplication::translate("myClient", "Read Trap FPGA 1 BFDN2", nullptr));
        ReadTrapBFDNButt_3->setText(QApplication::translate("myClient", "Read Trap FPGA 2 BFDN2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("myClient", "TestUCODN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myClient: public Ui_myClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
