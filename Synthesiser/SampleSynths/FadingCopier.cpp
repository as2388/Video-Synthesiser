//
// Created by Alexander Simpson on 2016-02-02.
//

#include <Synthesiser/Units/FloatUnits.h>
#include <Synthesiser/Units/ImageUnits.h>
#include "FadingCopier.h"

void FadingCopier_Ctor(FadingCopier* synth) {
    World* world = synth->mWorld;

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

    // Copy a region of the image; with transparency
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
    CopyRegion* copyRegion = new CopyRegion();
    QImage** inPayload = new QImage*[1];
    inPayload[0] = world->mUserImages[*synth->mIntParams[4]];
    Unit_Ctor(copyRegion, world, rectInFloatBuffer, NULL, NULL, NULL, inPayload, resources);
    CopyRegion_Ctor(copyRegion);

    // Output
    Draw* draw = new Draw();
    int** drawInFloatBuffer = new int*[1];
    drawInFloatBuffer[0] = synth->mIntParams[3];
    Unit_Ctor(draw, world, NULL, NULL, drawInFloatBuffer, NULL, resources, NULL);
    Draw_Ctor(draw);

    synth -> mNumberOfUnits = 6;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = acquirer;
    synth -> mUnits[1] = clear;
    synth -> mUnits[2] = line;
    synth -> mUnits[3] = copyRegion;
    synth -> mUnits[4] = draw;
    synth -> mUnits[5] = releaser;
}