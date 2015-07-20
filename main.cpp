#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Stephen Burchill");
    app.setApplicationName("Assignment 3: Ray Tracing");
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
