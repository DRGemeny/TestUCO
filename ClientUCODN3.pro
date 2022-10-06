#-------------------------------------------------
#
# Project created by QtCreator 2020-07-15T11:56:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientUCODN3
TEMPLATE = app

CONFIG += c++11 debug_and_releas


SOURCES += main.cpp\
        myclient.cpp \
    hrdwrnet.cpp \
    loghrd1.cpp \
    msg_t.cpp \
    testmacp.cpp \
    libhrdwr.cpp \
    testUCODN.cpp

HEADERS  += myclient.h \
    hrdwrnet.h \
    loghrd1.h \
    msg_t.h \
    TimTest_01_cmn.h \
    libhrdwr.h

FORMS    += myclient.ui

LIBS += -ldl
