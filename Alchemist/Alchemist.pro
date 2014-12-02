#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T16:11:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Alchemist
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    asharefun.cpp

HEADERS  += mainwindow.h \
    AStruct.h \
    asharefun.h

FORMS    += mainwindow.ui

CONFIG +=console
#QT += testlib

win32 {
    INCLUDEPATH += $$PWD/lib/Ctp/windows
    INCLUDEPATH += $$PWD/../actor
    INCLUDEPATH += $$PWD/../dealer
    INCLUDEPATH += $$PWD/../recorder
    LIBS += -L$$PWD/lib/Ctp/windows/tr -lthosttraderapi
    LIBS += -L$$PWD/lib/Ctp/windows/md/ -lthostmduserapi
    DEPENDPATH += $$PWD/lib/Ctp/windows

    win32:CONFIG(debug, debug|release):LIBS += -L$$PWD/../bin/build-recorder-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug/ -lrecorder
    win32:CONFIG(debug, debug|release):LIBS += -L$$PWD/../bin/build-dealer-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug/ -ldealer
    win32:CONFIG(debug, debug|release):LIBS += -L$$PWD/../bin/build-actor-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug/ -lactor

    win32:CONFIG(release, debug|release):LIBS += -L$$PWD/../bin/build-recorder-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/release/ -lrecorder
    win32:CONFIG(release, debug|release):LIBS += -L$$PWD/../bin/build-dealer-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/release/ -ldealer
    win32:CONFIG(release, debug|release):LIBS += -L$$PWD/../bin/build-actor-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/release/ -lactor

   # INCLUDEPATH += $$PWD/../TradeLib/build-TradeLib-Desktop_Qt_5_3_MSVC2012_OpenGL_32bit-Debug/debug
   # DEPENDPATH += $$PWD/../TradeLib/build-TradeLib-Desktop_Qt_5_3_MSVC2012_OpenGL_32bit-Debug/debug

} unix {
    INCLUDEPATH += $$PWD/inc/Ctp/linux
    INCLUDEPATH += $$PWD/../actor
    INCLUDEPATH += $$PWD/../dealer
    INCLUDEPATH += $$PWD/../recorder
    LIBS += -L$$PWD/lib/Ctp/linux/tr/ -lthosttraderapi
    LIBS += -L$$PWD/lib/Ctp/linux/md/ -lthostmduserapi
    DEPENDPATH += $$PWD/lib/Ctp/linux

    LIBS += -L$$PWD/../bin/build-recorder-Desktop-Debug/ -lrecorder
    LIBS += -L$$PWD/../bin/build-dealer-Desktop-Debug/ -ldealer
    LIBS += -L$$PWD/../bin/build-actor-Desktop-Debug/ -lactor

}
