//
// Created by Alexander Simpson on 2016-01-10.
//

#ifndef VIDEOSYNTH_UNITEVALUATOR_H
#define VIDEOSYNTH_UNITEVALUATOR_H

#include <qlogging.h>
#include <QDebug>
#include <qrgb.h>
#include <qimage.h>
#include <qelapsedtimer.h>
#include <qfile.h>
#include <Synthesiser/Units/ImageUnits.h>

class UnitEvaluator {
public:
    void evaluateRectangle() {
        QString filename="/Users/Alexander/Desktop/time_ugen_draw2.csv";
        QFile file(filename);
        QTextStream stream(&file);

        if (file.open(QIODevice::WriteOnly))
        {
            qDebug() << "file open";
        } else {
            qDebug() << "failed to open file";
        }

        QElapsedTimer stopwatch;

        Rectangle* rect = new Rectangle();
        float** rectInputs = new float*[4];
        QImage** imageInContainer = new QImage*[1];
        imageInContainer[0] = NULL;
        QImage** imageOutContainer = new QImage*[1];
        imageOutContainer[0] = NULL;
        rectInputs[0] = new float[0];
        rectInputs[1] = new float[0];
        int** colorContainer = new int*[1];
        colorContainer[0] = new int(qRgba(255, 255, 255, 255));

        Unit_Ctor(rect, NULL, rectInputs, NULL, colorContainer, NULL, imageInContainer, imageOutContainer);

        for (int x = 1; x <= 1000; x++) {
            if (imageInContainer[0] != NULL) {
                delete rect->copier;

                delete imageInContainer[0];
                delete imageOutContainer[0];
                delete rectInputs[2];
                delete rectInputs[3];
            }

            imageInContainer[0] = new QImage(x, x, QImage::Format_ARGB32);
            imageInContainer[0]->fill(qRgba(0, 0, 0, 0));

            imageOutContainer[0] = new QImage(x, x, QImage::Format_ARGB32);
            imageOutContainer[0]->fill(qRgba(0, 0, 0, 0));

            rectInputs[2] = new float(x);
            rectInputs[3] = new float(x);

            Rectangle_Ctor(rect);

            stopwatch.restart();
            for (int times = 0; times < 1000; times++) {
                rect->mCalcFunc(rect, 1);
            }
            qint64 totalTime = stopwatch.elapsed();
            stream << x << "," << totalTime << endl;
            qDebug() << x << "," << totalTime;
        }

        return;
    }

    void evaluateSymm8() {
        QString filename="/Users/Alexander/Desktop/time_ugen_symm8.csv";
        QFile file(filename);
        QTextStream stream(&file);

        if (file.open(QIODevice::WriteOnly))
        {
            qDebug() << "file open";
        } else {
            qDebug() << "failed to open file";
        }

        QElapsedTimer stopwatch;

        Symm8* symm = new Symm8();
        QImage** imageInContainer = new QImage*[1];
        imageInContainer[0] = NULL;
        QImage** imageOutContainer = new QImage*[1];
        imageOutContainer[0] = NULL;

        Unit_Ctor(symm, NULL, NULL, NULL, NULL, NULL, imageInContainer, imageOutContainer);

        for (int x = 1; x <= 1000; x++) {
            if (imageInContainer[0] != NULL) {
                //delete imageInContainer[0];
                //delete imageOutContainer[0];
            }

            imageInContainer[0] = new QImage(x, x, QImage::Format_ARGB32);
            imageInContainer[0]->fill(qRgba(0, 0, 0, 0));

            imageOutContainer[0] = new QImage(x, x, QImage::Format_ARGB32);
            imageOutContainer[0]->fill(qRgba(0, 0, 0, 0));

            Symm8_Ctor(symm);

            stopwatch.restart();
            for (int times = 0; times < 1000; times++) {
                symm->mCalcFunc(symm, 1);
            }
            qint64 totalTime = stopwatch.elapsed();

            stream << x << "," << totalTime << endl;
            qDebug() << x << "," << totalTime;
        }

        return;
    }
};


#endif //VIDEOSYNTH_UNITEVALUATOR_H
