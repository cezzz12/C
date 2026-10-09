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
#include <QFile>
#include <algorithm>
class PatientService : public QObject {
    Q_OBJECT
private:
    QList<Patient> patients;
    QList<Doctor> doctors;
    QString patientsFileName = "patients.txt";
    QString doctorsFileName = "doctors.txt";
public:
    explicit PatientService(QObject* parent = nullptr) : QObject(parent) {}

    bool loadData(const QString& patientsFile,const QString& doctorsFile) {
        patients = PatientRepository::loadPatients(patientsFile);
        doctors = DoctorRepository::loadDoctors(doctorsFile);
        std::sort(patients.begin(), patients.end(),
            [](const Patient& a, const Patient& b) {
                return a.getAddmissionDate() < b.getAddmissionDate();
            });
        return !patients.isEmpty();
    }

    bool saveData() {
        return PatientRepository::savePatients(patientsFileName, patients);
    }

    const QList<Patient>& getPatients() const { return patients; }
    const QList<Doctor>& getDoctors() const { return doctors; }

    bool saveDataExplicitly() {
        return saveData();
    }

    bool addPatient(const QString& name,QString& errorMessage ,const QString& diagnosis = "",
                const QString& specialization_needed = "",
                const QString& current_doctor = "",
                const QDate& addmission_date = QDate::currentDate()) {
        if (name.trimmed().isEmpty()) {
            errorMessage = "Patient name cannot be empty.";
            return false;
        }

        if (addmission_date < QDate::currentDate()) {
            errorMessage = "Admission date cannot be in the past.";
            return false;
        }
        QString finalDiagnosis = diagnosis.trimmed().isEmpty() ? "undiagnosed" : diagnosis;
        QString finalSpecialization = specialization_needed.isNull() ? "" : specialization_needed;
        QString finalDoctor = current_doctor.isNull() ? "" : current_doctor;

        patients.append(Patient(name, finalDiagnosis, finalSpecialization, finalDoctor, addmission_date));
        std::sort(patients.begin(), patients.end(),
            [](const Patient& a, const Patient& b) {
                return a.getAddmissionDate() < b.getAddmissionDate();
            });
        emit patientsChanged();
        return true;
    }
    // Get patients with a specific current doctor
    QList<Patient> getPatientsForDoctor(const QString& doctorName) const {
        QList<Patient> filteredPatients;
        for (const Patient& patient : patients) {
            if (patient.getCurrentDoctor() == doctorName) {
                filteredPatients.append(patient);
            }
        }
        return filteredPatients;
    }
signals:
    void patientsChanged();
};
#endif //SERVICE_H
