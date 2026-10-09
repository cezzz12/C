//
// Created by Cezar on 24.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <QFile>
#include <QTextStream>
#include <QList>
#include "domain.h"
#include <QDebug>
class AstronomerRepository {
  public:
    static QList<Astronomer> loadAstronomers(const QString &filename) {
        QList<Astronomer> astronomers;
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file:" << filename;
            return astronomers;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 2) {
                astronomers.append(Astronomer(parts[0].trimmed(), parts[1].trimmed()));
            }
        }
        file.close();
        return astronomers;
    }
};
class StarRepository {
  public:
    static QList<Star> loadStars(const QString &filename) {
        QList<Star> stars;
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file:" << filename;
            return stars;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 5) {
                stars.append(Star(parts[0].trimmed(), parts[1].trimmed(),
                                  parts[2].toInt(), parts[3].toInt(), parts[4].toInt()));
            }
        }
        file.close();
        return stars;
    }
    static bool saveStars(const QString &filename, const QList<Star> &stars) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for writing:" << filename;
            return false;
        }
        QTextStream out(&file);
        for (const Star &star : stars) {
            out << star.getName() << ", "
                << star.getConstellation() << ", "
                << star.getRA() << ", "
                << star.getDEC() << ", "
                << star.getDiameter() << "\n";
        }
        file.close();
        return true;
    }
};
#endif //REPOSITORY_H
