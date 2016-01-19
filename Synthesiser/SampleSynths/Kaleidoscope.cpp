//
// Created by Alexander Simpson on 2016-01-10.
//

#include <Synthesiser/Units/FloatUnits.h>
#include <Synthesiser/Units/ImageUnits.h>
#include "Kaleidoscope.h"

void Kaleidoscope_Ctor(Kaleidoscope* synth, World* world) {
    QImage** lookOutImgBuffer = new QImage*[1];
//    QImage *lookOutputImage = new QImage(800, 800, QImage::Format_ARGB32);
//    lookOutputImage->fill(qRgba(0, 0, 0, 0));
//    lookOutImgBuffer[0] = lookOutputImage;
//    Look* look = new Look();
//    Unit_Ctor(look, world, NULL, NULL, NULL, NULL, NULL, lookOutImgBuffer);
//    Look_Ctor(look);

    lookOutImgBuffer[0] = world->mImageBuffers[1];
    QImage** symmOutImgBuffer = new QImage*[1];
    QImage *symmOutputImage = new QImage(800, 800, QImage::Format_ARGB32);
    symmOutputImage->fill(qRgba(0, 0, 0, 0));
    symmOutImgBuffer[0] = symmOutputImage;
    Symm8* symm = new Symm8();
    Unit_Ctor(symm, world, NULL, NULL, NULL, NULL, lookOutImgBuffer, symmOutImgBuffer);
    Symm8_Ctor(symm);

    Draw* draw = new Draw();
    int** drawInFloatBuffer = new int*[1];
    drawInFloatBuffer[0] = new int(0);
    lookOutImgBuffer[0] = world->mImageBuffers[1];
    Unit_Ctor(draw, world, NULL, NULL, drawInFloatBuffer, NULL, symmOutImgBuffer, NULL);
    Draw_Ctor(draw);

    synth -> mNumberOfUnits = 2;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = symm;
    synth -> mUnits[1] = draw;
}