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
#include <QDate>

class DoctorRepository {
  public:
    static QList<Doctor> loadDoctors(const QString &fileName) {
        QList<Doctor> doctors;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for reading:" << fileName;
            return doctors;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 2) {
                doctors.append(Doctor(parts[0], parts[1]));
            }
        }
        file.close();
        return doctors;
    }
};
class PatientRepository {
public:
    static QList<Patient> loadPatients(const QString &fileName) {
        QList<Patient> patients;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for reading:" << fileName;
            return patients;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 5) {
                patients.append(Patient(parts[0], parts[1], parts[2], parts[3], QDate::fromString(parts[4], "yyyy-MM-dd")));
            }
        }
        file.close();
        return patients;
    }
    static bool savePatients(const QString &fileName, const QList<Patient> &patients) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for writing:" << fileName;
            return false;
        }
        QTextStream out(&file);
        for (const Patient &patient : patients) {
            out << patient.getName() << ","
                << patient.getDiagnosis() << ","
                << patient.getSpecializationNeeded() << ","
                << patient.getCurrentDoctor() << ","
                << patient.getAddmissionDate().toString("yyyy-MM-dd") << "\n";
        }
        file.close();
        return true;
    }
};
#endif //REPOSITORY_H
