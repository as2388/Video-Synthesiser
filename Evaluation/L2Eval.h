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
#include <sys/time.h>

class L2Eval {
public:
    void timeEverything() {
        qDebug() << "Starting test...";

        //this->timeImageMalloc();

        this->timeQPainterCopy();
        this->timeMyCopy();
        this->timeMyMemCopy();
        this->timeMyFastMemCopy();
        this->timeImageFill();
        this->timeMyFastFill();
        this->timeRectOldCore();
        this->timeRectFillCore();
        this->timeRectFillSmall();

        qDebug() << "Done!";
    }

    void timeImageMalloc() {
        QElapsedTimer stopwatch = QElapsedTimer();
        stopwatch.restart();
        QImage* image;
        for (int i = 0; i < 10000; i++) {
            image = new QImage(800, 800, QImage::Format_ARGB32);
        }
        qint64 totalTime = stopwatch.elapsed();
        qDebug() << totalTime;
    }

    void timeQPainterCopy() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QPainter* copier = new QPainter(outputImage);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            copier->drawImage(QPoint(0, 0), *inputImage);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "QPainter copy:" << timeCompute(startTime, endTime);
    };

    void timeMyCopy() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        QImage** outPayload = new QImage*[0];
        inPayload[0] = inputImage;
        outPayload[0] = outputImage;

        CopyImage* unit = new CopyImage();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
        CopyImage_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "Naive copy:" << timeCompute(startTime, endTime);
    };

    long int timeCompute(timeval startTime, timeval endTime) {
        long int start = (startTime.tv_sec) * 1000 + (startTime.tv_usec) / 1000;
        long int end = (endTime.tv_sec) * 1000 + (endTime.tv_usec) / 1000;

        return end - start;
    }

    void timeMyMemCopy() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        QImage** outPayload = new QImage*[0];
        inPayload[0] = inputImage;
        outPayload[0] = outputImage;

        CopyImageFast* unit = new CopyImageFast();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
        CopyImageFast_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "scanline memcpy:" << timeCompute(startTime, endTime);
    };

    void timeMyFastMemCopy() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        QImage** outPayload = new QImage*[0];
        inPayload[0] = inputImage;
        outPayload[0] = outputImage;

        CopyImageVeryFast* unit = new CopyImageVeryFast();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
        CopyImageVeryFast_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "Fast memcpy (experimental):" << timeCompute(startTime, endTime);
    };

    void timeImageFill() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        inPayload[0] = inputImage;

        ClearImage* unit = new ClearImage();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, NULL);
        ClearImage_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "Clear:" << timeCompute(startTime, endTime);
    }

    void timeMyFastFill() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        inPayload[0] = inputImage;

        ClearImageFast* unit = new ClearImageFast();
        Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, NULL);
        ClearImageFast_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "Fast clear (experimental):" << timeCompute(startTime, endTime);
    };

    void timeRectOldCore() {
        QImage* inputImage = new QImage(800, 600, QImage::Format_ARGB32);
        inputImage->fill(qRgba(0, 0, 0, 0));
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** inPayload = new QImage*[0];
        inPayload[0] = inputImage;
        QImage** outPayload = new QImage*[0];
        outPayload[0] = outputImage;

        float* rectX = new float(0);
        float* rectY = new float(0);
        float* rectWidth = new float(800);
        float* rectHeight = new float(600);
        float** rectInFloatBuffer = new float*[4];
        rectInFloatBuffer[0] = rectX;
        rectInFloatBuffer[1] = rectY;
        rectInFloatBuffer[2] = rectWidth;
        rectInFloatBuffer[3] = rectHeight;
        int** color = new int*[1];
        color[0] = new int(qRgba(0, 0, 0, 0));

        Rectangle* unit = new Rectangle();
        Unit_Ctor(unit, NULL, rectInFloatBuffer, NULL, color, NULL, inPayload, outPayload);
        Rectangle_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "800 x 800 rectangle:" << timeCompute(startTime, endTime);
    }

    void timeRectFillCore() {
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage** outPayload = new QImage*[0];
        outPayload[0] = outputImage;

        float* rectX = new float(0);
        float* rectY = new float(0);
        float* rectWidth = new float(800);
        float* rectHeight = new float(600);
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

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "800 x 800 rectangle optimised:" << timeCompute(startTime, endTime);
    }

    void timeRectFillSmall() {
        QImage* outputImage = new QImage(800, 600, QImage::Format_ARGB32);
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

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < 1000; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "50 x 50 Rectangle optimised:" << timeCompute(startTime, endTime);
    }
};

#endif //VIDEOSYNTH_L2EVAL_H
