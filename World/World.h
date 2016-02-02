//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_WORLD_H
#define VIDEOSYNTH_WORLD_H


#include <qimage.h>
#include <Graph/Graph.h>
#include "ImagePool.h"

class World {
private:
    ImagePool* imagePool;
public:
    World(int poolSize, int imgWidth, int imgHeight);

    QPainter** mDisplayBuffers;
    QImage** mImageBuffers;
    int mNumDisplayBuffers;
    QImage** mUserImages;
    Graph* graph;

    QImage* acquirePooledImage();
    void releasePooledImage(QImage* image);
};

#endif //VIDEOSYNTH_WORLD_H
