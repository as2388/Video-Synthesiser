#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <stdio.h>
#include <Synthesiser/Unit.h>
#include <QDebug>
#include <Synthesiser/Synth.h>
#include <Synthesiser/SampleSynths/Amplitude.h>

QImage** imageBuffer = new QImage*[2];
Graph* graph = new Graph();
World* world;
float **floatParams = new float *[4];

MainWindow::~MainWindow()
{
    delete ui;
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

    Graph* g = new Graph();
    g->setFirstChild(graph);
    floatParams[0] = new float(0); // x
    floatParams[1] = new float(3); // y
    floatParams[2] = new float(500); // width
    floatParams[3] = new float(14); // height
    Amplitude* ampSynth = new Amplitude();
    Synth_Ctor(ampSynth, world, floatParams, NULL);
    Amplitude_Ctor(ampSynth);
    graph->appendSibling(ampSynth);
    world->graph->setFirstChild(g);

    // Set a timer to update the displayed image every 1/20s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(50);
}

/**
 * @brief MainWindow::advanceDisplayedImage Advance the pointer to the image to be rendered
 * by one position, and force a window repaint.
 */
void MainWindow::advanceDisplayedImage() {
    // Reset display buffer
    imageBuffer[0]->fill(qRgba(0, 0, 0, 255));

    // Compute and display next graph frame
    world->graph->calc();
    this->update();
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

// Updates the rectangle synth's parameters based on the given amplitude
void MainWindow::updateAmplitude(float newAmplitude) {
    // Amplitude is between 0 and 1. Normalise it to fill available image width.
    newAmplitude *= imageBuffer[0]->width() / 2;

    *floatParams[0] = (imageBuffer[0]->width() / 2) - newAmplitude; // Rectangle x
    *floatParams[2] = newAmplitude * 2; // Rectangle width
}
