//
// Created by Cezar on 22.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "domain.h"

class CourierRepository {
public:
    static QList<Courier> loadCouriers(const QString& fileName) {
        QList<Courier> couriers;
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open couriers file:" << fileName;
            return couriers;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            // Format: Name|Street1,Street2,Street3|CenterX,CenterY,Radius
            QStringList parts = line.split('|');
            if (parts.size() == 3) {
                QString name = parts[0].trimmed();

                // Parse streets
                QStringList streets = parts[1].split(',');
                for (QString& street : streets) {
                    street = street.trimmed();
                }

                // Parse zone coordinates and radius
                QStringList zoneParts = parts[2].split(',');
                if (zoneParts.size() == 3) {
                    double centerX = zoneParts[0].trimmed().toDouble();
                    double centerY = zoneParts[1].trimmed().toDouble();
                    double radius = zoneParts[2].trimmed().toDouble();

                    couriers.append(Courier(name, streets, centerX, centerY, radius));
                }
            }
        }

        file.close();
        return couriers;
    }

    static bool saveCouriers(const QList<Courier>& couriers, const QString& fileName) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open couriers file for writing:" << fileName;
            return false;
        }

        QTextStream out(&file);
        for (const Courier& courier : couriers) {
            out << courier.getName() << "|";
            out << courier.getAssignedStreets().join(",") << "|";
            out << courier.getCenterX() << "," << courier.getCenterY() << "," << courier.getRadius();
            out << "\n";
        }

        file.close();
        return true;
    }
};

class PackageRepository {
public:
    static QList<Package> loadPackages(const QString& fileName) {
        QList<Package> packages;
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open packages file:" << fileName;
            return packages;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            // Format: Recipient|Street|Number|LocationX,LocationY|DeliveryStatus
            QStringList parts = line.split('|');
            if (parts.size() == 5) {
                QString recipient = parts[0].trimmed();
                QString street = parts[1].trimmed();
                int number = parts[2].trimmed().toInt();

                // Parse location coordinates
                QStringList locationParts = parts[3].split(',');
                if (locationParts.size() == 2) {
                    double locationX = locationParts[0].trimmed().toDouble();
                    double locationY = locationParts[1].trimmed().toDouble();
                    bool deliveryStatus = (parts[4].trimmed().toLower() == "true");

                    packages.append(Package(recipient, street, number, locationX, locationY, deliveryStatus));
                }
            }
        }

        file.close();
        return packages;
    }

    static bool savePackages(const QList<Package>& packages, const QString& fileName) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open packages file for writing:" << fileName;
            return false;
        }

        QTextStream out(&file);
        for (const Package& package : packages) {
            out << package.getRecipient() << "|";
            out << package.getStreet() << "|";
            out << package.getNumber() << "|";
            out << package.getLocationX() << "," << package.getLocationY() << "|";
            out << (package.getDeliveryStatus() ? "true" : "false");
            out << "\n";
        }

        file.close();
        return true;
    }
};

#endif //REPOSITORY_H