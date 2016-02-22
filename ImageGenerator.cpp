//
// Created by Alexander Simpson on 2016-02-22.
//

#include <Graph/Graph.h>
#include <QPainter>
#include <World/World.h>
#include <UserGraphics/UserGraphics.h>
#include <Synthesiser/SampleSynths/Kaleidoscope.h>
#include <Synthesiser/SampleSynths/FadingSquares.h>
#include "ImageGenerator.h"
#include <iostream>

QImage** imageBuffer = new QImage*[2];
Graph* graph = new Graph();

ImageGenerator::ImageGenerator() {
    srand(time(0));

    world = new World(10, 800, 600);
    imageBuffer[0] = world->acquirePooledImage();
    imageBuffer[1] = world->acquirePooledImage();
    imageBuffer[0]->fill(qRgba(0, 0, 0, 255));
    imageBuffer[1]->fill(qRgba(0, 0, 0, 255));
    world->mImageBuffers = imageBuffer;
    world->mDisplayBuffers = new QPainter*[2];
    world->mDisplayBuffers[0] = new QPainter(imageBuffer[0]);
    world->mDisplayBuffers[1] = new QPainter(imageBuffer[1]);
    world->mNumDisplayBuffers = 2;

    world -> mUserImages = new QImage*[5];
    UserGraphics().loadUserGraphics(world->mUserImages, 3, 0);

    Graph* g = new Graph();
    g->setFirstChild(graph);
    Kaleidoscope* kaleidoscope = new Kaleidoscope();
    Kaleidoscope_Ctor(kaleidoscope, world);
    //graph->appendSibling(kaleidoscope);
    world->graph->setFirstChild(g);
}

float randf(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void ImageGenerator::run() {
    QImage* nextOutput;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        for (int z = 0; z < 10; z++) {
            FadingSquares *node = new FadingSquares();

            int **intParams = new int *[5];
            intParams[0] = new int(int(randf(80, 255))); // R
            intParams[1] = new int(int(randf(80, 255))); // G
            intParams[2] = new int(int(randf(80, 255))); // B
            intParams[3] = new int(0); // Image buffer to write to
            //intParams[4] = new int(randf(0, 1) + img); // User image to read from

            float **floatParams = new float *[5];
            floatParams[0] = new float(randf(0, 800 - 200)); // x
            floatParams[1] = new float(randf(0, 600 - 200)); // y
            // Move to upper-right half if necessary by mirroring over y = - x
            /*if (*floatParams[0] < *floatParams[1]) {
                float *temp = floatParams[0];
                floatParams[0] = floatParams[1];
                floatParams[1] = temp;
            } */
            floatParams[2] = new float(randf(70, 200)); // width
            floatParams[3] = floatParams[2]; // height
            floatParams[4] = new float(15); // length of fade in frames
            Synth_Ctor(node, world, floatParams, intParams);
            FadingSquares_Ctor(node);
            graph->appendSibling(node);
        }

        //    add = 15;
        //}

        //    add--;

        imageBuffer[0]->fill(qRgba(0, 0, 0, 255));
        world->graph->calc();

        nextOutput = world->acquirePooledImage();
        //world->releasePooledImage(nextOutput);
        memcpy(nextOutput->bits(), imageBuffer[0]->bits(), (size_t) imageBuffer[0]->bytesPerLine() * imageBuffer[0]->height());
        while (!queue->bounded_push(nextOutput)){
            //sleep(1);
//            qDebug() << "bounded push fail";
        }
        //std::cout << "loop\n";
    }
#pragma clang diagnostic pop
}