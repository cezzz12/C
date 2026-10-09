#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainApplication mainApp;
    if (!mainApp.initialize()) {
        return -1; // Initialization failed, exit application
    }

    return app.exec();
}