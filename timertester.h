#ifndef TIMERTESTER_H
#define TIMERTESTER_H

#include <QObject>

class timertester : public QObject
{
    Q_OBJECT
public:
    explicit timertester(QObject *parent = 0);
    void begin();
signals:

public slots:
    void timerFire();
};

#endif // TIMERTESTER_H
