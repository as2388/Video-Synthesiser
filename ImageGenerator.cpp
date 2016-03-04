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
#include <Synthesiser/SampleSynths/FadingCopier.h>

Graph* graph = new Graph();
Kaleidoscope* kaleidoscope;

ImageGenerator::ImageGenerator() {
    srand(time(0));

    world = new World(20, 800, 450);
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
    //g->setFirstChild(kaleidoscope);
    world->graph->setFirstChild(graph);
}

float randf(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float img = 0;
void ImageGenerator::run() {
    QImage* nextOutput;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        //for (int z = 0; z < 2; z++) {
        img+=0.02;
            FadingCopier *node = new FadingCopier();
            //FadingSquares* node = new FadingSquares();

            int **intParams = new int *[5];
            intParams[0] = new int(int(randf(80, 255))); // R
            intParams[1] = new int(int(randf(80, 255))); // G
            intParams[2] = new int(int(randf(80, 255))); // B
            intParams[3] = new int(0); // Image buffer to write to
            intParams[4] = new int(int((randf(0.3, 0.7) + img)) % 4); // User image to read from

            float **floatParams = new float *[5];
            floatParams[2] = new float(randf(70, 300)); // width
            floatParams[3] = floatParams[2]; // height
            floatParams[0] = new float(randf(0, 800 - *floatParams[2])); // x
            floatParams[1] = new float(randf(0, 450 - *floatParams[3])); // y
            // Move to upper-right half if necessary by mirroring over y = - x
            /*if (*floatParams[0] < *floatParams[1]) {
                float *temp = floatParams[0];
                floatParams[0] = floatParams[1];
                floatParams[1] = temp;
            }*/

            floatParams[4] = new float(15); // length of fade in frames
            Synth_Ctor(node, world, floatParams, intParams);
            FadingCopier_Ctor(node);
            //FadingSquares_Ctor(node);
            if (graph->firstChild) {
                graph->firstChild->appendSibling(node);
            } else {
                graph->setFirstChild(node);
            }
        //}

        //    add = 15;
        //}

        //    add--;

        for (int i = 0; i < world->mNumDisplayBuffers; i++) {
            world->mImageBuffers[i]->fill(qRgba(0, 0, 0, 255));
        }

        world->graph->calc();

        nextOutput = world->acquirePooledImage();
        memcpy(nextOutput->bits(), world->mImageBuffers[0]->bits(),
               (size_t) world->mImageBuffers[0]->bytesPerLine() * world->mImageBuffers[0]->height());
        //std::cout << "pushing:" << nextOutput << "\n";
        while (!(queue->bounded_push(nextOutput))){
            //usleep(2000);
        }
    }
#pragma clang diagnostic pop
}