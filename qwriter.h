#ifndef QWRITER_H
#define QWRITER_H

#include <QObject>
#include <QThread>

class QWriter : public QThread
{
    Q_OBJECT
public:
    explicit QWriter(QObject *parent = 0);
    void run();

signals:
    void postNewData(int);

public slots:
};

#endif // QWRITER_H
