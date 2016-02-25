#include "mainwindow.h"
#include <QApplication>

#include "timertester.h"
#include "ImageGenerator.h"
#include <Evaluation/L2Eval.h>

timertester timerTest;

boost::lockfree::queue<QImage*> boostQueue(5);
//BoostWriter bWriter(&boostQueue);
//BoostReader bReader(&boostQueue);
QThread* genThread = new QThread();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //qDebug() << qRgba(255, 255, 255, 127);
    //qDebug() << (qRgba(255, 255, 255, 127) & (~(0xFF << 24)));
    //qDebug() << ((qRgba(255, 255, 255, 127) & (~(0xFF << 24))) | (char) 255);

    //((*(outputLine + x)) & ~(0xFF)) | alpha;

    ImageGenerator *ig = new ImageGenerator;
    ig->setQueue(&boostQueue);
    ig->moveToThread(genThread);
    MainWindow::connect(genThread, SIGNAL(started()), ig, SLOT(run()));

    MainWindow w;
    w.setQueue(&boostQueue);
    w.setWorld(ig->world);
    w.setBaseSize(QSize(800, 640));
    w.show();

    genThread->start(QThread::TimeCriticalPriority);

    //L2Eval().timeEverything();

    //UnitEvaluator().evaluateRectangle();
    //UnitEvaluator().evaluateSymm8();

    //bWriter.start();
    //bReader.start();

    //timerTest.begin();

    return a.exec();
}
