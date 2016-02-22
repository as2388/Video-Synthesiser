//
// Created by Alexander Simpson on 2016-01-10.
//

#include <Synthesiser/Units/ImageUnits.h>
#include <Synthesiser/Units/FloatUnits.h>
#include "FadingSquares.h"

void FadingSquares_Ctor(FadingSquares* synth) {
    World* world = synth -> mWorld;

    // Acquire/release required images
    int* id = new int(0);
    int** idBuffer = new int*[1];
    idBuffer[0] = id;
    QImage** resources = new QImage*[1];
    AcquireImage* acquirer = new AcquireImage();
    Unit_Ctor(acquirer, world, NULL, NULL, idBuffer, NULL, NULL, resources);
    AcquireImage_Ctor(acquirer);
    ReleaseImage* releaser = new ReleaseImage();
    Unit_Ctor(releaser, world, NULL, NULL, idBuffer, NULL, resources, NULL);
    ReleaseImage_Ctor(releaser);

    // Reset the acquired image
    ClearImage* clear = new ClearImage();
    Unit_Ctor(clear, world, NULL, NULL, NULL, NULL, resources, NULL);
    ClearImage_Ctor(clear);

    // Line from 255 to 0 over n frames
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

    int* colorA = new int(0);
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

    // Draw a rectangle to the image
    float* rectX = synth->mFloatParams[0];
    float* rectY = synth->mFloatParams[1];
    float* rectWidth = synth->mFloatParams[2];
    float* rectHeight = synth->mFloatParams[3];
    float** rectInFloatBuffer = new float*[5];
    rectInFloatBuffer[0] = rectX;
    rectInFloatBuffer[1] = rectY;
    rectInFloatBuffer[2] = rectWidth;
    rectInFloatBuffer[3] = rectHeight;
    int** intInBuffer = new int*[1];
    intInBuffer[0] = colorOutIntBuffer[0];
    RectFast* rect = new RectFast();
    Unit_Ctor(rect, world, rectInFloatBuffer, NULL, intInBuffer, NULL, NULL, resources);
    RectFast_Ctor(rect);

    // Output
    Draw* draw = new Draw();
    int** drawInFloatBuffer = new int*[1];
    drawInFloatBuffer[0] = synth->mIntParams[3];
    Unit_Ctor(draw, world, NULL, NULL, drawInFloatBuffer, NULL, resources, NULL);
    Draw_Ctor(draw);

    synth -> mNumberOfUnits = 8;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = acquirer;
    synth -> mUnits[1] = clear;
    synth -> mUnits[2] = line;
    synth -> mUnits[3] = fi;
    synth -> mUnits[4] = color;
    synth -> mUnits[5] = rect;
    synth -> mUnits[6] = draw;
    synth -> mUnits[7] = releaser;
}
