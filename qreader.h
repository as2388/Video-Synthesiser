#ifndef QREADER_H
#define QREADER_H

#include <QObject>
#include <QThread>

class QReader : public QThread
{
    Q_OBJECT
public:
    explicit QReader(QObject *parent = 0);
    void run();

signals:

public slots:
    void receiveNewData(int newData);
};

#endif // QREADER_H
