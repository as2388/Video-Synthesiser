#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "qqueuetest.h"
#include "qwriter.h"
#include "qreader.h"
#include "timertester.h"

QWriter writer;
QReader reader;
timertester timerTest;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QObject::connect(&writer, SIGNAL(postNewData(int)), &reader, SLOT(receiveNewData(int)), Qt::QueuedConnection);

//    qDebug() << reader.thread();
//    qDebug() << writer.thread();

    //reader.start();
    //writer.start();

    //timerTest.begin();

    return a.exec();
}
