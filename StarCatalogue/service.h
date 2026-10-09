//
// Created by Cezar on 24.06.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <QObject>
#include <QList>
#include <algorithm>
#include "domain.h"
#include "repository.h"
#include <QDebug>
class StarService : public QObject {
    Q_OBJECT
private:
    QList<Astronomer> astronomers;
    QList<Star> stars;
public:
  explicit StarService(QObject* parent = nullptr) : QObject(parent) {}

    bool loadData(const QString& astronomersFile, const QString& starsFile) {
        astronomers = AstronomerRepository::loadAstronomers(astronomersFile);
        stars = StarRepository::loadStars(starsFile);
        std::sort(stars.begin(), stars.end(),
            [](const Star& a, const Star& b) {
                return a.getConstellation() < b.getConstellation();
            });
        return !astronomers.isEmpty() && !stars.isEmpty();
    }

    bool saveData() {
        if (astronomers.isEmpty() || stars.isEmpty()) {
            return false;
        }
        return StarRepository::saveStars("stars.txt", stars);
    }

    const QList<Astronomer>& getAstronomers() const { return astronomers; }
    const QList<Star>& getStars() const { return stars; }

    bool saveDataExplicitly() {
        return saveData();
    }
    // Find an astronomer by name
    bool findAstronomer(const QString& name, Astronomer*& astronomer) {
        for (int i = 0; i < astronomers.size(); ++i) {
            if (astronomers[i].getName().toLower() == name.toLower()) {
                astronomer = &astronomers[i];
                return true;
            }
        }
        astronomer = nullptr;
        return false;
    }
    //add star by name,RA,DEC,diameter ;it will have same constellation as the astronomer that added it
    bool addStar(const QString& name, int RA, int DEC, int diameter, const QString& astronomerName, QString& errorMessage) {
        if (name.trimmed().isEmpty()) {
            errorMessage = "Star name cannot be empty.";
            return false;
        }

        // Check if star already exists
        for (const Star& star : stars) {
            if (star.getName().toLower() == name.trimmed().toLower()) {
                errorMessage = "A star with this name already exists.";
                return false;
            }
        }
        // diameter must be positive
        if (diameter <= 0) {
            errorMessage = "Diameter must be a positive integer.";
            return false;
        }

        Astronomer* astronomer = nullptr;
        if (!findAstronomer(astronomerName, astronomer)) {
            errorMessage = "Astronomer not found.";
            return false;
        }

        stars.append(Star(name.trimmed(), astronomer->getConstellation(), RA, DEC, diameter));
        std::sort(stars.begin(), stars.end(),
            [](const Star& a, const Star& b) {
                return a.getName() < b.getName();
            });

        emit starsChanged();
        return true;
    }
    // Filter stars by constellation
    QList<Star> filterStarsByConstellation(const QString& constellation) const {
        QList<Star> filteredStars;
        for (const Star& star : stars) {
            if (star.getConstellation().toLower() == constellation.toLower()) {
                filteredStars.append(star);
            }
        }
        return filteredStars;
    }
signals:
    void starsChanged();
};
#endif //SERVICE_H
