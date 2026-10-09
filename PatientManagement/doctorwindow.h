//
// Created by Cezar on 24.06.2025.
//

#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include "domain.h"
#include "service.h"
#include "addpatientdialog.h"
class DoctorWindow : public QMainWindow {
    Q_OBJECT
private:
    Doctor doctor;
    PatientService* service;
    QTableWidget* patientsTable;
    QPushButton* addPatientButton;
    QLabel* doctorInfoLabel;
    QCheckBox* showPatientsForCurrentDoctorCheckBox;

public:
    DoctorWindow(const Doctor& doctor, PatientService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), doctor(doctor), service(service) {

        setWindowTitle("Doctor: " + doctor.getName());
        setMinimumSize(800, 600);

        setupUI();
        populatePatients();

        // Connect to service signals
        connect(service, &PatientService::patientsChanged, this, &DoctorWindow::onPatientsChanged);
    }
private:
  void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // Doctor info label
        doctorInfoLabel = new QLabel();
        doctorInfoLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #f0f0f0; border: 1px solid #ccc;");
        updateDoctorInfo();
        mainLayout->addWidget(doctorInfoLabel);

        // Checkbox for filtering patients for current doctor
        showPatientsForCurrentDoctorCheckBox = new QCheckBox("Show only patients for this doctor");
        connect(showPatientsForCurrentDoctorCheckBox, &QCheckBox::toggled, this, &DoctorWindow::onShowPatientsForCurrentDoctorToggled);
        mainLayout->addWidget(showPatientsForCurrentDoctorCheckBox);

        // Patients table
        patientsTable = new QTableWidget(this);
        patientsTable->setColumnCount(5);
        patientsTable->setHorizontalHeaderLabels({"Name", "Diagnosis", "Specialization Needed", "Admission Date", "Current Doctor"});
        patientsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        mainLayout->addWidget(patientsTable);

        // Add patient button
        addPatientButton = new QPushButton("Add Patient");
        connect(addPatientButton, &QPushButton::clicked, this, &DoctorWindow::onAddPatientClicked);
        mainLayout->addWidget(addPatientButton);

        // Button layout
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch();
        buttonLayout->addWidget(addPatientButton);

        mainLayout->addLayout(buttonLayout);
    }

    void populatePatients() {
        QList<Patient> patientsToShow;

        if (showPatientsForCurrentDoctorCheckBox->isChecked()) {
            patientsToShow = service->getPatientsForDoctor(doctor.getName());
        } else {
            patientsToShow = service->getPatients();
        }

        patientsTable->setRowCount(patientsToShow.size());

        for (int i = 0; i < patientsToShow.size(); ++i) {
            const Patient& patient = patientsToShow[i];

            QTableWidgetItem* nameItem = new QTableWidgetItem(patient.getName());
            QTableWidgetItem* diagnosisItem =new QTableWidgetItem(patient.getDiagnosis());
            QTableWidgetItem* specializationItem = new QTableWidgetItem(patient.getSpecializationNeeded());
            QTableWidgetItem* admissionDateItem = new QTableWidgetItem(patient.getAddmissionDate().toString("yyyy-MM-dd"));
            QTableWidgetItem* currentDoctorItem = new QTableWidgetItem(patient.getCurrentDoctor());
            //Highlight patients with current doctor as this doctor
            if (patient.getCurrentDoctor() == doctor.getName()) {
                nameItem->setBackground(Qt::green);
                diagnosisItem->setBackground(Qt::green);
                specializationItem->setBackground(Qt::green);
                admissionDateItem->setBackground(Qt::green);
                currentDoctorItem->setBackground(Qt::green);
            }
            patientsTable->setItem(i, 0, nameItem);
            patientsTable->setItem(i, 1, diagnosisItem);
            patientsTable->setItem(i, 2, specializationItem);
            patientsTable->setItem(i, 3, admissionDateItem);
            patientsTable->setItem(i, 4, currentDoctorItem);
            }
        patientsTable->resizeColumnsToContents();
        }
        void updateDoctorInfo() {
            doctorInfoLabel->setText(QString("Doctor: %1\nSpecialization: %2")
                                     .arg(doctor.getName())
                                     .arg(doctor.getSpecialization()));
        }
private slots:
    void onPatientsChanged() {
        populatePatients();
    }

    void onAddPatientClicked() {
        AddPatientDialog dialog(service, this);
        if (dialog.exec() == QDialog::Accepted) {
            populatePatients();
        }
    }

    void onShowPatientsForCurrentDoctorToggled(bool checked) {
        populatePatients();
    }
};
#endif //DOCTORWINDOW_H
