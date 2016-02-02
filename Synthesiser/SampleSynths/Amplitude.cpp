//
// Created by Alexander Simpson on 2016-02-02.
//

#include <Synthesiser/Units/ImageUnits.h>
#include "Amplitude.h"

void Amplitude_Ctor(Amplitude* synth) {
    World* world = synth->mWorld;

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

    // Draw a rectangle on the image which is proportional to the amplitude
    float* rectX = synth->mFloatParams[0];
    float* rectY = synth->mFloatParams[1];
    float* rectWidth = synth->mFloatParams[2];
    float* rectHeight = synth->mFloatParams[3];
    float** rectInFloatBuffer = new float*[4];
    int* rectColor = new int(qRgba(255, 255, 255, 255));
    int** colorIn = new int*[1];
    colorIn[0] = rectColor;
    rectInFloatBuffer[0] = rectX;
    rectInFloatBuffer[1] = rectY;
    rectInFloatBuffer[2] = rectWidth;
    rectInFloatBuffer[3] = rectHeight;
    RectFast* rect = new RectFast();
    Unit_Ctor(rect, world, rectInFloatBuffer, NULL, colorIn, NULL, NULL, resources);
    RectFast_Ctor(rect);

    // Output
    Draw* draw = new Draw();
    int** drawInFloatBuffer = new int*[1];
    drawInFloatBuffer[0] = new int(0);
    Unit_Ctor(draw, world, NULL, NULL, drawInFloatBuffer, NULL, resources, NULL);
    Draw_Ctor(draw);

    synth -> mNumberOfUnits = 5;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = acquirer;
    synth -> mUnits[1] = clear;
    synth -> mUnits[2] = rect;
    synth -> mUnits[3] = draw;
    synth -> mUnits[4] = releaser;
}