//
// Created by Alexander Simpson on 2016-02-01.
//

#include "ImagePool.h"
#include <QDebug>

ImagePool::ImagePool(int poolSize, int imgWidth, int imgHeight) {
    this->imgWidth = imgWidth;
    this->imgHeight = imgHeight;

    for (int i = 0; i < poolSize; i++) {
        QImage* img = new QImage(imgWidth, imgHeight, QImage::Format_ARGB32);
        this->freePool.push(img);
    }
}

QImage* ImagePool::acquireImage() {
    if (this->freePool.empty()) {
        return new QImage(imgWidth, imgHeight, QImage::Format_ARGB32);
    } else {
        QImage* out = this->freePool.top();
        this->freePool.pop();
        return out;
    }
}

void ImagePool::releaseImage(QImage* image) {
    this->freePool.push(image);
}
