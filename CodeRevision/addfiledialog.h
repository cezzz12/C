//
// Created by Cezar on 24.06.2025.
//
#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "service.h"

class AddFileDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* fileNameEdit;
    QPushButton* addButton;
    QPushButton* cancelButton;
    FileService* service;
    QString creatorName;

public:
    AddFileDialog(const QString& creator, FileService* service, QWidget* parent = nullptr)
        : QDialog(parent), service(service), creatorName(creator) {

        setWindowTitle("Add New File");
        setModal(true);
        resize(300, 120);

        setupUI();
    }

    private slots:
        void onAddClicked() {
        QString fileName = fileNameEdit->text().trimmed();
        QString errorMessage;

        if (service->addFile(fileName, creatorName, errorMessage)) {
            accept();
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }

private:
    void setupUI() {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        mainLayout->addWidget(new QLabel("File Name:"));

        fileNameEdit = new QLineEdit(this);
        mainLayout->addWidget(fileNameEdit);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        addButton = new QPushButton("Add", this);
        cancelButton = new QPushButton("Cancel", this);

        connect(addButton, &QPushButton::clicked, this, &AddFileDialog::onAddClicked);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(cancelButton);
        mainLayout->addLayout(buttonLayout);

        fileNameEdit->setFocus();
    }
};
#endif //ADDFILEDIALOG_H

