//
// Created by Alexander Simpson on 2015-11-29.
//


#include "World.h"

World::World(int poolSize, int imgWidth, int imgHeight) {
    this->graph = new Graph(); // Create graph root
    this->imagePool = new ImagePool(poolSize, imgWidth, imgHeight);
}

QImage* World::acquirePooledImage() {
    return this->imagePool->acquireImage();
}

void World::releasePooledImage(QImage* image) {
    this->imagePool->releaseImage(image);
}
