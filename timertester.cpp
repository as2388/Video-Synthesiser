#include "timertester.h"
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QFile>

int virtualTime = 0;
QTime stopwatch;

QString filename="/Users/Alexander/Documents/qtimerdata.csv";
QFile file(filename);
QTextStream stream(&file);

timertester::timertester(QObject *parent) : QObject(parent)
{

}

void timertester::begin() {
    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << "file open";
    } else {
        qDebug() << "failed to open file";
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerFire()));
    timer->start(100);
    stopwatch.start();
}

void timertester::timerFire() {
    virtualTime += 100;
    stream << virtualTime << ", " << stopwatch.elapsed() << ", " << stopwatch.elapsed() - virtualTime << endl;
    qDebug() << virtualTime << ", " << stopwatch.elapsed() << ", " << stopwatch.elapsed() - virtualTime;
}
