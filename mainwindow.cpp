#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QImage>

QImage imageBuffer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    imageBuffer = this->ugen_blankImage(400, 100);
//    imageBuffer = this->ugen_rectangle(imageBuffer, 30, 30, 40, 40);
//    imageBuffer = this->ugen_blur(imageBuffer, 4);
//    imageBuffer = this->ugen_add(imageBuffer, ugen_rectangle(ugen_blankImage(400, 100), 130, 30, 40, 40));
//    imageBuffer = this->ugen_blur(imageBuffer, 4);
//    imageBuffer = this->ugen_add(imageBuffer, ugen_rectangle(ugen_blankImage(400, 100), 230, 30, 40, 40));
//    imageBuffer = this->ugen_blur(imageBuffer, 4);
//    imageBuffer = this->ugen_add(imageBuffer, ugen_rectangle(ugen_blankImage(400, 100), 330, 30, 40, 40));

    imageBuffer = this->ugen_blankImage(400, 100);
    imageBuffer = this->ugen_rectangle(imageBuffer, 30, 30, 40, 40);
    imageBuffer = this->ugen_blur(imageBuffer, 4);
    imageBuffer = this->ugen_rectangle(imageBuffer, 130, 30, 40, 40);
    imageBuffer = this->ugen_blur(imageBuffer, 4);
    imageBuffer = this->ugen_rectangle(imageBuffer, 230, 30, 40, 40);
    imageBuffer = this->ugen_blur(imageBuffer, 4);
    imageBuffer = this->ugen_rectangle(imageBuffer, 330, 30, 40, 40);

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(1000);
}

QImage MainWindow::ugen_blankImage(int width, int height) {
    QImage image = QImage(width, height, QImage::Format_ARGB32);
    image.fill(Qt::GlobalColor::black);

    return image;
}

QImage MainWindow::ugen_add(QImage input0, QImage input1) {
    QImage output = this->ugen_blankImage(input0.width(), input0.height());

    for (int x = 0; x < input0.width(); x++) {
        for (int y = 0; y < input0.height(); y++) {
            QColor rgb0 = QColor(input0.pixel(x, y));
            QColor rgb1 = QColor(input1.pixel(x, y));

            uint alphaOut = qAlpha(input0.pixel(x, y)) + qAlpha(input1.pixel(x, y));

            output.setPixel(x, y, qRgba(rgb0.red() + rgb1.red(), rgb0.green() + rgb1.green(),
                                        rgb0.blue() + rgb1.blue(), alphaOut));
        }
    }

    return output;
}

QImage MainWindow::ugen_rectangle(QImage input, int x, int y, int width, int height, uint color) {
    for (int ix = x; ix < x + width; ix++) {
        for (int iy = y; iy < y + height; iy++) {
            input.setPixel(ix, iy, color);
        }
    }

    return input;
}

QImage MainWindow::ugen_blur(QImage input, int strength) {
    QImage output = ugen_blankImage(input.width(), input.height());

    for (int xx = 0; xx < input.width(); xx++) {
        for (int yy = 0; yy < input.height(); yy++) {
            int summed = 0;
            uint sumRed = 0;
            uint sumGreen = 0;
            uint sumBlue = 0;
            uint sumAlpha = 0;

            for (int x = -strength + xx; x <= strength + xx; x++) {
                for (int y = -strength + yy; y <= strength + yy; y++) {
                    if (x > 0 && y > 0 && x < input.width() && y < input.height()) {
                        QColor rgb = QColor(input.pixel(x, y));
                        sumRed += rgb.red();
                        sumGreen += rgb.green();
                        sumBlue += rgb.blue();
                        sumAlpha += qAlpha(input.pixel(x, y));
                        summed++;
                    }
                }
            }

            sumRed /= summed;
            sumGreen /= summed;
            sumBlue /= summed;
            sumAlpha /= summed;

            output.setPixel(xx, yy, qRgba(sumRed, sumGreen, sumBlue, sumAlpha));
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
    // TODO: render a new image :)
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
