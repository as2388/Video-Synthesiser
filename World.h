//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_WORLD_H
#define VIDEOSYNTH_WORLD_H


#include <qimage.h>

class World {
public:
    QPainter** mDisplayBuffers;
    int mNumDisplayBuffers;
};




#endif //VIDEOSYNTH_WORLD_H
