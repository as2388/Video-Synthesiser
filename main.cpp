#include "mainwindow.h"
#include <QApplication>

#include "timertester.h"
#include "ImageGenerator.h"
#include <Evaluation/FinalEvaluator.h>

timertester timerTest;

boost::lockfree::queue<QImage*> boostQueue(5);
QThread* genThread = new QThread();
bool evaluationMode = false;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!evaluationMode) {
        ImageGenerator *ig = new ImageGenerator;
        ig->setQueue(&boostQueue);
        ig->moveToThread(genThread);
        MainWindow::connect(genThread, SIGNAL(started()), ig, SLOT(run()));

        MainWindow w;
        w.setQueue(&boostQueue);
        w.setWorld(ig->world);
        w.setBaseSize(QSize(800, 608));
        w.show();

        genThread->start(QThread::TimeCriticalPriority);
    } else {
        QThread* evalThread = new QThread();
        FinalEvaluator* eval = new FinalEvaluator();
        eval->moveToThread(evalThread);
        MainWindow::connect(evalThread, SIGNAL(started()), eval, SLOT(evaluateEverything()));
        evalThread->start(QThread::TimeCriticalPriority);
    }

    return a.exec();
}
