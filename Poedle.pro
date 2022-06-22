#-------------------------------------------------
#
# Project created by QtCreator 2022-05-26T22:30:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Poedle
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    BaseTrie.h

FORMS    += widget.ui
CONFIGS +=c++11

RESOURCES += \
    res.qrc
CONFIG +=c++11

win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}
