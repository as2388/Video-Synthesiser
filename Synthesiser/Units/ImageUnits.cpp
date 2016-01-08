#include "ImageUnits.h"
#include <Synthesiser/Units/UnitMacros.h>
#include <QPainter>

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

void FloatToInt_next(FloatToInt* unit, int inNumSamples) {
    *unit -> mIntOutBuf[0] = int(*unit -> mFloatInBuf[0]);
}

void FloatToInt_Ctor(FloatToInt* unit) {
    SETCALC(FloatToInt_next);
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

    unit -> copier = unit -> mWorld -> mDisplayBuffers[0];
}