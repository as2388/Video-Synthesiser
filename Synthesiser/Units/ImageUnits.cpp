#include "ImageUnits.h"
#include <Synthesiser/Units/UnitMacros.h>
#include <QPainter>
#include <QtGui>

void Rectangle_next(Rectangle* unit, int inNumSamples) {
    unit -> copier -> drawImage(QPoint(0, 0), *(unit -> inputImage));
    //memcpy(unit->outputImage->bits(), unit->inputImage->bits(), (size_t) unit->inputImage->bytesPerLine() * unit->inputImage->height());

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

void RectFast_next(RectFast* unit, int inNumSamples) {
    int iX = int(ZIN0(0));
    int iY = int(ZIN0(1));
    int iWidth = int(ZIN0(2));
    int iHeight = int(ZIN0(3));
    int iColor = *unit->mIntInBuf[0];
    QImage* output = unit->mImageOutBuf[0];

    for (int y = iY; y < iY + iHeight; y++) {
        uint *line = (uint *) output->scanLine(y);
        for (int x = iX; x < iX + iWidth; x++) {
            *(line + x) = iColor;
        }
    }
}
void RectFast_Ctor(RectFast* unit) {
    SETCALC(RectFast_next);
}

void CopyImage_next(CopyImage* unit) {
    QImage* input = unit -> mImageInBuf[0];
    QImage* output = unit -> mImageOutBuf[0];
    for (int y = 0; y < input->height(); y ++) {
        uint *inputLine = (uint*) input->scanLine(y);
        uint *outputLine = (uint*) output->scanLine(y);

        for (int x = 0; x < input->width(); x++) {
            *(inputLine + x) = *(outputLine + x);
        }
    }
}

void CopyImage_Ctor(CopyImage* unit) {
    SETCALC(CopyImage_next);
}

void CopyImageFast_next(CopyImageFast* unit) {
    QImage* input = unit -> mImageInBuf[0];
    QImage* output = unit -> mImageOutBuf[0];
    for (int y = 0; y < input->height(); y ++) {
        uint *inputLine = (uint*) input->scanLine(y);
        uint *outputLine = (uint*) output->scanLine(y);

        memcpy(outputLine, inputLine, (size_t) input->bytesPerLine());
    }
}

void CopyImageFast_Ctor(CopyImageFast* unit) {
    SETCALC(CopyImageFast_next);
}

void CopyImageVeryFast_next(CopyImageVeryFast* unit) {
    QImage* input = unit -> mImageInBuf[0];
    QImage* output = unit -> mImageOutBuf[0];
    memcpy(output->bits(), input->bits(), (size_t) input->bytesPerLine() * input->height());
}

void CopyImageVeryFast_Ctor(CopyImageVeryFast* unit) {
    SETCALC(CopyImageVeryFast_next);
}

void ClearImage_next(ClearImage* unit) {
    unit->mImageInBuf[0]->fill(qRgba(0, 0, 0, 0));
}

void ClearImage_Ctor(ClearImage* unit) {
    SETCALC(ClearImage_next);
}

void ClearImageFast_next(ClearImageFast* unit) {
    QImage* image = unit->mImageInBuf[0];
    memset(image->bits(), 0, (size_t) image->bytesPerLine() * image->height());
}

void ClearImageFast_Ctor(ClearImageFast* unit) {
    SETCALC(ClearImageFast_next);
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

void CopyRegion_next(CopyRegion* unit) {
    int iX = int(ZIN0(0));
    int iY = int(ZIN0(1));
    int iWidth = int(ZIN0(2));
    int iHeight = int(ZIN0(3));
    int alpha = int(ZIN0(4));
    QImage* input = unit->mImageInBuf[0];
    QImage* output = unit->mImageOutBuf[0];

    for (int y = iY; y < iY + iHeight; y++) {
        uint *inputLine = (uint *) input->scanLine(y);
        uint *outputLine = (uint *) output->scanLine(y);
        for (int x = iX; x < iX + iWidth; x++) {
            *(outputLine + x) = (*(inputLine + x) & (~(0xFF << 24))) | (alpha << 24);
        }
    }
}
void CopyRegion_Ctor(CopyRegion* unit) {
    SETCALC(CopyRegion_next);
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

void Symm8_next(Symm8* unit, int inNumSamples) {
    // Copy the upper right triangle to the output image's top left quadrant.
    for (int y = 0; y < unit->outputImage->width() >> 1; y++) {
        uint *outputLine = (uint *) unit->outputImage->scanLine(y);
        uint *inputLine = (uint *) unit->inputImage->scanLine(y);
        for (int x = 0; x < unit->inputImage->width() >> 1; x++) {
            if (x >= y) {
                *(outputLine + x) = *(inputLine + x);
            } else {
                *(outputLine + x) = unit->inputImage->pixel(y, x);
            }
        }
    }

    // Mirror the upper-left quadrant to the upper-right quadrant
    for (int y = 0; y < unit->outputImage->width() >> 1; y++) {
        uint *line = (uint *) unit->outputImage->scanLine(y);
        for (int x = 0; x < unit->inputImage->width() >> 1; x++) {
            *(line + unit->inputImage->width() - x) = *(line + x);
        }
    }

    // Mirror the upper half to the lower half
    for (int y = 0; y < unit->outputImage->width() >> 1; y++) {
        uint *upperLine = (uint *) unit->outputImage->scanLine(y);
        uint *lowerLine = (uint *) unit->outputImage->scanLine(unit->outputImage->width() - y);
        for (int x = 0; x < unit->inputImage->width(); x++) {
            *(lowerLine + x) = *(upperLine + x);
        }
    }

}

void Symm8_Ctor(Symm8* unit) {
    SETCALC(Symm8_next);

    unit->inputImage = unit->mImageInBuf[0];
    unit->outputImage = unit->mImageOutBuf[0];
}

void Draw_next(Draw* unit, int inNumSamples) {
    unit->mWorld->mDisplayBuffers[*unit->mIntInBuf[0]]->drawImage(QPoint(0, 0), *(unit -> inputImage));
}

void Draw_Ctor(Draw* unit) {
    SETCALC(Draw_next);

    unit -> inputImage = unit -> mImageInBuf[0];
}

void Look_next(Look* unit, int inNumSamples) {
    //QPainter painter(unit->mImageOutBuf[0]);
    //painter.drawImage(QPoint(0, 0), *(unit->mWorld->mImageBuffers[1]));
    //painter.end();

    unit->mImageOutBuf[0] = unit->mWorld->mImageBuffers[1];

    //unit->copier = new QPainter(unit->mImageInBuf[0]);

    //QPainter painter(unit->mImageOutBuf[0]);
    //unit->copier->drawImage(QPointF(0, 0), *(unit->mWorld->mImageBuffers[1]));
}

void Look_Ctor(Look* unit) {
    SETCALC(Look_next);

    //unit ->copier = new QPainter(unit->mImageInBuf[0]);
}