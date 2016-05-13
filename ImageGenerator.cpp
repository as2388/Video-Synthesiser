//
// Created by Alexander Simpson on 2016-02-22.
//

#include <Graph/Graph.h>
#include <QPainter>
#include <World/World.h>
#include <UserGraphics/UserGraphics.h>
#include <Synthesiser/SampleSynths/Kaleidoscope.h>
#include "ImageGenerator.h"
#include <Synthesiser/SampleSynths/MovingSquare.h>
#include <sys/time.h>
#include <qtextstream.h>
#include <iostream>

Graph* graph = new Graph();
Kaleidoscope* kaleidoscope;

ImageGenerator::ImageGenerator() {
    srand(time(0));

    world = new World(20, 800, 600);
    world->mImageBuffers = new QImage*[2];
    world->mImageBuffers[0] = world->acquirePooledImage();
    world->mImageBuffers[1] = world->acquirePooledImage();
    world->mImageBuffers[0]->fill(qRgba(0, 0, 0, 255));
    world->mImageBuffers[1]->fill(qRgba(0, 0, 0, 255));
    world->mNumDisplayBuffers = 2;

    world -> mUserImages = new QImage*[5];
    UserGraphics().loadUserGraphics(world->mUserImages, 4, 0);

    Graph* g = new Graph();
    kaleidoscope = new Kaleidoscope();
    Kaleidoscope_Ctor(kaleidoscope, world);
    g->setFirstChild(kaleidoscope);
    world->graph->setFirstChild(kaleidoscope);
}

float randf(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float img = 0;
long int timeCompute(timeval startTime, timeval endTime) {
    long int start = (startTime.tv_sec) * 1000 + (startTime.tv_usec) / 1000;
    long int end = (endTime.tv_sec) * 1000 + (endTime.tv_usec) / 1000;

    return end - start;
}

int first = 0;
void ImageGenerator::run() {
    QImage* nextOutput;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {

        MovingSquare *node = new MovingSquare();
        int **intParams = new int *[4];
        float **floatParams = new float *[7];


        intParams[0] = new int(int(randf(80, 255))); // R
        intParams[1] = new int(int(randf(80, 255))); // G
        intParams[2] = new int(int(randf(80, 255))); // B
        intParams[3] = new int(1); // Image buffer to write to

        floatParams[0] = new float(randf(40, 65)); // width
        floatParams[1] = floatParams[0]; // height
        floatParams[2] = new float(500); // xstart
        floatParams[3] = new float(randf(0, 500)); // xend
        floatParams[4] = new float(400); // ystart
        floatParams[5] = new float(1); // yend
        floatParams[6] = new float(20.0);

        Synth_Ctor(node, world, floatParams, intParams);
        MovingSquare_Ctor(node);
        if (kaleidoscope->firstChild) {
            kaleidoscope->firstChild->appendSibling(node);
        } else {
            kaleidoscope->setFirstChild(node);
        }

        for (int i = 0; i < world->mNumDisplayBuffers; i++) {
            world->mImageBuffers[i]->fill(qRgba(0, 0, 0, 255));
        }

        world->graph->calc();

        nextOutput = world->acquirePooledImage();
        memcpy(nextOutput->bits(), world->mImageBuffers[0]->bits(),
               (size_t) world->mImageBuffers[0]->bytesPerLine() * world->mImageBuffers[0]->height());


        while (!(queue->bounded_push(nextOutput))){
            usleep(2000);
        }
    }


#pragma clang diagnostic pop
}