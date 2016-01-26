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

    //qDebug() << qRgba(255, 255, 255, 127);
    //qDebug() << (qRgba(255, 255, 255, 127) & (~(0xFF << 24)));
    //qDebug() << ((qRgba(255, 255, 255, 127) & (~(0xFF << 24))) | (char) 255);

    //((*(outputLine + x)) & ~(0xFF)) | alpha;

    MainWindow w;
    w.setBaseSize(QSize(800, 640));
    w.show();

    //L2Eval().timeEverything();

    //UnitEvaluator().evaluateRectangle();
    //UnitEvaluator().evaluateSymm8();

    //bWriter.start();
    //bReader.start();

    //timerTest.begin();

    return a.exec();
}
