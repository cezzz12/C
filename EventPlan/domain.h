//
// Created by Cezar on 24.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <QDate>
#include <QList>
#include <QString>

class Person{
private:
    QString name;
    int latitude;
    int longitude;
    bool isOrganizer;
public:
    Person() : latitude(0), longitude(0), isOrganizer(false) {}
    Person(const QString &name, int latitude, int longitude, bool status)
        : name(name), latitude(latitude), longitude(longitude), isOrganizer(status) {}

    QString getName() const { return name; }
    int getLatitude() const { return latitude; }
    int getLongitude() const { return longitude; }
    bool getStatus() const { return isOrganizer; }


    void setName(const QString &newName) { this->name = newName; }
    void setLatitude(int newLatitude) { this->latitude = newLatitude; }
    void setLongitude(int newLongitude) { this->longitude = newLongitude; }
    void setStatus(bool newStatus) { this->isOrganizer = newStatus; }
};

class Event{
private:
     QString organizer;
     QString name;
     int latitude;
     int longitude;
     QDate date;
     QString description;
public:
      Event() : latitude(0), longitude(0) {}
        Event(const QString &organizer, const QString &name, int latitude, int longitude, const QDate &date, const QString &description)
            : organizer(organizer), name(name), latitude(latitude), longitude(longitude), date(date), description(description) {}
      QString getOrganizer() const { return organizer; }
      QString getName() const { return name; }
      int getLatitude() const { return latitude; }
      int getLongitude() const { return longitude; }
        QDate getDate() const { return date; }
        QString getDescription() const { return description; }

      void setOrganizer(const QString &newOrganizer) { this->organizer = newOrganizer; }
        void setName(const QString &newName) { this->name = newName; }
        void setLatitude(int newLatitude) { this->latitude = newLatitude; }
        void setLongitude(int newLongitude) { this->longitude = newLongitude; }

};
#endif //DOMAIN_H
