//
// Created by Cezar on 24.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <QString>
#include <QList>
#include <QDebug>
class Astronomer{
private:
    QString name;
    QString constellation;
public:
    Astronomer(const QString &name, const QString &constellation)
        : name(name), constellation(constellation) {}

    QString getName() const { return name; }
    QString getConstellation() const { return constellation; }

    void setName(const QString &newName) { name = newName; }
    void setConstellation(const QString &newConstellation) { constellation = newConstellation; }


};
class Star{
private:
    QString name;
    QString constellation;
    int RA; // Right Ascension
    int DEC; // Declination
    int diameter;
public:
    Star():  RA(0), DEC(0), diameter(0) {}
    Star(const QString &name, const QString &constellation, int RA, int DEC, int diameter)
        : name(name), constellation(constellation), RA(RA), DEC(DEC), diameter(diameter) {}

    QString getName() const { return name; }
    QString getConstellation() const { return constellation; }
    int getRA() const { return RA; }
    int getDEC() const { return DEC; }
    int getDiameter() const { return diameter; }

    void setName(const QString &newName) { name = newName; }
    void setConstellation(const QString &newConstellation) { constellation = newConstellation; }
    void setRA(int newRA) { RA = newRA; }
    void setDEC(int newDEC) { DEC = newDEC; }
    void setDiameter(int newDiameter) { diameter = newDiameter; }


};
#endif //DOMAIN_H
