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
#include <Synthesiser/Units/FloatUnits.h>

class FinalEvaluator : public QObject {
Q_OBJECT
private:
    int maxSize = 10;
    int count = 1000;
    int highCount = 1000000;

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
    //QString path = "/Users/alexander/Documents/partii-project/submittables/figs2/";
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

    void evaluateCopyRegion() {
        QString filename = path + "copyregion.csv";
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

            float **inData = new float*[5];
            inData[0] = new float(0);
            inData[1] = new float(0);
            inData[2] = new float(size);
            inData[3] = new float(size);
            inData[4] = new float(255);

            CopyRegion *unit = new CopyRegion();
            Unit_Ctor(unit, NULL, inData, NULL, NULL, NULL, inPayload, outPayload);
            CopyRegion_Ctor(unit);

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

            qDebug() << "5. Copy Region" << size << "," << timeCompute(startTime, endTime);
            stream << size << "," << timeCompute(startTime, endTime) << endl;
        }
    }

    void evaluateAlphaBlend() {
        QString filename = path + "alphablend.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        for (int size = 1; size <= maxSize; size++) {
            QImage *inputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage *inputImage2 = new QImage(size, size, QImage::Format_ARGB32);
            inputImage2->fill(qRgba(0, 0, 0, 0));

            QImage *outputImage = new QImage(size, size, QImage::Format_ARGB32);
            inputImage->fill(qRgba(0, 0, 0, 0));

            QImage **inPayload = new QImage *[1];
            inPayload[0] = inputImage;
            inPayload[1] = inputImage2;

            QImage **outPayload = new QImage *[0];
            outPayload[0] = outputImage;

            AlphaBlend *unit = new AlphaBlend();
            Unit_Ctor(unit, NULL, NULL, NULL, NULL, NULL, inPayload, outPayload);
            AlphaBlend_Ctor(unit);

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

            qDebug() << "6. Alphablend" << size << "," << timeCompute(startTime, endTime);
            stream << size << "," << timeCompute(startTime, endTime) << endl;
        }
    }

    void evaluateColor() {
        QString filename = path + "color.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        int **in = new int*[3];
        in[0] = new int(127);
        in[1] = new int(127);
        in[2] = new int(127);
        in[3] = new int(127);

        int **out = new int*[0];
        out[0] = new int(0);

        Color *unit = new Color();
        Unit_Ctor(unit, NULL, NULL, NULL, in, out, NULL, NULL);
        Color_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "7. Color"  << "," << timeCompute(startTime, endTime);
        stream << timeCompute(startTime, endTime) << endl;
    }

    void evaluateAcquireReleaseImage() {
        QString filename = path + "acquirerelease.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        World world = World(10, maxSize, maxSize);

        int **in = new int*[1];
        in[0] = new int(0);

        QImage *outputImage = new QImage(maxSize, maxSize, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage **outPayload = new QImage *[1];
        outPayload[0] = outputImage;

        AcquireImage *unit = new AcquireImage();
        Unit_Ctor(unit, &world, NULL, NULL, in, NULL, NULL, outPayload);
        AcquireImage_Ctor(unit);

        ReleaseImage *unit2 = new ReleaseImage();
        Unit_Ctor(unit2, &world, NULL, NULL, in, NULL, outPayload, NULL);
        ReleaseImage_Ctor(unit2);

        for (int i = 0; i < highCount; i++) {
            unit2->mCalcFunc(unit2, 1);
        }
        for (int i = 0; i < highCount; i++) {
            unit->mCalcFunc(unit, 1);
        }
        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit2->mCalcFunc(unit2, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "8. Release Image"  << "," << timeCompute(startTime, endTime);
        stream << "release" << timeCompute(startTime, endTime) << endl;

        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "9. Acquire Image"  << "," << timeCompute(startTime, endTime);
        stream << "acquire" << timeCompute(startTime, endTime) << endl;
    }

    void evaluateReadRef() {
        QString filename = path + "readref.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);
        
        World world = World(20, 800, 600);
        world.mImageBuffers = new QImage*[2];
        world.mImageBuffers[0] = world.acquirePooledImage();
        world.mImageBuffers[1] = world.acquirePooledImage();
        world.mImageBuffers[0]->fill(qRgba(0, 0, 0, 255));
        world.mImageBuffers[1]->fill(qRgba(0, 0, 0, 255));
        world.mNumDisplayBuffers = 2;

        int **in = new int*[1];
        in[0] = new int(0);

        QImage *outputImage = new QImage(maxSize, maxSize, QImage::Format_ARGB32);
        outputImage->fill(qRgba(0, 0, 0, 0));

        QImage **outPayload = new QImage *[1];
        outPayload[0] = outputImage;

        ReadRef *unit = new ReadRef();
        Unit_Ctor(unit, &world, NULL, NULL, in, NULL, NULL, outPayload);
        ReadRef_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "10. ReadRef"  << "," << timeCompute(startTime, endTime);
        stream << timeCompute(startTime, endTime) << endl;
    }

    void evaluateLine() {
        QString filename = path + "line.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        float **in = new float*[2];
        in[0] = new float(0);
        in[1] = new float(highCount);
        in[2] = new float(highCount);

        float **out = new float*[0];
        out[0] = new float(0);

        Line *unit = new Line();
        Unit_Ctor(unit, NULL, in, out, NULL, NULL, NULL, NULL);
        Line_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "11. Line"  << "," << timeCompute(startTime, endTime);
        stream << timeCompute(startTime, endTime) << endl;
    }

    void evaluateConverters() {
        QString filename = path + "converters.csv";
        QFile file(filename);
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        float **in = new float*[0];
        in[0] = new float(0);

        int **out = new int*[0];
        out[0] = new int(0);

        FloatToInt *unit = new FloatToInt();
        Unit_Ctor(unit, NULL, in, NULL, NULL, out, NULL, NULL);
        FloatToInt_Ctor(unit);

        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit->mCalcFunc(unit, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "12. float to int"  << "," << timeCompute(startTime, endTime);
        stream << timeCompute(startTime, endTime) << endl;

        IntToFloat *unit2 = new IntToFloat();
        Unit_Ctor(unit2, NULL, NULL, in, out, NULL, NULL, NULL);
        IntToFloat_Ctor(unit2);

        gettimeofday(&startTime, NULL);
        for (int i = 0; i < highCount; i++) {
            unit2->mCalcFunc(unit2, 1);
        }
        gettimeofday(&endTime, NULL);

        qDebug() << "13. int to float"  << "," << timeCompute(startTime, endTime);
        stream << timeCompute(startTime, endTime) << endl;
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
        this->evaluateColor();
        this->evaluateAcquireReleaseImage();
        this->evaluateReadRef();
        this->evaluateLine();
        this->evaluateConverters();

        this->evaluateRectangleFast();
        this->evaluateImageFill();
        this->evaluateCopyImage();
        this->evaluateSymm8();
        this->evaluateCopyRegion();
        this->evaluateAlphaBlend();

        //this->evaluateDrift();
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
