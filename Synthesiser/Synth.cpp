//
// Created by Alexander Simpson on 2015-11-29.
//

#include <World.h>
#include "Synth.h"

void Synth_Ctor(Synth* synth, World* world /*, TODO: SynthDef */) {
    float* lineStart = new float(0);
    float* lineEnd = new float(60);
    float* lineSteps = new float(60);
    float* lineOut = new float(0);
    float** lineInFloatBuffer = new float*[3];
    lineInFloatBuffer[0] = lineStart;
    lineInFloatBuffer[1] = lineEnd;
    lineInFloatBuffer[2] = lineSteps;
    float** lineOutFloatBuffer = new float*[1];
    lineOutFloatBuffer[0] = lineOut;
    Line* line = new Line();
    Unit_Ctor(line, world, lineInFloatBuffer, lineOutFloatBuffer, NULL, NULL);
    Line_Ctor(line);

    float* rectX = new float(10);
    float* rectY = new float(10);
    float* rectWidth = lineOut; //new float(60);
    float* rectHeight = lineOut; //new float(60);
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
    Unit_Ctor(rectangle, world, rectInFloatBuffer, NULL, rectInImageBuffer, rectOutImageBuffer);
    Rectangle_Ctor(rectangle);
    rectangle -> color = qRgba(255, 0, 0, 127);

    float* rect2X = new float(30);
    float* rect2Y = new float(30);
    float* rect2Width = lineOut; //new float(60);
    float* rect2Height = lineOut; // new float(60);
    float** rect2InFloatBuffer = new float*[4];
    rect2InFloatBuffer[0] = rect2X;
    rect2InFloatBuffer[1] = rect2Y;
    rect2InFloatBuffer[2] = rect2Width;
    rect2InFloatBuffer[3] = rect2Height;
    QImage *rect2InputImage = new QImage(100, 100, QImage::Format_ARGB32);
    rect2InputImage->fill(qRgba(0, 0, 0, 0));
    QImage** rect2InImageBuffer = new QImage*[1];
    rect2InImageBuffer[0] = rect2InputImage;
    QImage *rect2OutputImage = new QImage(100, 100, QImage::Format_ARGB32);
    rect2OutputImage->fill(qRgba(0, 0, 0, 0));
    QImage** rect2OutImageBuffer = new QImage*[1];
    rect2OutImageBuffer[0] = rect2OutputImage;
    Rectangle* rectangle2 = new Rectangle();
    Unit_Ctor(rectangle2, world, rect2InFloatBuffer, NULL, rect2InImageBuffer, rect2OutImageBuffer);
    Rectangle_Ctor(rectangle2);
    rectangle2 -> color = qRgba(0, 0, 255, 127);

    AlphaBlend* alphaBlend = new AlphaBlend();
    QImage** alphaBlendInputImages = new QImage*[2];
    alphaBlendInputImages[0] = rectOutImageBuffer[0];
    alphaBlendInputImages[1] = rect2OutImageBuffer[0];
    QImage** alphaBlendOutputImage = new QImage*[1];
    alphaBlendOutputImage[0] = new QImage(100, 100, QImage::Format_ARGB32);
    Unit_Ctor(alphaBlend, world, NULL, NULL, alphaBlendInputImages, alphaBlendOutputImage);
    AlphaBlend_Ctor(alphaBlend);


    Draw* draw = new Draw();
    Unit_Ctor(draw, world, NULL, NULL, alphaBlendOutputImage, NULL);
    Draw_Ctor(draw);

    synth -> mNumberOfUnits = 5;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = line;
    synth -> mUnits[1] = rectangle;
    synth -> mUnits[2] = rectangle2;
    synth -> mUnits[3] = alphaBlend;
    synth -> mUnits[4] = draw;
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