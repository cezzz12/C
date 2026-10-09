//
// Created by Cezar on 22.06.2025.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "domain.h"
#include "repository.h"
#include <QObject>
#include <QList>
#include <QSet>
#include <algorithm>

class DeliveryService : public QObject {
    Q_OBJECT

private:
    QList<Courier> couriers;
    QList<Package> packages;
    QString couriersFile;
    QString packagesFile;

public:
    explicit DeliveryService(QObject* parent = nullptr) : QObject(parent) {}

    bool loadData(const QString& couriersFileName, const QString& packagesFileName) {
        couriersFile = couriersFileName;
        packagesFile = packagesFileName;

        couriers = CourierRepository::loadCouriers(couriersFileName);
        packages = PackageRepository::loadPackages(packagesFileName);

        return !couriers.isEmpty() && !packages.isEmpty();
    }

    const QList<Courier>& getCouriers() const { return couriers; }
    const QList<Package>& getPackages() const { return packages; }

    // Get packages assigned to a specific courier
    QList<Package> getPackagesForCourier(const Courier& courier, bool onlyUndelivered = true) const {
        QList<Package> assignedPackages;

        for (const Package& package : packages) {
            if (onlyUndelivered && package.getDeliveryStatus()) {
                continue; // Skip delivered packages if only undelivered requested
            }

            if (package.isAssignedToCourier(courier)) {
                assignedPackages.append(package);
            }
        }

        return assignedPackages;
    }

    // Get packages for a specific street
    QList<Package> getPackagesForStreet(const Courier& courier, const QString& street, bool onlyUndelivered = true) const {
        QList<Package> streetPackages;

        for (const Package& package : packages) {
            if (onlyUndelivered && package.getDeliveryStatus()) {
                continue;
            }

            if (package.getStreet().compare(street, Qt::CaseInsensitive) == 0 &&
                package.isAssignedToCourier(courier)) {
                streetPackages.append(package);
            }
        }

        return streetPackages;
    }

    // Get all unique streets for a courier
    QStringList getStreetsForCourier(const Courier& courier) const {
        QSet<QString> streets;

        // Add assigned streets
        for (const QString& street : courier.getAssignedStreets()) {
            streets.insert(street);
        }

        // Add streets from packages within zone
        for (const Package& package : packages) {
            if (courier.isLocationInZone(package.getLocationX(), package.getLocationY())) {
                streets.insert(package.getStreet());
            }
        }

        QStringList sortedStreets = streets.values();
        sortedStreets.sort();
        return sortedStreets;
    }

    // Add a new package
    bool addPackage(const QString& recipient, const QString& street, int number,
                   double locationX, double locationY, QString& errorMessage) {
        // Validate input
        if (recipient.trimmed().isEmpty()) {
            errorMessage = "Recipient name cannot be empty.";
            return false;
        }

        if (street.trimmed().isEmpty()) {
            errorMessage = "Street cannot be empty.";
            return false;
        }

        if (number <= 0) {
            errorMessage = "Number must be positive.";
            return false;
        }

        // Check if package already exists
        for (const Package& package : packages) {
            if (package.getRecipient().compare(recipient.trimmed(), Qt::CaseInsensitive) == 0 &&
                package.getStreet().compare(street.trimmed(), Qt::CaseInsensitive) == 0 &&
                package.getNumber() == number) {
                errorMessage = "A package for this recipient at this address already exists.";
                return false;
            }
        }

        // Create and add new package
        Package newPackage(recipient.trimmed(), street.trimmed(), number, locationX, locationY, false);
        packages.append(newPackage);

        // Save to file
        PackageRepository::savePackages(packages, packagesFile);

        // Emit signal to notify UI
        emit packagesChanged();

        errorMessage.clear();
        return true;
    }

    // Deliver a package
    bool deliverPackage(const QString& recipient, const QString& street, int number, QString& errorMessage) {
        for (Package& package : packages) {
            if (package.getRecipient().compare(recipient, Qt::CaseInsensitive) == 0 &&
                package.getStreet().compare(street, Qt::CaseInsensitive) == 0 &&
                package.getNumber() == number) {

                if (package.getDeliveryStatus()) {
                    errorMessage = "Package is already delivered.";
                    return false;
                }

                package.setDeliveryStatus(true);

                // Save to file
                PackageRepository::savePackages(packages, packagesFile);

                // Emit signal to notify UI
                emit packagesChanged();

                errorMessage.clear();
                return true;
            }
        }

        errorMessage = "Package not found.";
        return false;
    }

    // Get delivery statistics
    int getTotalPackages() const { return packages.size(); }
    int getDeliveredPackages() const {
        int count = 0;
        for (const Package& package : packages) {
            if (package.getDeliveryStatus()) count++;
        }
        return count;
    }
    int getUndeliveredPackages() const { return getTotalPackages() - getDeliveredPackages(); }

signals:
    void packagesChanged();
};

#endif //SERVICE_H