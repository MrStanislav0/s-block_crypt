#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T16:36:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewPro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fun.cpp \
    m.cpp \
    Sfiles.cpp

HEADERS  += mainwindow.h \
    fun.h \
    Sfiles.h

FORMS    += mainwindow.ui
QMAKE_LFLAGS_RELEASE += -static -static-libgcc
