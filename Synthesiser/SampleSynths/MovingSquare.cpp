//
// Created by Alexander Simpson on 2016-04-20.
//

#include <Synthesiser/Units/ImageUnits.h>
#include <Synthesiser/Units/FloatUnits.h>
#include "MovingSquare.h"

void MovingSquare_Ctor(MovingSquare* synth) {
    World* world = synth -> mWorld;

    QImage** resources = new QImage*[1];
    ReadRef* readRef = new ReadRef();
    int** readRefInIntBuffer = new int*[1];
    readRefInIntBuffer[0] = synth->mIntParams[3];
    Unit_Ctor(readRef, world, NULL, NULL, readRefInIntBuffer, NULL, NULL, resources);
    ReadRef_Ctor(readRef);

    // Line from 255 to 0 over n frames
    float* lineXStart = synth->mFloatParams[2];
    float* lineXEnd = synth->mFloatParams[3];
    float* lineXSteps = synth->mFloatParams[6];
    float* lineXOut = new float(0);
    float** lineXInFloatBuffer = new float*[3];
    lineXInFloatBuffer[0] = lineXStart;
    lineXInFloatBuffer[1] = lineXEnd;
    lineXInFloatBuffer[2] = lineXSteps;
    float** lineXOutFloatBuffer = new float*[1];
    lineXOutFloatBuffer[0] = lineXOut;
    Line* lineX = new Line();
    Unit_Ctor(lineX, world, lineXInFloatBuffer, lineXOutFloatBuffer, NULL, NULL, NULL, NULL);
    Line_Ctor(lineX);

    float* lineYStart = synth->mFloatParams[4];
    float* lineYEnd = synth->mFloatParams[5];
    float* lineYSteps = synth->mFloatParams[6];
    float* lineYOut = new float(0);
    float** lineYInFloatBuffer = new float*[3];
    lineYInFloatBuffer[0] = lineYStart;
    lineYInFloatBuffer[1] = lineYEnd;
    lineYInFloatBuffer[2] = lineYSteps;
    float** lineYOutFloatBuffer = new float*[1];
    lineYOutFloatBuffer[0] = lineYOut;
    Line* lineY = new Line();
    Unit_Ctor(lineY, world, lineYInFloatBuffer, lineYOutFloatBuffer, NULL, NULL, NULL, NULL);
    Line_Ctor(lineY);

    int* colorR = synth->mIntParams[0];
    int* colorG = synth->mIntParams[1];
    int* colorB = synth->mIntParams[2];
    int** colorInIntBuffer = new int*[4];
    colorInIntBuffer[0] = colorR;
    colorInIntBuffer[1] = colorG;
    colorInIntBuffer[2] = colorB;
    colorInIntBuffer[3] = new int(255);
    int* colorOut = new int(0);
    int** colorOutIntBuffer = new int*[1];
    colorOutIntBuffer[0] = colorOut;
    Color* color = new Color();
    Unit_Ctor(color, world, NULL, NULL, colorInIntBuffer, colorOutIntBuffer, NULL, NULL);
    Color_Ctor(color);

    // Draw a rectangle to the image
    float* rectX = lineXOut;
    float* rectY = lineYOut;
    float* rectWidth = synth->mFloatParams[0];
    float* rectHeight = synth->mFloatParams[1];
    float** rectInFloatBuffer = new float*[4];
    rectInFloatBuffer[0] = rectX;
    rectInFloatBuffer[1] = rectY;
    rectInFloatBuffer[2] = rectWidth;
    rectInFloatBuffer[3] = rectHeight;
    int** intInBuffer = new int*[1];
    intInBuffer[0] = colorOutIntBuffer[0];
    RectFast* rect = new RectFast();
    Unit_Ctor(rect, world, rectInFloatBuffer, NULL, intInBuffer, NULL, NULL, resources);
    RectFast_Ctor(rect);

    synth -> mNumberOfUnits = 5;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = readRef;
    synth -> mUnits[1] = lineX;
    synth -> mUnits[2] = lineY;
    synth -> mUnits[3] = color;
    synth -> mUnits[4] = rect;
}
