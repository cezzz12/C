//
// Created by Cezar on 24.06.2025.
//

#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "service.h"
class AddEventDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* eventNameEdit;
    QLineEdit* organizerEdit;
    QLineEdit* latitudeEdit;
    QLineEdit* longitudeEdit;
    QLineEdit* dateEdit;
    QLineEdit* descriptionEdit;
    QPushButton* addButton;
    QPushButton* cancelButton;
    EventService* service;
public:
    AddEventDialog(const QString& organizer, EventService* service, QWidget* parent = nullptr)
        : QDialog(parent), service(service) {

        setWindowTitle("Add New Event");
        setModal(true);
        resize(400, 300);

        setupUI();
    }
private slots:
    void onAddClicked() {
        QString name = eventNameEdit->text().trimmed();
        int latitude = latitudeEdit->text().toInt();
        int longitude = longitudeEdit->text().toInt();
        QDate::fromString(dateEdit->text(), "yyyy-MM-dd");
        QString description = descriptionEdit->text().trimmed();

        QString errorMessage;
        if (service->addEvent(name, organizerEdit->text(), latitude, longitude, QDate::fromString(dateEdit->text(), "yyyy-MM-dd") , description, errorMessage)) {
            accept();
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }
private:
  void setupUI() {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        mainLayout->addWidget(new QLabel("Event Name:"));
        eventNameEdit = new QLineEdit(this);
        mainLayout->addWidget(eventNameEdit);

        mainLayout->addWidget(new QLabel("Organizer:"));
        organizerEdit = new QLineEdit(this);
        mainLayout->addWidget(organizerEdit);

        mainLayout->addWidget(new QLabel("Latitude:"));
        latitudeEdit = new QLineEdit(this);
        mainLayout->addWidget(latitudeEdit);

        mainLayout->addWidget(new QLabel("Longitude:"));
        longitudeEdit = new QLineEdit(this);
        mainLayout->addWidget(longitudeEdit);

        mainLayout->addWidget(new QLabel("Date (yyyy-MM-dd):"));
        dateEdit = new QLineEdit(this);
        mainLayout->addWidget(dateEdit);

        mainLayout->addWidget(new QLabel("Description:"));
        descriptionEdit = new QLineEdit(this);
        mainLayout->addWidget(descriptionEdit);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        addButton = new QPushButton("Add", this);
        cancelButton = new QPushButton("Cancel", this);

        connect(addButton, &QPushButton::clicked, this, &AddEventDialog::onAddClicked);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(cancelButton);
        mainLayout->addLayout(buttonLayout);
    }
};
#endif //ADDEVENTDIALOG_H
