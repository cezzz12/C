//
// Created by Cezar on 24.06.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "domain.h"
#include "repository.h"
#include <QObject>
#include <QList>
#include <QSet>
#include <QString>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDate>

class EventService : public QObject {
    Q_OBJECT
private:
    QList<Person> persons;
    QList<Event> events;
    QString personsFileName = "persons.txt";
    QString eventsFileName = "events.txt";

    public:
    explicit EventService(QObject* parent = nullptr) : QObject(parent) {}
    bool loadData(const QString& personsFile, const QString& eventsFile) {
        persons = PersonRepository::loadPersons(personsFile);
        events = EventRepository::loadEvents(eventsFile);

        // Sort events by date
        std::sort(events.begin(), events.end(),
            [](const Event& a, const Event& b) {
                return a.getDate() < b.getDate();
            });

        return !persons.isEmpty() && !events.isEmpty();
    }
    bool saveData() {
        if(eventsFileName.isEmpty()) {
            return false;
        }
        return EventRepository::saveEvents(eventsFileName, events);
    }
    const QList<Person>& getPersons() const { return persons; }
    const QList<Event>& getEvents() const { return events; }
    bool saveDataExplicitly() {
        return saveData();
    }
    bool addEvent(const QString& name, const QString& organizer, int latitude, int longitude,
                 const QDate& date, const QString& description, QString& errorMessage) {
        if (name.trimmed().isEmpty() || organizer.trimmed().isEmpty()) {
            errorMessage = "Event name and organizer cannot be empty.";
            return false;
        }

        // Check if event already exists with same name and location
        for (const Event& event : events) {
            if (event.getName().toLower() == name.trimmed().toLower() &&
                event.getLatitude() == latitude && event.getLongitude() == longitude) {
                errorMessage = "An event with this name and location already exists.";
                return false;
                }
        }

        events.append(Event(organizer.trimmed(), name.trimmed(), latitude, longitude, date, description.trimmed()));

        // Re-sort events by date
        std::sort(events.begin(), events.end(),
            [](const Event& a, const Event& b) {
                return a.getDate() < b.getDate();
            });

        emit eventsChanged();
        return true;
    }
    bool isPersonCloseToEvent(const Person& person, const Event& event, double threshold = 5.0) const {
        double distance = qSqrt(qPow(event.getLatitude() - person.getLatitude(), 2) +
                                qPow(event.getLongitude() - person.getLongitude(), 2));
        return distance <= threshold;
    }
    QList<Event> getEventsCloseToPerson(const Person& person, double threshold = 5.0) const {
        QList<Event> closeEvents;
        for (const Event& event : events) {
            if (isPersonCloseToEvent(person, event, threshold)) {
                closeEvents.append(event);
            }
        }
        return closeEvents;
    }
signals:
    void eventsChanged();
};
#endif //SERVICE_H
