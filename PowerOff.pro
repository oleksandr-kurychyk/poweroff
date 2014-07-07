#-------------------------------------------------
#
# Project created by QtCreator 2013-08-23T21:35:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PowerOff
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgettimerlist.cpp \
    widgettimercpu.cpp \
    widgetpowerexec.cpp \
    widgetnetworktimer.cpp \
    widgetcurinf.cpp \
    comandsdialog.cpp \
    comandoperations.cpp

HEADERS  += mainwindow.h \
    widgettimerlist.h \
    widgettimercpu.h \
    widgetpowerexec.h \
    widgetnetworktimer.h \
    widgetcurinf.h \
    headers.h \
    net_func.h \
    comandoperations.h \
    comandsdialog.h

OTHER_FILES +=

FORMS += \
    comandsdialog.ui

RESOURCES += \
    resource.qrc
