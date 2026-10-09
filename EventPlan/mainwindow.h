#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QObject>
#include <QList>
#include <QMessageBox>
#include "domain.h"
#include "service.h"
#include "personwindow.h"

class mainApplication : public QObject {
    Q_OBJECT
private:
    EventService service;
    QList<PersonWindow*> personWindows;

public:
    mainApplication(QObject* parent = nullptr) : QObject(parent) {}

    ~mainApplication() {
        service.saveDataExplicitly(); // Save data before exiting
        for (PersonWindow* window : personWindows) {
            delete window;
        }
    }

    bool initialize(const QString& personsFile = "persons.txt",
                    const QString& eventsFile = "events.txt") {
        if (!service.loadData(personsFile, eventsFile)) {
            QMessageBox::critical(nullptr, "Error",
                "Failed to load data files. Please check that persons.txt exists and contains valid data.");
            return false;
        }

        // Create windows for each person
        const QList<Person>& persons = service.getPersons();
        for (const Person& person : persons) {
            PersonWindow* window = new PersonWindow(person, &service);
            personWindows.append(window);
            window->show();
        }

        return true;
    }

    public slots:
        void onApplicationAboutToQuit() {
        // Save data when application is about to quit
        service.saveDataExplicitly();
    }
};


#endif //MAINWINDOW_H
