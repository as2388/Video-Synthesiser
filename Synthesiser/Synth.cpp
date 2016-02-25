//
// Created by Alexander Simpson on 2015-11-29.
//

#include <World/World.h>
#include "Synth.h"
#include "Synthesiser/Units/Units.h"
#include <stdlib.h>


void Synth_Ctor(Synth* synth, World* world, float** floatParams, int** intParams /*, TODO: SynthDef */) {
    synth->mDone = false;
    synth->mWorld = world;
    synth->mFloatParams = floatParams;
    synth->mIntParams = intParams;
}

inline void Synth_Compute_Unit(Unit* unit)
{
    (unit -> mCalcFunc)(unit, 1);
}

void Synth::calc() {
    Graph::calc();

    for (int i = 0; i < this -> mNumberOfUnits; i++) {
        Synth_Compute_Unit(this -> mUnits[i]);

        if (this->mUnits[i]->mDone) {
            this->mDone = true;
        }
    }

    if (this->mDone) {
        Graph::remove();
    }
}
