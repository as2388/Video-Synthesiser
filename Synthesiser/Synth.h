//
// Created by Alexander Simpson on 2015-11-29.
//

#ifndef VIDEOSYNTH_SYNTH_H
#define VIDEOSYNTH_SYNTH_H


#include "Unit.h"

struct Synth {
    int mNumberOfUnits;
    Unit** mUnits;
};

void Synth_Ctor(Synth* synth /*, TODO: SynthDef */);
void Synth_Compute(Synth* synth);


#endif //VIDEOSYNTH_SYNTH_H
