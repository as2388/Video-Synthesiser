#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    void initialiseInMemoryImages();
    QImage ugen_blankImage(int width, int height);
    QImage ugen_rectangle(QImage input, int x, int y, int width, int height, uint color = qRgba(255, 255, 255, 255));
    QImage ugen_add(QImage input0, QImage input1);
    QImage ugen_blur(QImage input, int strength);
    QImage ugen_draw(QImage input);

public slots:
    void advanceDisplayedImage();
};

#endif // MAINWINDOW_H