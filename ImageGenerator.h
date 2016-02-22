//
// Created by Alexander Simpson on 2016-02-22.
//

#ifndef VIDEOSYNTH_IMAGEGENERATOR_H
#define VIDEOSYNTH_IMAGEGENERATOR_H


#include <qthread.h>
#include <boost/lockfree/queue.hpp>
#include <World/World.h>

class ImageGenerator : public QObject {
    Q_OBJECT
private:
    boost::lockfree::queue<QImage*> *queue;
public:
    World* world;
    ImageGenerator();
    void setQueue(boost::lockfree::queue<QImage*> *q) {this->queue = q;}
public slots:
    void run();
};


#endif //VIDEOSYNTH_IMAGEGENERATOR_H
