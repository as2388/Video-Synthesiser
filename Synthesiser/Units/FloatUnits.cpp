//
// Created by Alexander Simpson on 2016-01-08.
//

#include "FloatUnits.h"

static inline void Line_next_loop(Line * unit, int & counter, int remain, double & level)
{
    float *out = ZOUT(0);
    double slope = unit->mSlope;

    do {
        if (counter==0) {
            int nsmps = remain;
            remain = 0;
            float endlevel = unit->mEndLevel;
            LOOP(nsmps,
                 ZXP(out) = endlevel;
            );
        } else {
            int nsmps = sc_min(remain, counter);
            counter -= nsmps;
            remain -= nsmps;
            LOOP(nsmps,
                 ZXP(out) = level;
                         level += slope;
            );
            if (counter == 0) {
                unit->mDone = true;
                //int doneAction = (int)ZIN0(3);
                //DoneAction(doneAction, unit); TODO: Find out what this does
            }
        }
    } while (remain);

}

void Line_next(Line *unit, int inNumSamples)
{
    double level = unit->mLevel;
    int counter = unit->mCounter;
    Line_next_loop(unit, counter, inNumSamples, level);
    unit->mCounter = counter;
    unit->mLevel = level;
}

void Line_Ctor(Line* unit)
{
    SETCALC(Line_next);
    double start = ZIN0(0);
    double end = ZIN0(1);
    double dur = ZIN0(2);

    int counter = (int)(dur * unit->mRate->mSampleRate + .5f);
    unit->mCounter = sc_max(1, counter);
    if(counter == 0){
        unit->mLevel = end;
        unit->mSlope = 0.;
    } else {
        unit->mLevel = start;
        unit->mSlope = (end - start) / unit->mCounter;
        unit->mLevel += unit->mSlope;
    }
    unit->mEndLevel = end;
    ZOUT0(0) = unit->mLevel;
}
