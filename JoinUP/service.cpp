//
// Created by Cezar on 25.06.2025.
//
#include "service.h"
#include <algorithm>
#include <QtMath>

EventService::EventService(QObject* parent) : QObject(parent) {}

bool EventService::loadData(const QString& personsFile, const QString& eventsFile) { //load from file
    persons = PersonRepository::loadPersons(personsFile);
    events = EventRepository::loadEvents(eventsFile);
    std::sort(events.begin(), events.end(),
        [](const Event& a, const Event& b) {
            return a.getDate() < b.getDate(); //sorting by date
        });
    return !persons.isEmpty() && !events.isEmpty();
}

bool EventService::saveData() { //saving changes(after add)
    if (eventsFileName.isEmpty()) {
        return false;
    }
    return EventRepository::saveEvents(eventsFileName, events);
}

const QList<Person>& EventService::getPersons() const {
    return persons;
}

const QList<Event>& EventService::getEvents() const {
    return events;
}

bool EventService::saveDataExplicitly() {
    return saveData();
}
bool EventService::isPersonCloseToEvent(const Person& person, const Event& event, double threshold) const { //euclidean distance
    double distance = qSqrt(qPow(event.getLatitude() - person.getLatitude(), 2) +
                            qPow(event.getLongitude() - person.getLongitude(), 2));
    return distance <= threshold;
}

QList<Event> EventService::getEventsCloseToPerson(const Person& person, double threshold) const { //return array for checkbox
    QList<Event> closeEvents;
    for (const Event& event : events) {
        if (isPersonCloseToEvent(person, event, threshold)) {
            closeEvents.append(event);
        }
    }
    return closeEvents;
}


bool EventService::addEvent(const QString& name, const QString& organizer, int latitude, int longitude,
                            const QDate& date, const QString& description, QString& errorMessage) {
    if (name.trimmed().isEmpty() || organizer.trimmed().isEmpty()) { //check if name empty
        errorMessage = "Event name and organizer cannot be empty.";
        return false;
    }
    for (const Event& event : events) { //event with name and location exists already
        if (event.getName().toLower() == name.trimmed().toLower() &&
            event.getLatitude() == latitude && event.getLongitude() == longitude) {
            errorMessage = "An event with this name and location already exists.";
            return false;
        }
    }
    events.append(Event(organizer.trimmed(), name.trimmed(), latitude, longitude, date, description.trimmed()));
    std::sort(events.begin(), events.end(),
        [](const Event& a, const Event& b) { //sort again after adding
            return a.getDate() < b.getDate();
        });
    emit eventsChanged(); //for the observer pattern vector is changed
    return true;
}


