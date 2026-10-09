//
// Created by Cezar on 24.06.2025.
//

#ifndef TWMAINWINDOW_H
#define TWMAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QApplication>
#include "service.h"
#include "TableViewAstronomerWindow.h"

class TWmainWindow : public QMainWindow {
    Q_OBJECT

private:
    StarService* service;
    QList<TableViewAstronomerWindow*> astronomerWindows;

public:
    explicit TWmainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent), service(new StarService(this)) {

        connect(service, &StarService::starsChanged, this, &TWmainWindow::onStarsChanged);
    }

    ~TWmainWindow() {
        service->saveDataExplicitly(); // Save data before exit
        for (auto* window : astronomerWindows) {
            window->close();
        }
    }

    bool init() {
        // Load data from files
        if (!service->loadData("astronomers.txt", "stars.txt")) {
            qDebug() << "Failed to load data files";
            return false;
        }

        // Create a window for each astronomer
        const QList<Astronomer>& astronomers = service->getAstronomers();
        for (const Astronomer& astronomer : astronomers) {
            TableViewAstronomerWindow* window = new TableViewAstronomerWindow(astronomer, service);
            astronomerWindows.append(window);
            window->show();
        }

        // Hide the main window since we only need the astronomer windows
        this->hide();

        return true;
    }
private slots:
    void ApplicationAboutToQuit() {
        service->saveDataExplicitly();
    }
    void onStarsChanged() {

    }
};

#endif // TWMAINWINDOW_H