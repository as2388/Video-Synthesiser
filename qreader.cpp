#include "qreader.h"
#include <QQueue>
#include <QDebug>
#include <QThread>

QQueue<int> queue;
const int queueSizeLimit = 50;

QReader::QReader(QObject *parent) : QThread()
{

}

void QReader::receiveNewData(int newData) {
    if (queue.size() < queueSizeLimit) {
        queue.enqueue(newData);
        qDebug() << "Added new data: " << newData;
    } else {
        qDebug() << "New data rejected (queue full) " << newData;
    }
}

void QReader::run() {
    while (true) {
    if (!queue.isEmpty()) {
        qDebug() << "Dequeued: " << queue.dequeue();
    }
    }
}
