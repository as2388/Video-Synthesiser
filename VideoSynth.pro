#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T15:29:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tutorial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qqueuetest.cpp \
    qreader.cpp \
    qwriter.cpp \
    timertester.cpp

HEADERS  += mainwindow.h \
    qqueuetest.h \
    qreader.h \
    qwriter.h \
    timertester.h

FORMS    += mainwindow.ui