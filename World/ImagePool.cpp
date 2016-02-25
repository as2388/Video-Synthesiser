//
// Created by Alexander Simpson on 2016-02-01.
//

#include "ImagePool.h"
#include <QDebug>

ImagePool::ImagePool(int poolSize, int imgWidth, int imgHeight) {
    this->pool = new QImage*[poolSize];
    for (int i = 0; i < poolSize; i++) {
        this->pool[i] = new QImage(imgWidth, imgHeight, QImage::Format_ARGB32);
        this->freePool.push(this->pool[i]);
    }
}

QImage* ImagePool::acquireImage() {
    QImage* out = this->freePool.top();
    this->freePool.pop();
    //qDebug() << "returning" << out;
    return out;
}

void ImagePool::releaseImage(QImage* image) {
    this->freePool.push(image);
}
