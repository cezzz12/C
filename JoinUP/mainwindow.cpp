//
// Created by Cezar on 25.06.2025.
//
#include "mainwindow.h"

mainApplication::mainApplication(QObject* parent)
    : QObject(parent) {}

mainApplication::~mainApplication() { //save in destructor
    service.saveDataExplicitly();
    for (PersonWindow* window : personWindows) {
        delete window;
    }
}

bool mainApplication::initialize(const QString& personsFile, const QString& eventsFile) {
    if (!service.loadData(personsFile, eventsFile)) {
        QMessageBox::critical(nullptr, "Error",
            "Failed to load data files. Please check that persons.txt exists and contains valid data.");
        return false;
    }
    const QList<Person>& persons = service.getPersons();
    for (const Person& person : persons) {
        PersonWindow* window = new PersonWindow(person, &service);
        personWindows.append(window);
        window->show();
    }
    return true;
}

void mainApplication::onApplicationAboutToQuit() { //save when exiting
    service.saveDataExplicitly();
}