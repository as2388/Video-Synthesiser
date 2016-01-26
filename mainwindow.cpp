#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "World.h"
#include <QtGui>
#include <stdio.h>
#include <Synthesiser/Unit.h>
#include <QDebug>
#include <Synthesiser/Synth.h>
#include <Synthesiser/SampleSynths/FadingSquares.h>
#include <Synthesiser/SampleSynths/Kaleidoscope.h>

QImage** imageBuffer = new QImage*[2];
//Synth** synths;
int* timeToReconstruct = new int[5];
World* world;
Graph* graph = new Graph();
QElapsedTimer* frameTimer = new QElapsedTimer();

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

    imageBuffer[0] = this->ugen_blankImagePointer(800, 800);
    imageBuffer[1] = this->ugen_blankImagePointer(800, 800);
    imageBuffer[0]->fill(qRgba(0, 0, 0, 255));
    imageBuffer[1]->fill(qRgba(0, 0, 0, 255));

    world = new World();
    world -> mImageBuffers = imageBuffer;
    world -> mDisplayBuffers = new QPainter*[2];
    world -> mDisplayBuffers[0] = new QPainter(imageBuffer[0]);
    world -> mDisplayBuffers[1] = new QPainter(imageBuffer[1]);
    world -> mNumDisplayBuffers = 2;

    Graph* g = new Graph();
    g->setFirstChild(graph);
    Kaleidoscope* kaleidoscope = new Kaleidoscope();
    Kaleidoscope_Ctor(kaleidoscope, world);
    graph->appendSibling(kaleidoscope);
    world->graph->setFirstChild(g);

//    for (int i = 0; i < 15; i++) {
//        Synth* node = new Synth();
//        Synth_Ctor(node, world);
//        world->graph->insertGraphAfter(node, world->graph);
//    }

    //synths = new Synth*[15];
    //for (int i = 0; i < 15; i++) {
    //    synths[i] = new Synth();
    //    Synth_Ctor(synths[i], world);
    //    timeToReconstruct[i] = i;
    //}

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(50);

    //frameTimer->start();

    //this->advanceDisplayedImage();
}

void MainWindow::time_ugen_draw() {
    QString filename="/Users/Alexander/Documnts/time_ugen_draw.csv";
    QFile file(filename);
    QTextStream stream(&file);

    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << "file open";
    } else {
        qDebug() << "failed to open file";
    }

    QElapsedTimer stopwatch;
    QImage image;
    for (int x = 1; x <= 1000; x++) {
        image = ugen_blankImage(x, x);
        stopwatch.restart();
        for (int times = 0; times < 1000; times++) {
            image = ugen_rectangle(image, 0, 0, x, x, qRgba(255, 255, 255, 255));
        }
        qint64 totalTime = stopwatch.elapsed();
        stream << x << "," << totalTime << endl;
        qDebug() << x << "," << totalTime;
    }

    return;
}

void MainWindow::time_ugen_blur_size() {
    QString filename="/Users/Alexander/Documents/time_ugen_blur_size.csv";
    QFile file(filename);
    QTextStream stream(&file);

    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << "file open";
    } else {
        qDebug() << "failed to open file";
    }

    QElapsedTimer stopwatch;
    QImage image;
    for (int x = 1; x <= 1000; x++) {
        image = ugen_blankImage(x, x);
        image = ugen_rectangle(image, 0, 0, x, x, qRgba(255, 255, 255, 255));
        QImage output = ugen_blankImage(image.width(), image.height());
        stopwatch.restart();
        for (int times = 0; times < 1000; times++) {
            image = ugen_blur(image, output, 3);
        }
        qint64 totalTime = stopwatch.elapsed();
        stream << x << "," << totalTime << endl;
        qDebug() << x << "," << totalTime;
    }

    return;
}

