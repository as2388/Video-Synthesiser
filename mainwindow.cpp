#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <stdio.h>
#include <Synthesiser/Unit.h>
//#include <QDebug>
#include <Synthesiser/Synth.h>
#include <Synthesiser/SampleSynths/FadingSquares.h>
#include <Synthesiser/SampleSynths/Kaleidoscope.h>
#include <UserGraphics/UserGraphics.h>
#include <qlabel.h>
#include <World/World.h>
#include <Synthesiser/SampleSynths/FadingCopier.h>

QElapsedTimer timer = QElapsedTimer();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set a timer to update the displayed image every 1s
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(50);
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
    qDebug() << timer.elapsed();
    timer.restart();

    // If the queue is empty don't render this frame.
    if (queue->empty()) {qDebug() << "drop"; return;}

    QPainter painter(this);
    QImage* nextOutput;
    queue->pop(nextOutput);
    painter.drawPixmap(QPoint(0, 10), QPixmap::fromImage(*nextOutput));
    painter.end();
    world->releasePooledImage(nextOutput);
}


