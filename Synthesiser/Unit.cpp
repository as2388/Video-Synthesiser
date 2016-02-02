//
// Created by Alexander Simpson on 2015-11-29.
//

#include <qpainter.h>
#include <World/World.h>
#include "Unit.h"

void Unit_Ctor(Unit* unit, World* world,
               float** floatInBuf, float** floatOutBuf,
               int** intInBuf, int** intOutBuf,
               QImage** imageInBuf, QImage** imageOutBuf) {
    unit -> mWorld = world;

    unit -> mDone = false;

    unit -> mFloatInBuf = floatInBuf;
    unit -> mFloatOutBuf = floatOutBuf;

    unit -> mIntInBuf = intInBuf;
    unit -> mIntOutBuf = intOutBuf;

    unit -> mImageInBuf = imageInBuf;
    unit -> mImageOutBuf = imageOutBuf;

    unit -> mRate = new Rate();
    unit -> mRate -> mSampleRate = 1;
}
