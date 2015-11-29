//
// Created by Alexander Simpson on 2015-11-29.
//

#include <qpainter.h>
#include "Unit.h"


void Unit_Ctor(Unit* unit, float** floatInBuf, float** floatOutBuf, QImage** imageInBuf, QImage** imageOutBuf) {
    unit -> mDone = false;

    unit -> mFloatInBuf = floatInBuf;
    unit -> mFloatOutBuf = floatOutBuf;

    unit -> mImageInBuf = imageInBuf;
    unit -> mImageOutBuf = imageOutBuf;

    unit -> mRate = new Rate();
    unit -> mRate -> mSampleRate = 1;
}






#define IN(index)  (unit->mFloatInBuf[index])
#define OUT(index) (unit->mFloatOutBuf[index])
#define ZOFF (0)
#define ZIN(i) (IN(i) - ZOFF)	// get buffer pointer offset for iteration
#define ZIN0(i) (IN(i)[0])		// get first sample
#define ZOUT(i) (OUT(i) - ZOFF)		// get buffer pointer offset for iteration
#define ZOUT0(i) (OUT(i)[0])		// get first sample
#define LOOP(length, stmt) for (int xxi=0; xxi<(length); ++xxi) { stmt; }
#define ZXP(z) (*(z)++)
#define SETCALC(func) (unit->mCalcFunc = (UnitCalcFunc)&func)
#define sc_max(a,b) (((a) > (b)) ? (a) : (b))
#define sc_min(a,b) (((a) < (b)) ? (a) : (b))

static inline void Line_next_loop(Line * unit, int & counter, int remain, double & level)
{
    float *out = ZOUT(0);
    double slope = unit->mSlope;

    do {
        if (counter==0) {
            int nsmps = remain;
            remain = 0;
            float endlevel = unit->mEndLevel;
            LOOP(nsmps,
                 ZXP(out) = endlevel;
            );
        } else {
            int nsmps = sc_min(remain, counter);
            counter -= nsmps;
            remain -= nsmps;
            LOOP(nsmps,
                 ZXP(out) = level;
            level += slope;
            );
            if (counter == 0) {
                unit->mDone = true;
                //int doneAction = (int)ZIN0(3);
                //DoneAction(doneAction, unit); TODO: Find out what this does
            }
        }
    } while (remain);

}


void Line_next(Line *unit, int inNumSamples)
{
    double level = unit->mLevel;
    int counter = unit->mCounter;
    Line_next_loop(unit, counter, inNumSamples, level);
    unit->mCounter = counter;
    unit->mLevel = level;
}

void Line_Ctor(Line* unit)
{
    SETCALC(Line_next);
    double start = ZIN0(0);
    double end = ZIN0(1);
    double dur = ZIN0(2);

    int counter = (int)(dur * unit->mRate->mSampleRate + .5f);
    unit->mCounter = sc_max(1, counter);
    if(counter == 0){
        unit->mLevel = end;
        unit->mSlope = 0.;
    } else {
        unit->mLevel = start;
        unit->mSlope = (end - start) / unit->mCounter;
        unit->mLevel += unit->mSlope;
    }
    unit->mEndLevel = end;
    ZOUT0(0) = unit->mLevel;
}

void Rectangle_next(Rectangle* unit, int inNumSamples) {
    unit -> copier -> drawImage(QPoint(0, 0), *(unit -> inputImage));

    int iX = int(ZIN0(0));
    int iY = int(ZIN0(1));
    int iWidth = int(ZIN0(2));
    int iHeight = int(ZIN0(3));

    for (int y = iY; y < iY + iHeight; y++) {
        uint *line = (uint *) unit -> outputImage -> scanLine(y);
        for (int x = iX; x < iX + iWidth; x++) {
            *(line + x) = qRgba(255, 0, 0, 255);
        }
    }
}

void Rectangle_Ctor(Rectangle* unit) {
    SETCALC(Rectangle_next);

    unit -> inputImage = unit -> mImageInBuf[0];
    unit -> outputImage = unit -> mImageOutBuf[0];

    unit -> copier = new QPainter(unit -> outputImage);
}