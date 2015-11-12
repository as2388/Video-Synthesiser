#ifndef BOOSTREADER_H
#define BOOSTREADER_H

#include <QThread>
#include <boost/lockfree/queue.hpp>

class BoostReader : public QThread
{
private:
    boost::lockfree::queue<int> *queue;
public:
    BoostReader(boost::lockfree::queue<int> *q);
private:
    void run();
};

#endif // BOOSTREADER_H
