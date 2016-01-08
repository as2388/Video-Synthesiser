#include <Synthesiser/Unit.h>
#include <Synthesiser/Units/UnitMacros.h>

struct Line : public Unit
{
    double mLevel, mSlope;
    float mEndLevel;
    int mCounter;
};

void Line_Ctor(Line* unit);