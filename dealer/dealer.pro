#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T15:51:45
#
#-------------------------------------------------

#QT       -= core gui
QT       += core gui

TARGET = dealer
TEMPLATE = lib

DEFINES += DEALER_LIBRARY

SOURCES += dealer.cpp \
    altraderspi.cpp \
    ../Alchemist/asharefun.cpp

HEADERS += dealer.h\
        dealer_global.h \
    altraderspi.h \
    ../Alchemist/asharefun.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32 {
    INCLUDEPATH += $$PWD/../Alchemist/inc/Ctp/windows
    INCLUDEPATH += $$PWD/../Alchemist
    LIBS += -L$$PWD/../Alchemist/lib/Ctp/windows/tr -lthosttraderapi
#    LIBS += -L$$PWD/lib/Ctp/windows/md/ -lthostmduserapi
    DEPENDPATH += $$PWD/../Alchemist/lib/Ctp/windows

} unix {
    INCLUDEPATH += $$PWD/inc/Ctp/linux
    INCLUDEPATH += $$PWD/../Alchemist

    LIBS += -L$$PWD/../Alchemist/lib/Ctp/linux/tr -lthosttraderapi
    DEPENDPATH += $$PWD/../Alchemist/lib/Ctp/linux

    QMAKE_LFLAGS += -pthread


}

