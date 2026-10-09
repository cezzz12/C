//
// Created by Cezar on 24.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <QList>
#include <QString>
#include "domain.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

class PersonRepository {
public:
    static QList<Person> loadPersons(const QString &fileName) {
        QList<Person> persons;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for reading:" << fileName;
            return persons;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 4) {
                persons.append(Person(parts[0], parts[1].toInt(), parts[2].toInt(), parts[3] == "true"));
            }
        }
        file.close();
        return persons;
    }

};

class EventRepository{
public:
    static QList<Event> loadEvents(const QString &fileName) {
        QList<Event> events;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for reading:" << fileName;
            return events;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 6) {
                events.append(Event(parts[0], parts[1], parts[2].toInt(), parts[3].toInt(), QDate::fromString(parts[4], "yyyy-MM-dd"),parts[5]));
            }
        }
        file.close();
        return events;
    }
    static bool saveEvents(const QString &fileName, const QList<Event> &events) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for writing:" << fileName;
            return false;
        }
        QTextStream out(&file);
        for (const Event &event : events) {
            out << event.getOrganizer() << ","
                << event.getName() << ","
                << event.getLatitude() << ","
                << event.getLongitude() << ","
                << event.getDate().toString("yyyy-MM-dd") << ","
                << event.getDescription() << "\n";
        }
        file.close();
        return true;
    }
};
#endif //REPOSITORY_H
