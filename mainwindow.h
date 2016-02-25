#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boost/lockfree/queue.hpp>
#include <World/World.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setQueue(boost::lockfree::queue<QImage*> *q) {this->queue = q;}
    void setWorld(World* w) {this->world = w; this->nextOutput = w->acquirePooledImage();}
    ~MainWindow();
private:
    QImage* nextOutput;
    boost::lockfree::queue<QImage*> *queue;
    World* world;
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
