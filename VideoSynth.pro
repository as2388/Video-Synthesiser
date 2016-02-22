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

QMAKE_CXXFLAGS += -std=c++11
_BOOST_PATH = /usr/local
INCLUDEPATH += "$${_BOOST_PATH}/include/"
INCLUDEPATH += "$${_BOOST_PATH}/libs/"
#LIBS += -L$${_BOOST_PATH}/lib/
#LIBS += -lboost_chrono -lboost_system -lboost_atomic

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoSynthApp
TEMPLATE = app

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O3


SOURCES += main.cpp\
        mainwindow.cpp \
    timertester.cpp \
    Synthesiser/Unit.cpp \
    Synthesiser/Synth.cpp \
    World/World.cpp \
    World/ImagePool.cpp \
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
    World/World.h \
    World/ImagePool.h \
    Synthesiser/Units/ImageUnits.h \
    Synthesiser/Units/FloatUnits.h \
    Graph/Graph.h \
    Synthesiser/SampleSynths/FadingSquares.h \
    Synthesiser/SampleSynths/Kaleidoscope.h \
    Evaluation/UnitEvaluator.h \
    Evaluation/L2Eval.h

FORMS    += mainwindow.ui

