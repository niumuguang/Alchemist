#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T15:29:56
#
#-------------------------------------------------

QT       += sql xml

QT       -= gui

TARGET = wise
TEMPLATE = lib

DEFINES += WISE_LIBRARY

SOURCES += wise.cpp

HEADERS += wise.h\
        wise_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
