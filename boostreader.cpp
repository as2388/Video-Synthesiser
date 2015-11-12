#include "boostreader.h"
#include <QDebug>

BoostReader::BoostReader(boost::lockfree::queue<int> *q)
{
    queue = q;
}

int expected = 0;
void BoostReader::run() {
    while (true) {
        int result;
        if (queue->pop(result)) {
            if (result != expected) {
                qDebug() << "fail" << result << expected;
                return;
            }
            expected++;

            if (result == 10000000) {
                qDebug() << "pass";
                return;
            }
        }
    }
}
