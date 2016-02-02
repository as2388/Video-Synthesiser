#include <Synthesiser/Unit.h>

struct AcquireImage: public Unit {

};
void AcquireImage_Ctor(AcquireImage* unit);

struct ReleaseImage: public Unit {

};
void ReleaseImage_Ctor(ReleaseImage* unit);

struct Rectangle: public Unit {
    QImage *inputImage, *outputImage;
    QPainter *copier;
    uint color;
};
void Rectangle_Ctor(Rectangle* unit);

struct RectFast: public Unit {

};
void RectFast_Ctor(RectFast* unit);

struct CopyImage: public Unit {

};
void CopyImage_Ctor(CopyImage* unit);

struct CopyImageFast: public Unit {

};
void CopyImageFast_Ctor(CopyImageFast* unit);

struct CopyImageVeryFast: public Unit {

};
void CopyImageVeryFast_Ctor(CopyImageVeryFast* unit);

struct ClearImage: public Unit {

};
void ClearImage_Ctor(ClearImage* unit);

struct ClearImageFast: public Unit {

};

void ClearImageFast_Ctor(ClearImageFast* unit);

struct AlphaBlend: public Unit {
    QImage *inputImageUnder, *inputImageOver, *outputImage;
};

void AlphaBlend_Ctor(AlphaBlend* unit);
int blendHelper(double ca, double aa, double cb, double ab);

struct Color: public Unit {

};
void Color_Ctor(Color* unit);

struct CopyRegion: public Unit {

};
void CopyRegion_Ctor(CopyRegion* unit);

struct Symm8: public Unit {
    QImage *inputImage, *outputImage;
};
void Symm8_Ctor(Symm8* unit);

struct FloatToInt: public Unit{

};
void FloatToInt_Ctor(FloatToInt* unit);

struct Draw: public Unit
{

};
void Draw_Ctor(Draw* draw);

struct Look: public Unit {
    QImage* outputImage;
    QPainter* copier;
};
void Look_Ctor(Look* look);