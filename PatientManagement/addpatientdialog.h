//
// Created by Cezar on 24.06.2025.
//

#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "service.h"
class AddPatientDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* nameEdit;
    QLineEdit* diagnosisEdit;
    QLineEdit* specializationNeededEdit;
    QLineEdit* currentDoctorEdit;
    QLineEdit* admissionDateEdit;
    QPushButton* addButton;
    QPushButton* cancelButton;
    PatientService* service;
public:
    AddPatientDialog(PatientService* service, QWidget* parent = nullptr)
        : QDialog(parent), service(service) {

        setWindowTitle("Add New Patient");
        setModal(true);
        resize(400, 300);

        setupUI();
    }
private slots:
    void onAddClicked() {
        QString name = nameEdit->text().trimmed();
        QString diagnosis = diagnosisEdit->text().trimmed();
        QString specializationNeeded = specializationNeededEdit->text().trimmed();
        QString currentDoctor = currentDoctorEdit->text().trimmed();
        QDate admissionDate = QDate::fromString(admissionDateEdit->text(), "yyyy-MM-dd");

        QString errorMessage;
        if (service->addPatient(name, errorMessage, diagnosis, specializationNeeded, currentDoctor, admissionDate)) {
            accept();
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }
private:
    void setupUI() {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        mainLayout->addWidget(new QLabel("Name:"));
        nameEdit = new QLineEdit(this);
        mainLayout->addWidget(nameEdit);

        mainLayout->addWidget(new QLabel("Diagnosis:"));
        diagnosisEdit = new QLineEdit(this);
        mainLayout->addWidget(diagnosisEdit);

        mainLayout->addWidget(new QLabel("Specialization Needed:"));
        specializationNeededEdit = new QLineEdit(this);
        mainLayout->addWidget(specializationNeededEdit);

        mainLayout->addWidget(new QLabel("Current Doctor:"));
        currentDoctorEdit = new QLineEdit(this);
        mainLayout->addWidget(currentDoctorEdit);

        mainLayout->addWidget(new QLabel("Admission Date (yyyy-MM-dd):"));
        admissionDateEdit = new QLineEdit(this);
        mainLayout->addWidget(admissionDateEdit);

        // Buttons
        addButton = new QPushButton("Add", this);
        connect(addButton, &QPushButton::clicked, this, &AddPatientDialog::onAddClicked);

        cancelButton = new QPushButton("Cancel", this);
        connect(cancelButton, &QPushButton::clicked, this, &AddPatientDialog::reject);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch();
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonLayout);
    }
};
#endif //ADDPATIENTDIALOG_H
