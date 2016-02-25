//
// Created by Alexander Simpson on 2016-01-10.
//

#include <Synthesiser/Units/FloatUnits.h>
#include <Synthesiser/Units/ImageUnits.h>
#include "Kaleidoscope.h"

void Kaleidoscope_Ctor(Kaleidoscope* synth, World* world) {
    QImage** lookOutImgBuffer = new QImage*[1];

    AcquireImage* acquirer = new AcquireImage();
    int** idBuffer = new int*[1];
    idBuffer[0] = new int(0);
    Unit_Ctor(acquirer, world, NULL, NULL, idBuffer, NULL, NULL, lookOutImgBuffer);
    AcquireImage_Ctor(acquirer);

    int** readFromBuffer = new int*[1];
    readFromBuffer[0] = new int(1);
    Read* read = new Read();
    Unit_Ctor(read, world, NULL, NULL, readFromBuffer, NULL, NULL, lookOutImgBuffer);
    Read_Ctor(read);

    Symm8* symm = new Symm8();
    Unit_Ctor(symm, world, NULL, NULL, NULL, NULL, lookOutImgBuffer, lookOutImgBuffer);
    Symm8_Ctor(symm);

    Nuke* nuke = new Nuke();
    Unit_Ctor(nuke, world, NULL, NULL, NULL, NULL, lookOutImgBuffer, NULL);
    Nuke_Ctor(nuke);

    Draw* draw = new Draw();
    int** drawInFloatBuffer = new int*[1];
    drawInFloatBuffer[0] = new int(0);
    Unit_Ctor(draw, world, NULL, NULL, drawInFloatBuffer, NULL, lookOutImgBuffer, NULL);
    Draw_Ctor(draw);
    ReleaseImage* releaser = new ReleaseImage();
    Unit_Ctor(releaser, world, NULL, NULL, idBuffer, NULL, lookOutImgBuffer, NULL);
    ReleaseImage_Ctor(releaser);

    synth -> mNumberOfUnits = 5;
    synth -> mUnits = new Unit*[synth -> mNumberOfUnits];

    synth -> mUnits[0] = acquirer;
    synth -> mUnits[1] = read;
    synth -> mUnits[2] = symm;
    synth -> mUnits[3] = draw;
    synth -> mUnits[4] = releaser;
}