cmake_minimum_required(VERSION 3.3)
project(VideoSynth)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt5/5.3.1/")
set(CMAKE_CXX_FLAGS "-O3")

set(SOURCE_FILES
        boostreader.cpp
        boostreader.h
        boostwriter.cpp
        boostwriter.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        timertester.cpp
        timertester.h
        ui_mainwindow.h
        ui_mainwindow.cpp
        Synthesiser/Unit.cpp
        Synthesiser/Unit.h
        Synthesiser/Synth.cpp
        Synthesiser/Synth.h
        World/World.cpp
        World/World.h
        Synthesiser/Units/UnitMacros.h
        Synthesiser/Units/ImageUnits.cpp
        Synthesiser/Units/ImageUnits.h
        Synthesiser/Units/FloatUnits.cpp
        Synthesiser/Units/FloatUnits.h
        Graph/Graph.cpp
        Graph/Graph.h
        Synthesiser/SampleSynths/FadingSquares.cpp
        Synthesiser/SampleSynths/FadingSquares.h
        Synthesiser/SampleSynths/Kaleidoscope.cpp
        Synthesiser/SampleSynths/Kaleidoscope.h
        Evaluation/UnitEvaluator.cpp
        Evaluation/UnitEvaluator.h
        Evaluation/L2Eval.h UserGraphics/UserGraphics.h World/ImagePool.cpp World/ImagePool.h Synthesiser/SampleSynths/FadingCopier.cpp Synthesiser/SampleSynths/FadingCopier.h ImageGenerator.cpp ImageGenerator.h Evaluation/FinalEvaluator.h Synthesiser/SampleSynths/MovingSquare.cpp Synthesiser/SampleSynths/MovingSquare.h)

add_executable(VideoSynth ${SOURCE_FILES})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/alexander/Qt5.5.1/5.5/clang_64/lib/cmake")

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
qt5_use_modules(VideoSynth Core Widgets Gui)