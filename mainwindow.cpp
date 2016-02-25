#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

QElapsedTimer timer = QElapsedTimer();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer.restart();

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
int startIn = 20;
void MainWindow::paintEvent(QPaintEvent *event) {
    //qDebug() << timer.elapsed();
    //timer.restart();
    if (startIn > 0) {
        startIn--;
    } else {
        // If the queue is empty don't render this frame.
        if (!queue->empty()) {
            world->releasePooledImage(nextOutput);
            queue->pop(nextOutput);
        } else {
            qDebug() << "frame dropped";
        }
    }

    QPainter painter(this);
    //qDebug() << nextOutput;
    painter.drawPixmap(QPoint(0, 10), QPixmap::fromImage(*nextOutput));
    painter.end();
}


