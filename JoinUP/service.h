//
// Created by Cezar on 25.06.2025.
//
#pragma once
#include "domain.h"
#include "repository.h"
#include <QObject>
#include <QList>
#include <QString>
#include <QDate>

class EventService : public QObject {
    Q_OBJECT
private:
    QList<Person> persons;
    QList<Event> events;
    QString personsFileName = "persons.txt";
    QString eventsFileName = "events.txt";

public:
    explicit EventService(QObject* parent = nullptr);
    bool loadData(const QString& personsFile, const QString& eventsFile);
    bool saveData();
    const QList<Person>& getPersons() const;
    const QList<Event>& getEvents() const;
    bool saveDataExplicitly();
    bool isPersonCloseToEvent(const Person& person, const Event& event, double threshold = 5.0) const;
    QList<Event> getEventsCloseToPerson(const Person& person, double threshold = 5.0) const;
    bool addEvent(const QString& name, const QString& organizer, int latitude, int longitude,
                  const QDate& date, const QString& description, QString& errorMessage);


    signals:
        void eventsChanged();
};