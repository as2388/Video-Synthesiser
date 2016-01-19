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

    QImage* ugen_blankImagePointer(int width, int height);
    QImage ugen_blankImage(int width, int height);
    QImage ugen_add_checkerboard(QImage input0, QImage input1);
    QImage ugen_add_simple(QImage input0, QImage input1);
    QImage ugen_add_alphaBlend(QImage input0, QImage input1);
    QImage ugen_draw(QImage input);

    int colorClamp(int value);

public slots:
    void advanceDisplayedImage();

   // int blendHelper(int Ca, int aa, int Cb, int ab);

    int blendHelper(double ca, double aa, double cb, double ab);

    void time_ugen_blur_size();

    QImage ugen_rectangle(QImage &input, int ix, int iy, int width, int height, uint color);

    void time_ugen_draw();

    void time_ugen_blur_strength();

    QImage ugen_blur(QImage input, QImage output, int strength);
};

#endif // MAINWINDOW_H
