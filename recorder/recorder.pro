#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T15:50:08
#
#-------------------------------------------------

QT       += core    #@brief qt内核包含
QT       += gui
QT       += sql

TARGET = recorder
TEMPLATE = lib

DEFINES += RECORDER_LIBRARY

SOURCES += recorder.cpp \
    cmysql_api.cpp \
    ctpmdspi.cpp \
    ../Alchemist/asharefun.cpp \
    chstimer.cpp

HEADERS += recorder.h\
        recorder_global.h \
    cmysql_api.h \
    ../Alchemist/asharefun.h \
    ctpmdspi.h \
    chstimer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    INCLUDEPATH += $$PWD/MySQL
    #LIBS += C:\Program Files\MySQL\MySQL Connector C++ 1.1.4\lib\opt -lmysqlcppconn
    #LIBS += -L$$PWD/MySQL/lib/ -lmysqlclient
    LIBS += -L$$PWD/../Alchemist/lib/Ctp/windows/md/ -lthostmduserapi
} unix {
    INCLUDEPATH += $$PWD/MySQL

    INCLUDEPATH += $$PWD/../../usr/lib/x86_64-linux-gnu
    DEPENDPATH += $$PWD/../../usr/lib/x86_64-linux-gnu

    LIBS += -L$$PWD/../Alchemist/lib/Ctp/linux/md/ -lthostmduserapi
#    LIBS += -L$$PWD/api/risk/lib/ -lriskuserapi
    #LIBS += -L$$PWD/CTP/api/trade/linux64/lib/ -lthostmduserapi -lthosttraderapi
    #QMAKE_LFLAGS += -pthread
    LIBS += -L$$PWD/../../usr/lib/x86_64-linux-gnu/ -lmysqlclient
    #PRE_TARGETDEPS += $$PWD/../../usr/lib/libmysqlcppconn.a
    #PRE_TARGETDEPS += $$PWD/../../usr/lib/x86_64-linux-gnu/libmysqlclient.a
}
