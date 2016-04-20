//
// Created by Alexander Simpson on 2016-02-01.
//

#ifndef VIDEOSYNTH_IMAGEPOOL_H
#define VIDEOSYNTH_IMAGEPOOL_H

#include <qimage.h>
#include <stack>

class ImagePool {
private:
    int imgWidth;
    int imgHeight;
    std::stack<QImage*> freePool;
public:
    ImagePool(int poolSize, int imgWidth, int imgHeight);
    QImage* acquireImage();
    void releaseImage(QImage* image);
};


#endif //VIDEOSYNTH_IMAGEPOOL_H
