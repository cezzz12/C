#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMessageBox>
#include <QList>
#include "programmerwindow.h"
#include "service.h"

class mainApplication : public QObject {
    Q_OBJECT
private:
    FileService service;
    QList<ProgrammerWindow*> programmerWindows;

public:
    mainApplication(QObject* parent = nullptr) : QObject(parent) {}

    ~mainApplication() {
        service.saveDataExplicitly();
        for (ProgrammerWindow* window : programmerWindows) {
            delete window;
        }
    }

    bool initialize(const QString& programmersFile = "programmers.txt",
                    const QString& sourceFilesFile = "source_files.txt") {

        if (!service.loadData(programmersFile, sourceFilesFile)) {
            QMessageBox::critical(nullptr, "Error",
                "Failed to load data files. Please check that programmers.txt and source_files.txt exist.");
            return false;
        }

        // Create windows for each programmer
        const QList<Programmer>& programmers = service.getProgrammers();
        for (const Programmer& programmer : programmers) {
            ProgrammerWindow* window = new ProgrammerWindow(programmer, &service);
            programmerWindows.append(window);
            window->show();
        }

        return true;
    }
private slots:
        void ApplicationAboutToQuit() {
            service.saveDataExplicitly();

        }
};
#endif // MAINWINDOW_H