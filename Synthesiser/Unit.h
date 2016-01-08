//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_UNIT_H
#define VIDEOSYNTH_UNIT_H

#include <qimage.h>
#include <World.h>

typedef void (*UnitCalcFunc)(struct Unit *inThing, int inNumSamples);
struct Rate {
    double mSampleRate; // samples per second
};

struct Unit {
    World *mWorld;
    bool mDone;
    float **mFloatInBuf, **mFloatOutBuf;
    int **mIntInBuf, **mIntOutBuf;
    QImage **mImageInBuf, **mImageOutBuf;
    struct Rate *mRate;
    UnitCalcFunc mCalcFunc;
};

void Unit_Ctor(Unit* unit, World* world,
               float** floatInBuf, float** floatOutBuf,
               int** intInBuf, int** intOutBuf,
               QImage** imageInBuf, QImage** imageOutBuf
/* TODO: UnitSpec, memory */);



#endif //VIDEOSYNTH_UNIT_H
