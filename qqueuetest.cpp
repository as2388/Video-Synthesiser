#include "qqueuetest.h"
#include <QDebug>
#include <QQueue>

QQueueTest::QQueueTest()
{

}

void QQueueTest::run() {
    qDebug() << "qtest running";

    QQueue<int> q;
    q.enqueue(1);
    q.enqueue(2);

    qDebug() << q.size();

    qDebug() << q.dequeue();
    qDebug() << q.dequeue();

    if (!q.isEmpty()) {
        qDebug() << q.dequeue();
    }
}
