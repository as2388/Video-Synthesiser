//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_SYNTH_H
#define VIDEOSYNTH_SYNTH_H

#include <Graph/Graph.h>
#include "Unit.h"

struct Synth : Graph {
    int mNumberOfUnits;
    Unit** mUnits;
    int** mIntParams;
    float** mFloatParams;
    World* mWorld;

    bool mDone;

    void calc();

    virtual ~Synth() {
        for (int i = 0; i < mNumberOfUnits; i++) {
            delete mUnits[i];
        }
        delete mUnits;
    }
};

void Synth_Ctor(Synth* synth, World* world, float** floatParams, int** intParams/*, TODO: SynthDef */);

#endif //VIDEOSYNTH_SYNTH_H
