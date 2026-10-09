//
// Created by Cezar on 22.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>
#include <cmath>
class Courier {
  private:
    QString name;
    QStringList assignedStreets;
    double centerX,centerY;
    double radius;
  public:
    Courier(const QString &name, const QStringList &streets, double centerX, double centerY, double radius)
        : name(name), assignedStreets(streets), centerX(centerX), centerY(centerY), radius(radius) {}

    QString getName() const { return name; }
    QStringList getAssignedStreets() const { return assignedStreets; }
    double getCenterX() const { return centerX; }
    double getCenterY() const { return centerY; }
    double getRadius() const { return radius; }

    void setName(const QString &newName) { name = newName; }
    void setAssignedStreets(const QStringList &newStreets) { assignedStreets = newStreets; }
    void setCenterX(double x) { centerX = x; }
    void setCenterY(double y) { centerY = y; }
    void setRadius(double r) { radius = r; }
    bool hasStreet(const QString& street) const {
        return assignedStreets.contains(street, Qt::CaseInsensitive);
    }
    bool isLocationInZone(double x, double y) const {
        double distance = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));
        return distance <= radius;
    }
    bool operator==(const Courier& other) const {
        return name == other.name;
    }

};

class Package {
private:
    QString recipient;
    QString street;
    int number;
    double locationX, locationY;
    bool deliveryStatus;

public:
    Package() : number(0), locationX(0), locationY(0), deliveryStatus(false) {}
    Package(const QString& recipient, const QString& street, int number,
            double locationX, double locationY, bool deliveryStatus = false)
        : recipient(recipient), street(street), number(number),
          locationX(locationX), locationY(locationY), deliveryStatus(deliveryStatus) {}

    QString getRecipient() const { return recipient; }
    QString getStreet() const { return street; }
    int getNumber() const { return number; }
    double getLocationX() const { return locationX; }
    double getLocationY() const { return locationY; }
    bool getDeliveryStatus() const { return deliveryStatus; }

    void setRecipient(const QString& newRecipient) { this->recipient = newRecipient; }
    void setStreet(const QString& newStreet) { this->street = newStreet; }
    void setNumber(int newNumber) { this->number = newNumber; }
    void setLocationX(double x) { this->locationX = x; }
    void setLocationY(double y) { this->locationY = y; }
    void setDeliveryStatus(bool status) { this->deliveryStatus = status; }

    // Get full address as string
    QString getFullAddress() const {
        return QString("%1 %2").arg(street).arg(number);
    }

    // Check if package is assigned to a courier
    bool isAssignedToCourier(const Courier& courier) const {
        return courier.hasStreet(street) || courier.isLocationInZone(locationX, locationY);
    }

    bool operator==(const Package& other) const {
        return recipient == other.recipient &&
               street == other.street &&
               number == other.number;
    }
};

#endif//DOMAIN_H
