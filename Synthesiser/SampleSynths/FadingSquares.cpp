//
// Created by Alexander Simpson on 2016-01-10.
//

#include <Synthesiser/Units/ImageUnits.h>
#include <Synthesiser/Units/FloatUnits.h>
#include "FadingSquares.h"

void FadingSquares_Ctor(FadingSquares* synth) {
    World* world = synth->mWorld;

    float* lineStart = new float(255);
    float* lineEnd = new float(0);
    float* lineSteps = synth->mFloatParams[4];
    float* lineOut = new float(0);
    float** lineInFloatBuffer = new float*[3];
    lineInFloatBuffer[0] = lineStart;
    lineInFloatBuffer[1] = lineEnd;
    lineInFloatBuffer[2] = lineSteps;
    float** lineOutFloatBuffer = new float*[1];
    lineOutFloatBuffer[0] = lineOut;
    Line* line = new Line();
    Unit_Ctor(line, world, lineInFloatBuffer, lineOutFloatBuffer, NULL, NULL, NULL, NULL);
    Line_Ctor(line);

    int * colorA = new int(0);
    int** colorABuffer = new int*[1];
    colorABuffer[0] = colorA;
    FloatToInt* fi = new FloatToInt();
    Unit_Ctor(fi, world, lineOutFloatBuffer, NULL, NULL, colorABuffer, NULL, NULL);
    FloatToInt_Ctor(fi);

    int* colorR = synth->mIntParams[0];
    int* colorG = synth->mIntParams[1];
    int* colorB = synth->mIntParams[2];
    int** colorInIntBuffer = new int*[4];
    colorInIntBuffer[0] = colorR;
    colorInIntBuffer[1] = colorG;
    colorInIntBuffer[2] = colorB;
    colorInIntBuffer[3] = colorABuffer[0];
    int* colorOut = new int(0);
    int** colorOutIntBuffer = new int*[1];
    colorOutIntBuffer[0] = colorOut;
    Color* color = new Color();
    Unit_Ctor(color, world, NULL, NULL, colorInIntBuffer, colorOutIntBuffer, NULL, NULL);
    Color_Ctor(color);

    float* rectX = synth->mFloatParams[0];
    float* rectY = synth->mFloatParams[1];
    float* rectWidth = synth->mFloatParams[2];
    float* rectHeight = synth->mFloatParams[3];
    float** rectInFloatBuffer = new float*[5];
    rectInFloatBuffer[0] = rectX;
    rectInFloatBuffer[1] = rectY;
    rectInFloatBuffer[2] = rectWidth;
    rectInFloatBuffer[3] = rectHeight;
    rectInFloatBuffer[4] = lineOutFloatBuffer[0];
    QImage *rectInputImage = new QImage(800, 600, QImage::Format_ARGB32); // TODO: How am I going to handle image size?
    rectInputImage->fill(qRgba(0, 0, 0, 0));
    QImage** rectInImageBuffer = new QImage*[1];
    rectInImageBuffer[0] = rectInputImage;
    QImage *rectOutputImage = new QImage(800, 600, QImage::Format_ARGB32);
    rectOutputImage->fill(qRgba(0, 0, 0, 0));
    QImage** rectOutImageBuffer = new QImage*[1];
    rectOutImageBuffer[0] = rectOutputImage;
    CopyRegion* copyRegion = new CopyRegion();
    QImage** inPayload = new QImage*[1];
    inPayload[0] = world->mUserImages[0];
    Unit_Ctor(copyRegion, world, rectInFloatBuffer, NULL, NULL, NULL, inPayload, rectOutImageBuffer);
    CopyRegion_Ctor(copyRegion);
//    RectFast* rectangle = new RectFast();
//    Unit_Ctor(rectangle, world, rectInFloatBuffer, NULL, colorOutIntBuffer, NULL, NULL, rectOutImageBuffer);
//    RectFast_Ctor(rectangle);

    ClearImage* clear = new ClearImage();
    Unit_Ctor(clear, world, NULL, NULL, NULL, NULL, rectOutImageBuffer, NULL);
    ClearImage_Ctor(clear);

    Draw* draw = new Draw();
    int** drawInFloatBuffer = new int*[1];
    drawInFloatBuffer[0] = synth->mIntParams[3];
    Unit_Ctor(draw, world, NULL, NULL, drawInFloatBuffer, NULL, rectOutImageBuffer, NULL);
    Draw_Ctor(draw);

    synth -> mNumberOfUnits = 6;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = clear;
    synth -> mUnits[1] = line;
    synth -> mUnits[2] = fi;
    synth -> mUnits[3] = color;
    synth -> mUnits[4] = copyRegion;
    synth -> mUnits[5] = draw;
}
