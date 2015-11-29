#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <Synthesiser/Unit.h>
#include <Synthesiser/Synth.h>

QImage imageBuffer;
Synth* synth;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageBuffer = this->ugen_blankImage(100, 100);
//    imageBuffer = this->ugen_rectangle(imageBuffer, 30, 30, 40, 40, qRgba(0, 255, 0, 255));
//    imageBuffer = this->ugen_blur(imageBuffer, 4);
//    imageBuffer = this->ugen_add(imageBuffer, ugen_rectangle(ugen_blankImage(400, 100), 130, 30, 40, 40));
//    imageBuffer = this->ugen_blur(imageBuffer, 4);
//    imageBuffer = this->ugen_add(imageBuffer, ugen_rectangle(ugen_blankImage(400, 100), 230, 30, 40, 40));
//    imageBuffer = this->ugen_blur(imageBuffer, 4);
//    imageBuffer = this->ugen_add(imageBuffer, ugen_rectangle(ugen_blankImage(400, 100), 330, 30, 40, 40));

    /*imageBuffer = this->ugen_blankImage(400, 100);
    imageBuffer = this->ugen_rectangle(imageBuffer, 30, 30, 40, 40);
    imageBuffer = this->ugen_blur(imageBuffer, 4);
    imageBuffer = this->ugen_rectangle(imageBuffer, 130, 30, 40, 40);
    imageBuffer = this->ugen_blur(imageBuffer, 4);
    imageBuffer = this->ugen_rectangle(imageBuffer, 230, 30, 40, 40);
    imageBuffer = this->ugen_blur(imageBuffer, 4);
    imageBuffer = this->ugen_rectangle(imageBuffer, 330, 30, 40, 40);*/

    // Add ugen examples
    //QImage i0 = this -> ugen_blankImage(100, 100);
    //i0        = this -> ugen_rectangle(i0, 10, 10, 60, 60, qRgba(255, 0, 0, 85));
    //QImage i1 = this -> ugen_blankImage(100, 100);
    //i1        = this -> ugen_rectangle(i1, 30, 30, 60, 60, qRgba(0, 0, 255, 170));
    //Checkerboard
    //imageBuffer = this -> ugen_add_checkerboard(i0, i1);
    //Channel add
    //imageBuffer = this -> ugen_add_simple(i0, i1);
    //Alpha blend
    //imageBuffer = this -> ugen_add_alphaBlend(i0, i1);
    //imageBuffer = this -> ugen_blur(imageBuffer, im 1);

    //imageBuffer = i1;

    synth = new Synth();
    Synth_Ctor(synth);

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(100);

    qDebug() << "ready";

    //time_ugen_draw();
    //time_ugen_blur_strength();
    //time_ugen_blur_size();
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
void MainWindow::advanceDisplayedImage() {
    Synth_Compute(synth);

     
    QPainter copier(&imageBuffer);
    copier.drawImage(QPoint(0, 0), *(((Rectangle *)(synth -> mUnits[1])) -> outputImage));
    //qDebug() << imageBuffer.width();

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
    painter.drawImage(QPointF(0, 10), imageBuffer);
}
