#include "mainwindow.h"
#include <QApplication>

#include "timertester.h"
#include <Evaluation/L2Eval.h>

timertester timerTest;

//boost::lockfree::queue<int> boostQueue(128);
//BoostWriter bWriter(&boostQueue);
//BoostReader bReader(&boostQueue);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    //w.setBaseSize(QSize(800, 840));
    //w.show();

    L2Eval().timeEverything();

    //UnitEvaluator().evaluateRectangle();
    //UnitEvaluator().evaluateSymm8();

    //bWriter.start();
    //bReader.start();

    //timerTest.begin();

    return a.exec();
}
