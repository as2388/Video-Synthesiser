#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <stdio.h>
#include <Synthesiser/Unit.h>
#include <QDebug>
#include <Synthesiser/Synth.h>
#include <Synthesiser/SampleSynths/FadingSquares.h>
#include <Synthesiser/SampleSynths/Kaleidoscope.h>
#include <UserGraphics/UserGraphics.h>
#include <qlabel.h>
#include <World/World.h>
#include <Synthesiser/SampleSynths/FadingCopier.h>
#include <Synthesiser/SampleSynths/Amplitude.h>

QImage** imageBuffer = new QImage*[2];
World* world;
Graph* graph = new Graph();
QElapsedTimer* frameTimer = new QElapsedTimer();
Amplitude* ampSynth;
float **floatParams = new float *[4];

float randf(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(0));

    world = new World(4, 800, 20);
    imageBuffer[0] = world->acquirePooledImage();
    imageBuffer[1] = world->acquirePooledImage();
    imageBuffer[0]->fill(qRgba(0, 0, 0, 255));
    imageBuffer[1]->fill(qRgba(0, 0, 0, 255));
    world->mImageBuffers = imageBuffer;
    world->mDisplayBuffers = new QPainter*[2];
    world->mDisplayBuffers[0] = new QPainter(imageBuffer[0]);
    world->mDisplayBuffers[1] = new QPainter(imageBuffer[1]);
    world->mNumDisplayBuffers = 2;

    //world -> mUserImages = new QImage*[5];
    //UserGraphics().loadUserGraphics(world->mUserImages, 3, 0);

    Graph* g = new Graph();
    g->setFirstChild(graph);
    floatParams[0] = new float(0); // x
    floatParams[1] = new float(3); // y
    floatParams[2] = new float(500); // width
    floatParams[3] = new float(14); // height
    ampSynth = new Amplitude();
    Synth_Ctor(ampSynth, world, floatParams, NULL);
    Amplitude_Ctor(ampSynth);
    graph->appendSibling(ampSynth);

    //Kaleidoscope* kaleidoscope = new Kaleidoscope();
    //Kaleidoscope_Ctor(kaleidoscope, world);
    //graph->appendSibling(kaleidoscope);

    world->graph->setFirstChild(g);

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(50);
}

/**
 * @brief MainWindow::advanceDisplayedImage Advance the pointer to the image to be rendered
 * by one position, and force a window repaint.
 */
float wth = 0;
void MainWindow::advanceDisplayedImage() {
    frameTimer -> restart();

    float ampVal = randf(0, 300);

    *floatParams[0] = imageBuffer[0]->width() / 2 - ampVal;
    *floatParams[2] = ampVal * 2;

    wth += 1;

    imageBuffer[0]->fill(qRgba(0, 0, 0, 255));
    world->graph->calc();

    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::paintEvent Draws the image which is currently to be displayed to the screen.
 * @param event
 */

void MainWindow::paintEvent(QPaintEvent *event) {
    // Draw the image to the screen.
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 15), QPixmap::fromImage(*imageBuffer[0]));
    painter.end();
}


