#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

QImage imageBuffer[3];
int imageBufferPosition = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up in-memory images
    this->initialiseInMemoryImages();

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceDisplayedImage()));
    timer->start(1000);
}

/**
 * @brief MainWindow::initialiseInMemoryImages Initialises three new QImages into
 * imageBuffer0[]: a red square, a green rectangle, and two white squares.
 */
void MainWindow::initialiseInMemoryImages() {
    // Initialise each image with a black background.
    for (int i = 0; i < 3; i++) {
        imageBuffer[i] = QImage(100, 100, QImage::Format_ARGB32);
        imageBuffer[i].fill(Qt::GlobalColor::black);
    }

    // Image0 contains a red square in approximately the middle of the image.
    for (int x = 30; x < 70; x++) {
        for (int y = 30; y < 70; y++) {
            imageBuffer[0].setPixel(x, y, qRgba(255, 0, 0, 255));
        }
    }

    // Image1 contains a blue rectangle
    for (int x = 10; x < 90; x++) {
        for (int y = 40; y < 60; y++) {
            imageBuffer[1].setPixel(x, y, qRgba(0, 255, 0, 255));
        }
    }

    // Image2 contains two white squares
    for (int x = 10; x < 40; x++) {
        for (int y = 10; y < 40; y++) {
            imageBuffer[2].setPixel(x, y, qRgba(255, 255, 255, 255));
        }
    }
    for (int x = 60; x < 90; x++) {
        for (int y = 60; y < 90; y++) {
            imageBuffer[2].setPixel(x, y, qRgba(255, 255, 255, 255));
        }
    }
}

/**
 * @brief MainWindow::advanceDisplayedImage Advance the pointer to the image to be rendered
 * by one position, and force a window repaint.
 */
void MainWindow::advanceDisplayedImage() {
    imageBufferPosition = (imageBufferPosition + 1) % 3;
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
    painter.drawImage(QPointF(0, 10), imageBuffer[imageBufferPosition]);
}
