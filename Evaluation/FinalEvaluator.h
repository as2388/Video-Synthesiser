//
// Created by Alexander Simpson on 2016-04-09.
//

#ifndef VIDEOSYNTH_FINALEVALUATOR_H
#define VIDEOSYNTH_FINALEVALUATOR_H

#include <QDebug>
#include <sys/time.h>
#include <Synthesiser/Units/ImageUnits.h>
#include <qtextstream.h>
#include <qfile.h>
#include <QTimer>

class FinalEvaluator : public QObject {
Q_OBJECT
private:
    int maxSize = 1000;
    int count = 1000;

    long int timeCompute(timeval startTime, timeval endTime) {
        long int start = (startTime.tv_sec) * 1000 + (startTime.tv_usec) / 1000;
        long int end = (endTime.tv_sec) * 1000 + (endTime.tv_usec) / 1000;

        return end - start;
    }

    QFile* driftFile;
    QTextStream* driftStream;
    int logicalTime = 0;
    struct timeval driftStartTime;
    QTimer *timer;
    //QString path = "/Users/alexander/Documents/partii-project/submittables/figs/";
    QString path = "/home/pi/figs/";
public:
    void evaluateRectangleFast() {
        QString filename = path + "rectangle.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        for (int size = 1; size <= maxSize; size++) {
            QImage *outputImage = new QImage(size, size, QImage::Format_ARGB32);
            outputImage->fill(qRgba(0, 0, 0, 0));

            QImage **outPayload = new QImage *[0];
            outPayload[0] = outputImage;

            float *rectX = new float(0);
            float *rectY = new float(0);
            float *rectWidth = new float(size);
            float *rectHeight = new float(size);
            float **rectInFloatBuffer = new float *[4];
            rectInFloatBuffer[0] = rectX;
            rectInFloatBuffer[1] = rectY;
            rectInFloatBuffer[2] = rectWidth;
            rectInFloatBuffer[3] = rectHeight;
            int **color = new int *[1];
            color[0] = new int(qRgba(0, 0, 0, 0));

            RectFast *unit = new RectFast();
            Unit_Ctor(unit, NULL, rectInFloatBuffer, NULL, color, NULL, NULL, outPayload);
            RectFast_Ctor(unit);

            struct timeval startTime, endTime;
            gettimeofday(&startTime, NULL);
            for (int i = 0; i < count; i++) {
                unit->mCalcFunc(unit, 1);
            }
            gettimeofday(&endTime, NULL);

            delete[] outPayload;
            delete outputImage;
            for (int i = 0; i < 4; i++) {delete rectInFloatBuffer[i];}
            delete[] rectInFloatBuffer;
            delete color[0];
            delete[] color;

            qDebug() << "1. RectangleFast" << size << "," << timeCompute(startTime, endTime);
            stream << size << "," << timeCompute(startTime, endTime) << endl;
        }
    }

    void evaluateImageFill() {
        QString filename = path + "fill.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        for (int size = 1; size <= maxSize; size++) {
            QImage *inputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage **inPayload = new QImage *[0];
            inPayload[0] = inputImage;

            ClearImage *unit = new ClearImage();
            Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, NULL);
            ClearImage_Ctor(unit);

            struct timeval startTime, endTime;
            gettimeofday(&startTime, NULL);
            for (int i = 0; i < count; i++) {
                unit->mCalcFunc(unit, 1);
            }
            gettimeofday(&endTime, NULL);

            delete inputImage;
            delete[] inPayload;

            qDebug() << "2. Fill" << size << "," << timeCompute(startTime, endTime);
            stream << size << "," << timeCompute(startTime, endTime) << endl;

        }
    }

    void evaluateCopyImage() {
        QString filename = path + "copy.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        for (int size = 1; size <= maxSize; size++) {
            QImage *inputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage *outputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage **inPayload = new QImage *[0];
            inPayload[0] = inputImage;

            QImage **outPayload = new QImage *[0];
            outPayload[0] = outputImage;

            CopyImageVeryFast *unit = new CopyImageVeryFast();
            Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
            CopyImageVeryFast_Ctor(unit);

            struct timeval startTime, endTime;
            gettimeofday(&startTime, NULL);
            for (int i = 0; i < count; i++) {
                unit->mCalcFunc(unit, 1);
            }
            gettimeofday(&endTime, NULL);

            delete inputImage;
            delete[] inPayload;
            delete outputImage;
            delete[] outPayload;

            qDebug() << "3. Copy" << size << "," << timeCompute(startTime, endTime);
            stream << size << "," << timeCompute(startTime, endTime) << endl;

        }
    }

    void evaluateSymm8() {
        QString filename = path + "symm8.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        for (int size = 1; size <= maxSize; size++) {
            QImage *inputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage *outputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage **inPayload = new QImage *[0];
            inPayload[0] = inputImage;

            QImage **outPayload = new QImage *[0];
            outPayload[0] = outputImage;

            Symm8 *unit = new Symm8();
            Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
            Symm8_Ctor(unit);

            struct timeval startTime, endTime;
            gettimeofday(&startTime, NULL);
            for (int i = 0; i < count; i++) {
                unit->mCalcFunc(unit, 1);
            }
            gettimeofday(&endTime, NULL);

            delete inputImage;
            delete[] inPayload;
            delete outputImage;
            delete[] outPayload;

            qDebug() << "4. Symm8" << size << "," << timeCompute(startTime, endTime);
            stream << size << "," << timeCompute(startTime, endTime) << endl;

        }
    }

    void evaluateColor() {

    }

    void evaluateFloats() {

    }

    void evaluateDrift() {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(driftUpdate()));

        this->driftFile = new QFile(path + "drift.csv");
        this->driftStream = new QTextStream(driftFile);
        this->driftFile->open(QIODevice::WriteOnly);

        gettimeofday(&driftStartTime, NULL);
        timer->start(100);
    }

public slots:
    void evaluateEverything() {
        this->evaluateRectangleFast();
        this->evaluateImageFill();
        this->evaluateCopyImage();
        this->evaluateSymm8();

        this->evaluateDrift();
    }

    void driftUpdate() {
        struct timeval endTime;
        gettimeofday(&endTime, NULL);
        logicalTime += 100;

        *driftStream << logicalTime << "," << timeCompute(driftStartTime, endTime) << endl;
        qDebug() << "5. Drift" << logicalTime << "," << timeCompute(driftStartTime, endTime);

        if (logicalTime > 100 * 10 * 60 * 5) {
            this->timer->stop();
        }
    };

};

#endif //VIDEOSYNTH_FINALEVALUATOR_H
