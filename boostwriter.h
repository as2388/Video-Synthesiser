#ifndef BOOSTWRITER_H
#define BOOSTWRITER_H

#include <QThread>
#include <boost/lockfree/queue.hpp>

class BoostWriter : public QThread
{
private:
    boost::lockfree::queue<int> *queue;
public:
    BoostWriter(boost::lockfree::queue<int> *q);
private:
    void run();
};

#endif // BOOSTWRITER_H
