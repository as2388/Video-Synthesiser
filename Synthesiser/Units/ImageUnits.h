#include <Synthesiser/Unit.h>

struct Rectangle: public Unit {
    QImage *inputImage, *outputImage;
    QPainter *copier;
    uint color;
};
void Rectangle_Ctor(Rectangle* unit);

struct AlphaBlend: public Unit {
    QImage *inputImageUnder, *inputImageOver, *outputImage;
};
void AlphaBlend_Ctor(AlphaBlend* unit);
int blendHelper(double ca, double aa, double cb, double ab);

struct Color: public Unit {

};
void Color_Ctor(Color* unit);

struct Symm8: public Unit {
    QImage *inputImage, *outputImage;
};
void Symm8_Ctor(Symm8* unit);

struct FloatToInt: public Unit{

};
void FloatToInt_Ctor(FloatToInt* unit);

struct Draw: public Unit
{
    QImage *inputImage;
};
void Draw_Ctor(Draw* draw);

struct Look: public Unit {
    QImage* outputImage;
    QPainter* copier;
};
void Look_Ctor(Look* look);