void MainWindow::time_ugen_blur_strength() {
    QString filename="/Users/Alexander/Documents/time_ugen_blur_strength.csv";
    QFile file(filename);
    QTextStream stream(&file);

    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << "file open";
    } else {
        qDebug() << "failed to open file";
    }

    QElapsedTimer stopwatch;
    QImage image;
    for (int strength = 1; strength < 20; strength++) {
        image = ugen_blankImage(800, 600);
        image = ugen_rectangle(image, 0, 0, 800, 600, qRgba(255, 255, 255, 255));
        QImage output = ugen_blankImage(image.width(), image.height());
        stopwatch.restart();
        for (int times = 0; times < 1000; times++) {
            image = ugen_blur(image, output, strength);
        }
        qint64 totalTime = stopwatch.elapsed();
        stream << strength << "," << totalTime << endl;
        qDebug() << strength << "," << totalTime;
    }

    return;
}


QImage* MainWindow::ugen_blankImagePointer(int width, int height) {
    QImage* image = new QImage(width, height, QImage::Format_ARGB32);
    image->fill(qRgba(0, 0, 0, 0));

    return image;
}

QImage MainWindow::ugen_blankImage(int width, int height) {
    QImage image = QImage(width, height, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));

    return image;
}

QImage MainWindow::ugen_add_checkerboard(QImage input0, QImage input1) {
    QImage output = this -> ugen_blankImage(input0.width(), input1.height());

    // Strategy: Consider the image to be laid out like this, with true/false
    // as the column/row headers, and 0/1 showing which of input0 and input1 to
    // read the pixel from:
    //       true | false | true | false | true
    // true    0      1       0       1      0
    // false   1      0       1       0      1
    // true    0      1       0       1      0
    // false   1      0       1       0      1
    // We then observe that input0 should be used when x xor y = false; input1 otherwise:
    for (int x = 0; x < input0.width(); x++) {
        for (int y = 0; y < input0.height(); y++) {
            bool xEven = x % 2 == 0;
            bool yEven = y % 2 == 0;

            if (xEven xor yEven) {
                output.setPixel(x, y, input0.pixel(x, y));
            } else {
                output.setPixel(x, y, input1.pixel(x, y));
            }
        }
    }

    return output;
}

QImage MainWindow::ugen_add_simple(QImage input0, QImage input1) {
    QImage output = this->ugen_blankImage(input0.width(), input0.height());

    // Strategy: Add each channel independently.
    for (int x = 0; x < input0.width(); x++) {
        for (int y = 0; y < input0.height(); y++) {
            QColor rgb0 = QColor(input0.pixel(x, y));
            QColor rgb1 = QColor(input1.pixel(x, y));

            int alphaOut = qAlpha(input0.pixel(x, y)) + qAlpha(input1.pixel(x, y));

            output.setPixel(x, y, qRgba(colorClamp(rgb0.red() + rgb1.red()),
                                        colorClamp(rgb0.green() + rgb1.green()),
                                        colorClamp(rgb0.blue() + rgb1.blue()),
                                        colorClamp(alphaOut))
            );
        }
    }

    return output;
}

int MainWindow::colorClamp(int value) {
    return value > 255 ? 255 : value;
}

QImage MainWindow::ugen_add_alphaBlend(QImage input0, QImage input1) {
    QImage output = this->ugen_blankImage(input0.width(), input0.height());

    for (int x = 0; x < input0.width(); x++) {
        for (int y = 0; y < input0.height(); y++) {
            QColor rgb0 = QColor(input0.pixel(x, y));
            QColor rgb1 = QColor(input1.pixel(x, y));

            int alpha0 = qAlpha(input0.pixel(x, y));
            int alpha1 = qAlpha(input1.pixel(x, y));

            double aan = alpha1 / 255.0;
            double abn = alpha0 / 255.0;

            output.setPixel(x, y, qRgba(
                    blendHelper(rgb1.red(),   alpha1, rgb0.red(),   alpha0),
                    blendHelper(rgb1.green(), alpha1, rgb0.green(), alpha0),
                    blendHelper(rgb1.blue(),  alpha1, rgb0.blue(),  alpha0),
                    (int) (255 * (aan + abn * (1 - aan))))
            );
        }
    }

    return output;
}

