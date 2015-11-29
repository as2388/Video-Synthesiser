//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_UNIT_H
#define VIDEOSYNTH_UNIT_H

#include <qimage.h>

typedef void (*UnitCalcFunc)(struct Unit *inThing, int inNumSamples);
struct Rate {
    double mSampleRate; // samples per second
};

struct Unit {
    bool mDone;
    float **mFloatInBuf, **mFloatOutBuf;
    QImage **mImageInBuf, **mImageOutBuf;
    struct Rate *mRate;
    UnitCalcFunc mCalcFunc;
};

void Unit_Ctor(Unit* unit, float** floatInBuf, float** floatOutBuf, QImage** imageInBuf, QImage** imageOutBuf
/* TODO: UnitSpec, memory */);

struct Rectangle: public Unit {
    QImage *inputImage, *outputImage;
    QPainter *copier;
};
void Rectangle_Ctor(Rectangle* unit);

struct Line : public Unit
{
    double mLevel, mSlope;
    float mEndLevel;
    int mCounter;
};
void Line_Ctor(Line* unit);

#endif //VIDEOSYNTH_UNIT_H
