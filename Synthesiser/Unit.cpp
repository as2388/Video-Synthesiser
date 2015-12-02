//
// Created by Alexander Simpson on 2015-11-29.
//

#include <qpainter.h>
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
    int iColor = *unit -> mIntInBuf[0];

    for (int y = iY; y < iY + iHeight; y++) {
        uint *line = (uint *) unit -> outputImage -> scanLine(y);
        for (int x = iX; x < iX + iWidth; x++) {
            *(line + x) = iColor;
        }
    }
}

void Rectangle_Ctor(Rectangle* unit) {
    SETCALC(Rectangle_next);

    unit -> inputImage = unit -> mImageInBuf[0];
    unit -> outputImage = unit -> mImageOutBuf[0];

    unit -> copier = new QPainter(unit -> outputImage);
}

void Color_next(Color* unit, int inNumSamples) {
    int r = *unit -> mIntInBuf[0];
    int g = *unit -> mIntInBuf[1];
    int b = *unit -> mIntInBuf[2];
    int a = *unit -> mIntInBuf[3];

    *unit -> mIntOutBuf[0] = qRgba(r, g, b, a);
}

void Color_Ctor(Color* unit) {
    SETCALC(Color_next);
}

void AlphaBlend_next(AlphaBlend* unit, int inNumSamples) {
    for (int x = 0; x < unit -> inputImageUnder -> width(); x++) {
        for (int y = 0; y < unit -> inputImageUnder -> height(); y++) {
            QColor rgb0 = QColor(unit -> inputImageUnder -> pixel(x, y));
            QColor rgb1 = QColor(unit -> inputImageOver -> pixel(x, y));

            int alpha0 = qAlpha(unit -> inputImageUnder -> pixel(x, y));
            int alpha1 = qAlpha(unit -> inputImageOver -> pixel(x, y));

            double aan = alpha1 / 255.0;
            double abn = alpha0 / 255.0;

            unit -> outputImage -> setPixel(x, y, qRgba(
                    blendHelper(rgb1.red(),   alpha1, rgb0.red(),   alpha0),
                    blendHelper(rgb1.green(), alpha1, rgb0.green(), alpha0),
                    blendHelper(rgb1.blue(),  alpha1, rgb0.blue(),  alpha0),
                    (int) (255 * (aan + abn * (1 - aan))))
            );
        }
    }
}
int blendHelper(double ca, double aa, double cb, double ab) {
    double aan = aa / 255.0;
    double abn = ab / 255.0;

    return (int) ((ca * aan + cb * abn * (1.0 - aan)) / (aan + abn * (1.0 - aan)));
}

void AlphaBlend_Ctor(AlphaBlend* unit) {
    SETCALC(AlphaBlend_next);

    unit -> inputImageUnder = unit -> mImageInBuf[0];
    unit -> inputImageOver = unit -> mImageInBuf[1];
    unit -> outputImage = unit -> mImageOutBuf[0];
}

void Draw_next(Draw* unit, int inNumSamples) {
    unit -> copier -> drawImage(QPoint(0, 0), *(unit -> inputImage));
}

void Draw_Ctor(Draw* unit) {
    SETCALC(Draw_next);

    unit -> inputImage = unit -> mImageInBuf[0];

    unit -> copier = new QPainter(unit -> mWorld -> mDisplayBuffers[0]);
}