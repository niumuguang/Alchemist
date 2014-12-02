#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T15:59:21
#
#-------------------------------------------------

QT       += widgets opengl sql xml

TARGET = actor
TEMPLATE = lib

DEFINES += ACTOR_LIBRARY

SOURCES += actor.cpp \
    dialogactor.cpp

HEADERS += actor.h\
        actor_global.h \
    dialogactor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    dialogactor.ui
