//
// Created by Alexander Simpson on 2015-11-29.
//

#include "Synth.h"

void Synth_Ctor(Synth* synth /*, TODO: SynthDef */) {
    float* lineStart = new float(0);
    float* lineEnd = new float(80);
    float* lineSteps = new float(80);
    float* lineOut = new float(0);
    float** lineInFloatBuffer = new float*[3];
    lineInFloatBuffer[0] = lineStart;
    lineInFloatBuffer[1] = lineEnd;
    lineInFloatBuffer[2] = lineSteps;
    float** lineOutFloatBuffer = new float*[1];
    lineOutFloatBuffer[0] = lineOut;
    Line* line = new Line();
    Unit_Ctor(line, lineInFloatBuffer, lineOutFloatBuffer, NULL, NULL);
    Line_Ctor(line);

    float* rectX = new float(10);
    float* rectY = new float(10);
    float* rectWidth = lineOut;
    float* rectHeight = new float(80);
    float** rectInFloatBuffer = new float*[4];
    rectInFloatBuffer[0] = rectX;
    rectInFloatBuffer[1] = rectY;
    rectInFloatBuffer[2] = rectWidth;
    rectInFloatBuffer[3] = rectHeight;
    QImage *rectInputImage = new QImage(100, 100, QImage::Format_ARGB32);
    rectInputImage->fill(qRgba(0, 0, 0, 0));
    QImage** rectInImageBuffer = new QImage*[1];
    rectInImageBuffer[0] = rectInputImage;
    QImage *rectOutputImage = new QImage(100, 100, QImage::Format_ARGB32);
    rectOutputImage->fill(qRgba(0, 0, 0, 0));
    QImage** rectOutImageBuffer = new QImage*[1];
    rectOutImageBuffer[0] = rectOutputImage;
    Rectangle* rectangle = new Rectangle();
    Unit_Ctor(rectangle, rectInFloatBuffer, NULL, rectInImageBuffer, rectOutImageBuffer);
    Rectangle_Ctor(rectangle);

    synth -> mNumberOfUnits = 2;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = line;
    synth -> mUnits[1] = rectangle;
}

inline void Synth_Compute_Unit(Unit* unit)
{
    (unit -> mCalcFunc)(unit, 1);
}

void Synth_Compute(Synth* synth) {
    for (int i = 0; i < synth -> mNumberOfUnits; i++) {
        Synth_Compute_Unit(synth -> mUnits[i]);
    }
}