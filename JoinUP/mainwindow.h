//
// Created by Cezar on 25.06.2025.
//
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
    mainApplication(QObject* parent = nullptr);
    ~mainApplication();
    bool initialize(const QString& personsFile = "persons.txt",
                    const QString& eventsFile = "events.txt");

    public slots:
        void onApplicationAboutToQuit();
};

#endif //MAINWINDOW_H