int MainWindow::blendHelper(double ca, double aa, double cb, double ab) {
    double aan = aa / 255.0;
    double abn = ab / 255.0;

    return (int) ((ca * aan + cb * abn * (1.0 - aan)) / (aan + abn * (1.0 - aan)));
}

QImage MainWindow::ugen_rectangle(QImage &input, int ix, int iy, int width, int height, uint color) {
    for (int y = iy; y < iy + height; y++) {
        uint *line = (uint *) input.scanLine(y);
        for (int x = ix; x < ix + width; x++) {
            *(line + x) = color;
        }
    }

    return input;
}

QImage MainWindow::ugen_blur(QImage input, QImage output, int strength) {
    for (int yy = 0; yy < input.height(); yy++) {
        uint *outputLine = (uint *) output.scanLine(yy);
        for (int xx = 0; xx < input.width(); xx++) {
            int summed = 0;
            uint sumRed = 0;
            uint sumGreen = 0;
            uint sumBlue = 0;
            uint sumAlpha = 0;


            for (int y = -strength + yy; y <= strength + yy; y++) {
                if (y > 0 && y < input.height()) {
                    uint *inputLine = (uint *) input.scanLine(y);
                    for (int x = -strength + xx; x <= strength + xx; x++) {
                        if (x > 0 && y > 0 && x < input.width()) {
                            uint pixel = *(inputLine + x);

                            sumRed += qRed(pixel);
                            sumGreen += qGreen(pixel);
                            sumBlue += qBlue(pixel);
                            sumAlpha += qAlpha(pixel);

                            summed++;
                        }
                    }
                }
            }

            sumRed /= summed;
            sumGreen /= summed;
            sumBlue /= summed;
            sumAlpha /= summed;

            *(outputLine + xx) = qRgba(sumRed, sumGreen, sumBlue, sumAlpha);
        }
    }

    return output;
}

QImage MainWindow::ugen_draw(QImage input) {
    return input;
}

/**
 * @brief MainWindow::advanceDisplayedImage Advance the pointer to the image to be rendered
 * by one position, and force a window repaint.
 */
bool add = true;
void MainWindow::advanceDisplayedImage() {
    frameTimer -> restart();

    for (int i = 0; i < 1000; i++) {
        FadingSquares *node = new FadingSquares();

        int **intParams = new int *[3];
        intParams[0] = new int(int(randf(80, 255))); // R
        intParams[1] = new int(int(randf(80, 255))); // G
        intParams[2] = new int(int(randf(80, 255))); // B
        intParams[3] = new int(1); // Image buffer to write to

        float **floatParams = new float *[5];
        floatParams[0] = new float(randf(0, 400 - 80)); // x
        floatParams[1] = new float(randf(0, 400 - 80)); // y
        // Move to upper-right half if necessary by mirroring over y = - x
        if (*floatParams[0] < *floatParams[1]) {
            float *temp = floatParams[0];
            floatParams[0] = floatParams[1];
            floatParams[1] = temp;
        }
        floatParams[2] = new float(randf(35, 80)); // width
        floatParams[3] = floatParams[2]; // height
        floatParams[4] = new float(15); // length of fade in frames
        Synth_Ctor(node, world, floatParams, intParams);
        FadingSquares_Ctor(node);
        graph->appendSibling(node);

        //add = !add;

        imageBuffer[0]->fill(qRgba(0, 0, 0, 255));
        imageBuffer[1]->fill(qRgba(0, 0, 0, 255));

        world->graph->calc();
    }
        printf("%d\n", frameTimer->elapsed());

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
void MainWindow::paintEvent(QPaintEvent *event)
{
    // Draw the image to the screen.
    QPainter painter(this);
    painter.drawImage(QPointF(0, 10), *imageBuffer[0]);
    painter.end();
}


