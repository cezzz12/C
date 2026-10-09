//
// Created by Cezar on 24.06.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QObject>
#include <QList>
#include <QMessageBox>
#include "domain.h"
#include "service.h"
#include "doctorwindow.h"

class mainApplication : public QObject {
    Q_OBJECT
private:
    PatientService service;
    QList<DoctorWindow*> DoctorWindows;
public:
    mainApplication(QObject* parent = nullptr) : QObject(parent) {}

    ~mainApplication() {
        service.saveDataExplicitly(); // Save data before exiting
        for (DoctorWindow* window : DoctorWindows) {
            delete window;
        }
    }

    bool initialize(const QString& patientsFile = "patients.txt",
                    const QString& doctorsFile = "doctors.txt") {
        if (!service.loadData(patientsFile, doctorsFile)) {
            QMessageBox::critical(nullptr, "Error",
                "Failed to load data files. Please check that patients.txt exists and contains valid data.");
            return false;
        }

        // Create windows for each doctor
        const QList<Doctor>& doctors = service.getDoctors();
        for (const Doctor& doctor : doctors) {
            DoctorWindow* window = new DoctorWindow(doctor, &service);
            DoctorWindows.append(window);
            window->show();
        }

        return true;
    }
private slots:
    void onApplicationAboutToQuit() {
        // Save data when application is about to quit
        service.saveDataExplicitly();
    }
};
#endif //MAINWINDOW_H
