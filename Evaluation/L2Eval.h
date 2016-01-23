//
// Created by Alexander Simpson on 2016-01-21.
//

#ifndef VIDEOSYNTH_L2EVAL_H
#define VIDEOSYNTH_L2EVAL_H

#include <qimage.h>
#include <QPainter>
#include <QDebug>
#include <qelapsedtimer.h>
#include <Synthesiser/Units/ImageUnits.h>

class L2Eval {
public:
    void timeEverything() {
        this->timeMyCopy();
        this->timeMyMemCopy();
        this->timeMyFastMemCopy();
        this->timeQPainterCopy();
        this->timeImageFill();
        this->timeRectFillCore();
        this->timeRectFillSmall();
    }

    void timeQPainterCopy() {
        QImage* inputImage = new QImage(800, 800, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 800, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QPainter* copier = new QPainter(outputImage);

//        for (int i = 0; i < 800; i++) {
//            qDebug() << inputImage->scanLine(i);
//        }

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            copier->drawImage(QPoint(0, 0), *inputImage);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    };

    void timeMyCopy() {
        QImage* inputImage = new QImage(800, 800, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 800, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        QImage** outPayload = new QImage*[0];
        inPayload[0] = inputImage;
        outPayload[0] = outputImage;

        CopyImage* unit = new CopyImage();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
        CopyImage_Ctor(unit);

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    };

    void timeMyMemCopy() {
        QImage* inputImage = new QImage(800, 800, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 800, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        QImage** outPayload = new QImage*[0];
        inPayload[0] = inputImage;
        outPayload[0] = outputImage;

        CopyImageFast* unit = new CopyImageFast();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
        CopyImageFast_Ctor(unit);

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    };

    void timeMyFastMemCopy() {
        QImage* inputImage = new QImage(800, 800, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 800, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        QImage** outPayload = new QImage*[0];
        inPayload[0] = inputImage;
        outPayload[0] = outputImage;

        CopyImageVeryFast* unit = new CopyImageVeryFast();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
        CopyImageVeryFast_Ctor(unit);

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    };

    void timeImageFill() {
        QImage* image = new QImage(800, 800, QImage::Format_ARGB32);

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            image->fill(qRgba(0, 0, 0, 0));
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    }

    void timeRectFillCore() {
        QImage* outputImage = new QImage(800, 800, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** outPayload = new QImage*[0];
        outPayload[0] = outputImage;

        float* rectX = new float(0);
        float* rectY = new float(0);
        float* rectWidth = new float(800);
        float* rectHeight = new float(800);
        float** rectInFloatBuffer = new float*[4];
        rectInFloatBuffer[0] = rectX;
        rectInFloatBuffer[1] = rectY;
        rectInFloatBuffer[2] = rectWidth;
        rectInFloatBuffer[3] = rectHeight;
        int** color = new int*[1];
        color[0] = new int(qRgba(0, 0, 0, 0));

        RectFast* unit = new RectFast();
        Unit_Ctor(unit, NULL, rectInFloatBuffer, NULL, color, NULL, NULL, outPayload);
        RectFast_Ctor(unit);

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    }

    void timeRectFillSmall() {
        QImage* outputImage = new QImage(800, 800, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** outPayload = new QImage*[0];
        outPayload[0] = outputImage;

        float* rectX = new float(375);
        float* rectY = new float(375);
        float* rectWidth = new float(50);
        float* rectHeight = new float(50);
        float** rectInFloatBuffer = new float*[4];
        rectInFloatBuffer[0] = rectX;
        rectInFloatBuffer[1] = rectY;
        rectInFloatBuffer[2] = rectWidth;
        rectInFloatBuffer[3] = rectHeight;
        int** color = new int*[1];
        color[0] = new int(qRgba(0, 0, 0, 0));

        RectFast* unit = new RectFast();
        Unit_Ctor(unit, NULL, rectInFloatBuffer, NULL, color, NULL, NULL, outPayload);
        RectFast_Ctor(unit);

        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        for (int i = 0; i < 10000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    }
};

#endif //VIDEOSYNTH_L2EVAL_H
