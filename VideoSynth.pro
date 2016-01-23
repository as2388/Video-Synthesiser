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
    Synthesiser/Unit.cpp \
    Synthesiser/Synth.cpp \
    World.cpp \
    Synthesiser/Units/ImageUnits.cpp \
    Synthesiser/Units/FloatUnits.cpp \
    Graph/Graph.cpp \
    Synthesiser/SampleSynths/FadingSquares.cpp \
    Synthesiser/SampleSynths/Kaleidoscope.cpp \
    Evaluation/UnitEvaluator.cpp

HEADERS  += mainwindow.h \
    timertester.h \
    Synthesiser/Unit.h \
    Synthesiser/Synth.h \
    World.h \
    Synthesiser/Units/ImageUnits.h \
    Synthesiser/Units/FloatUnits.h \
    Graph/Graph.h \
    Synthesiser/SampleSynths/FadingSquares.h \
    Synthesiser/SampleSynths/Kaleidoscope.h \
    Evaluation/UnitEvaluator.h

FORMS    += mainwindow.ui

