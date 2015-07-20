#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QVector3D>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void autoRender();
    void renderScene();
    void resetValues();
    void saveImage();

private:
    Ui::MainWindow *ui;
    QImage* rayTracerImage;

    void connectAllSlots();
    void createShapes();
    void createLights();
    int clamp(int value);
    void getGuiValues();
    QVector3D traceRay(QVector3D rayOrigin, QVector3D rayDirection, int depth);
};

#endif // MAINWINDOW_H
