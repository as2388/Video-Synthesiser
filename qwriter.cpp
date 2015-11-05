#include "qwriter.h"
#include <QDebug>

int output = 0;

QWriter::QWriter(QObject *parent) : QThread()
{

}

void QWriter::run() {
    qDebug() << "writer thread started";

    while (true) {
        qDebug() << "emitting " << output;
        emit postNewData(output);
        output++;
    }
}
