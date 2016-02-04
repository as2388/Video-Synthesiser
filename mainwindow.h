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
public slots:
    void advanceDisplayedImage();
    void updateAmplitude(float newAmplitude);
};

#endif // MAINWINDOW_H
