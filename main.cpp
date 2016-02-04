#include "mainwindow.h"
#include <QApplication>

#include "timertester.h"
#include "SonicPiAmplitudeExample.h"
#include <Evaluation/L2Eval.h>

timertester timerTest;

//boost::lockfree::queue<int> boostQueue(128);
//BoostWriter bWriter(&boostQueue);
//BoostReader bReader(&boostQueue);
QThread* ampThread = new QThread();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setBaseSize(QSize(800, 640));

    // Create and start the amplitude data generator
    SonicPiAmplitudeExample* ampGen = new SonicPiAmplitudeExample();
    ampGen->moveToThread(ampThread);

    MainWindow::connect(ampThread, SIGNAL(started()), ampGen, SLOT(run()));
    MainWindow::connect(ampGen, &SonicPiAmplitudeExample::amplitudeUpdate,
                        &w, &MainWindow::updateAmplitude
    );
    ampThread->start();

    w.show();

    //L2Eval().timeEverything();

    //bWriter.start();
    //bReader.start();

    return a.exec();
}
