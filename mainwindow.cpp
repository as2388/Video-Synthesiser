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

QImage** imageBuffer = new QImage*[2];
World* world;
Graph* graph = new Graph();
QElapsedTimer* frameTimer = new QElapsedTimer();
QLabel* imageLabel;

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

    imageLabel = new QLabel(this);
    imageLabel->setMinimumSize(800, 600);
    imageLabel->show();
    setCentralWidget(imageLabel);

    world = new World(5, 800, 600);
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

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(50);
}

/**
 * @brief MainWindow::advanceDisplayedImage Advance the pointer to the image to be rendered
 * by one position, and force a window repaint.
 */
int add = 0;
float img = 0.0;
void MainWindow::advanceDisplayedImage() {
    frameTimer -> restart();

    //for (int i = 0; i < 1000; i++) {
    //if (add == 0) {
    img += 0.01;
        FadingCopier *node = new FadingCopier();

        int **intParams = new int *[5];
        intParams[0] = new int(int(randf(80, 255))); // R
        intParams[1] = new int(int(randf(80, 255))); // G
        intParams[2] = new int(int(randf(80, 255))); // B
        intParams[3] = new int(0); // Image buffer to write to
        intParams[4] = new int(randf(0, 1) + img); // User image to read from

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
        FadingCopier_Ctor(node);
        graph->appendSibling(node);

    //    add = 15;
    //}

    //    add--;

        imageBuffer[0]->fill(qRgba(0, 0, 0, 255));

        world->graph->calc();
    //}

    //printf("%d\n", frameTimer->elapsed());

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
    painter.drawPixmap(QPoint(0, 10), QPixmap::fromImage(*imageBuffer[0]));
    painter.end();
}


