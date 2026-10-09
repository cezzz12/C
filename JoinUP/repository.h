//
// Created by Cezar on 25.06.2025.
//
#pragma once
#include <QList>
#include <QString>
#include "domain.h"

class PersonRepository {
public:
    static QList<Person> loadPersons(const QString &fileName); //load from file
};

class EventRepository {
public:
    static QList<Event> loadEvents(const QString &fileName); //load from file
    static bool saveEvents(const QString &fileName, const QList<Event> &events); //for saving after
};