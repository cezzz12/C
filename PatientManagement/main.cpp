#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mainApplication mainWindow;
    if (!mainWindow.initialize()) {
        return 1;
    }
    return app.exec();
}