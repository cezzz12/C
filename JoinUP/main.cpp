#include <QPushButton>
#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    mainApplication MAINWINDOW;
    if (!MAINWINDOW.initialize()) {
        return 1;
    }

    return app.exec();
}