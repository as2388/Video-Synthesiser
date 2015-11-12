#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T15:29:00
#
#-------------------------------------------------
macx {
    #QMAKE_CXXFLAGS += -std=c++11

    # Include Boost
    _BOOST_PATH = /usr/local/Cellar/boost/1.58.0
    INCLUDEPATH += "$${_BOOST_PATH}/include/"
    LIBS += -L$${_BOOST_PATH}/lib
    LIBS += -lboost_chrono -lboost_system
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tutorial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timertester.cpp \
    boostwriter.cpp \
    boostreader.cpp

HEADERS  += mainwindow.h \
    timertester.h \
    boostwriter.h \
    boostreader.h

FORMS    += mainwindow.ui

