//
// Created by Cezar on 24.06.2025.
//

#ifndef TABLEVIEWMAINWINDOW_H
#define TABLEVIEWMAINWINDOW_H
#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QApplication>
#include "service.h"
#include "TableViewWriterWindow.h"
class TWmainWindow : public QMainWindow {
    Q_OBJECT
private:
    IdeaService* service;
    QList<TableViewWriterWindow*> writerWindows;

public:
    explicit TWmainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent), service(new IdeaService(this)) {

        connect(service, &IdeaService::ideasChanged, this, &TWmainWindow::onIdeasChanged);
    }
    ~TWmainWindow() {
        service->saveDataExplicitly(); // Save data before exit
        for (auto* window : writerWindows) {
            window->close();
        }
    }
    bool init() {
        // Load data from files
        if (!service->loadData("writers.txt", "ideas.txt")) {
            qDebug() << "Failed to load data files";
            return false;
        }

        // Create a window for each writer
        const QList<Writer>& writers = service->getWriters();
        for (const Writer& writer : writers) {
            TableViewWriterWindow* window = new TableViewWriterWindow(writer, service);
            writerWindows.append(window);
            window->show();
        }

        // Hide the main window since we only need the writer windows
        this->hide();

        return true;
    }
private slots:
    void ApplicationAboutToQuit() {
        service->saveDataExplicitly();
    }
    void onIdeasChanged() {

    }
};
#endif //TABLEVIEWMAINWINDOW_H
