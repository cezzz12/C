#include <QApplication>
#include <QPushButton>
#include "TableViewMainWindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TWmainWindow mainWindow;
    if (!mainWindow.init()) {
        return -1; // Initialization failed
    }
    return QApplication::exec();
}