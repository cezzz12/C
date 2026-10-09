//
// Created by Cezar on 24.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <QString>
#include <QDate>
#include <QList>
class Doctor{
  private:
    QString name;
    QString specialization;
  public:
    Doctor(const QString &name, const QString &specialization)
        : name(name), specialization(specialization) {}

    QString getName() const { return name; }
    QString getSpecialization() const { return specialization; }
    void setName(const QString &newName) { name = newName; }
    void setSpecialization(const QString &newSpecialization) { specialization = newSpecialization; }
};
class Patient{
  private:
    QString name;
    QString diagnosis;
    QString specialization_needed;
    QString current_doctor;
    QDate addmission_date;
  public:
    Patient(const QString &name, const QString &diagnosis, const QString &specialization_needed,
            const QString &current_doctor, const QDate &addmission_date)
        : name(name), diagnosis(diagnosis), specialization_needed(specialization_needed),
          current_doctor(current_doctor), addmission_date(addmission_date) {}

    QString getName() const { return name; }
    QString getDiagnosis() const { return diagnosis; }
    QString getSpecializationNeeded() const { return specialization_needed; }
    QString getCurrentDoctor() const { return current_doctor; }
    QDate getAddmissionDate() const { return addmission_date; }

    void setName(const QString &newname) { name = newname; }
    void setCurrentDoctor(const QString &newdoctor) { current_doctor = newdoctor; }
    void setDiagnosis(const QString &newdiagnosis) { diagnosis = newdiagnosis; }
    void setSpecializationNeeded(const QString &newspecialization) { specialization_needed = newspecialization; }
    void setAddmissionDate(const QDate &newdate) { addmission_date = newdate; }
};
#endif //DOMAIN_H
