//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_WORLD_H
#define VIDEOSYNTH_WORLD_H


#include <qimage.h>
#include <Graph/Graph.h>

class World {
public:
    World();

    QPainter** mDisplayBuffers;
    QImage** mImageBuffers;
    int mNumDisplayBuffers;
    Graph* graph;
};




#endif //VIDEOSYNTH_WORLD_H
