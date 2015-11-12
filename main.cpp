#include "mainwindow.h"
#include <QApplication>

#include "boostwriter.h"
#include "boostreader.h"
#include "timertester.h"

timertester timerTest;

boost::lockfree::queue<int> boostQueue(128);
BoostWriter bWriter(&boostQueue);
BoostReader bReader(&boostQueue);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //bWriter.start();
    //bReader.start();

    //timerTest.begin();

    return a.exec();
}
