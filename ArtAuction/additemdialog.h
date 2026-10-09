//
// Created by Cezar on 22.06.2025.
//
#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "service.h"

class AddItemDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* nameLineEdit;
    QComboBox* categoryComboBox;
    QSpinBox* priceSpinBox;
    QPushButton* addButton;
    QPushButton* cancelButton;
    AuctionService* service;

public:
    AddItemDialog(AuctionService* service, QWidget* parent = nullptr)
        : QDialog(parent), service(service) {

        setWindowTitle("Add New Item");
        setModal(true);
        setFixedSize(350, 200);

        setupUI();
        connectSignals();
    }

private slots:
    void onAddClicked() {
        QString name = nameLineEdit->text();
        QString category = categoryComboBox->currentText();
        int price = priceSpinBox->value();

        QString errorMessage;
        if (service->addItem(name, category, price, errorMessage)) {
            accept(); // Close dialog with success
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }

    void onCancelClicked() {
        reject(); // Close dialog without adding
    }

private:
    void setupUI() {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        // Form layout for input fields
        QFormLayout* formLayout = new QFormLayout();

        // Name input
        nameLineEdit = new QLineEdit();
        nameLineEdit->setPlaceholderText("Enter item name");
        formLayout->addRow("Name:", nameLineEdit);

        // Category input (combo box with existing categories + ability to add new)
        categoryComboBox = new QComboBox();
        categoryComboBox->setEditable(true); // Allow typing new categories
        categoryComboBox->setPlaceholderText("Select or enter category");

        // Populate with existing categories
        QStringList categories = service->getCategories();
        categoryComboBox->addItems(categories);

        formLayout->addRow("Category:", categoryComboBox);

        // Price input
        priceSpinBox = new QSpinBox();
        priceSpinBox->setRange(0, 999999); // 0 to 999,999
        priceSpinBox->setSuffix(" $");
        priceSpinBox->setValue(0);
        formLayout->addRow("Current Price:", priceSpinBox);

        mainLayout->addLayout(formLayout);

        // Button layout
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        addButton = new QPushButton("Add Item");
        cancelButton = new QPushButton("Cancel");

        addButton->setDefault(true); // Enter key will trigger this

        buttonLayout->addStretch();
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonLayout);
    }

    void connectSignals() {
        connect(addButton, &QPushButton::clicked, this, &AddItemDialog::onAddClicked);
        connect(cancelButton, &QPushButton::clicked, this, &AddItemDialog::onCancelClicked);
    }
};

#endif //ADDITEMDIALOG_H
