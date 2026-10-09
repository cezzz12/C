//
// Created by Cezar on 25.06.2025.
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
    AddEventDialog(const QString& organizer, EventService* service, QWidget* parent = nullptr);

    private slots:
        void onAddClicked();

private:
    void setupUI();
};

#endif //ADDEVENTDIALOG_H