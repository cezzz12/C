//
// Created by Cezar on 24.06.2025.
//

#ifndef TABLEVIEWASTRONOMERWINDOW_H
#define TABLEVIEWASTRONOMERWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>
#include "domain.h"
#include "service.h"
#include "StarModel.h"

class TableViewAstronomerWindow : public QMainWindow {
    Q_OBJECT

private:
    Astronomer astronomer;
    StarService* service;
    StarModel* starModel;

    // UI Components
    QTableView* tableView;
    QCheckBox* constellationCheckBox;
    QLineEdit* starNameEdit;
    QSpinBox* raSpinBox;
    QSpinBox* decSpinBox;
    QSpinBox* diameterSpinBox;
    QPushButton* addStarButton;
    QLineEdit* searchEdit;
    QListWidget* searchResultsList;

public:
    explicit TableViewAstronomerWindow(const Astronomer& astronomer, StarService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), astronomer(astronomer), service(service) {

        setWindowTitle(astronomer.getName());
        setMinimumSize(800, 600);

        // Create the star model
        starModel = new StarModel(service, this);

        setupUI();
    }

private slots:
    void onConstellationCheckBoxToggled(bool checked) {
        starModel->setConstellationFilter(astronomer.getConstellation(), checked);
    }

    void onAddStarClicked() {
        QString name = starNameEdit->text().trimmed();
        int ra = raSpinBox->value();
        int dec = decSpinBox->value();
        int diameter = diameterSpinBox->value();

        QString errorMessage;
        if (service->addStar(name, ra, dec, diameter, astronomer.getName(), errorMessage)) {
            // Success - clear the input fields
            starNameEdit->clear();
            raSpinBox->setValue(0);
            decSpinBox->setValue(0);
            diameterSpinBox->setValue(1);

            QMessageBox::information(this, "Success", "Star added successfully!");
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }

    void onSearchTextChanged(const QString& text) {
        updateSearchResults(text);
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // Table view for stars
        tableView = new QTableView(this);
        tableView->setModel(starModel);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setAlternatingRowColors(true);
        tableView->resizeColumnsToContents();

        // Constellation filter checkbox
        constellationCheckBox = new QCheckBox(QString("Show only stars in %1 constellation").arg(astronomer.getConstellation()), this);
        connect(constellationCheckBox, &QCheckBox::toggled, this, &TableViewAstronomerWindow::onConstellationCheckBoxToggled);

        // Add star section
        QWidget* addStarWidget = new QWidget(this);
        QFormLayout* addStarLayout = new QFormLayout(addStarWidget);

        starNameEdit = new QLineEdit(this);
        raSpinBox = new QSpinBox(this);
        raSpinBox->setRange(-180, 180);
        decSpinBox = new QSpinBox(this);
        decSpinBox->setRange(-90, 90);
        diameterSpinBox = new QSpinBox(this);
        diameterSpinBox->setRange(1, 1000000);
        diameterSpinBox->setValue(1);

        addStarButton = new QPushButton("Add Star", this);
        connect(addStarButton, &QPushButton::clicked, this, &TableViewAstronomerWindow::onAddStarClicked);

        addStarLayout->addRow("Star Name:", starNameEdit);
        addStarLayout->addRow("RA:", raSpinBox);
        addStarLayout->addRow("DEC:", decSpinBox);
        addStarLayout->addRow("Diameter:", diameterSpinBox);
        addStarLayout->addRow("", addStarButton);

        // Search section
        QWidget* searchWidget = new QWidget(this);
        QVBoxLayout* searchLayout = new QVBoxLayout(searchWidget);

        searchEdit = new QLineEdit(this);
        searchEdit->setPlaceholderText("Search stars by name...");
        connect(searchEdit, &QLineEdit::textChanged, this, &TableViewAstronomerWindow::onSearchTextChanged);

        searchResultsList = new QListWidget(this);
        searchResultsList->setMaximumHeight(150);

        searchLayout->addWidget(new QLabel("Search Stars:", this));
        searchLayout->addWidget(searchEdit);
        searchLayout->addWidget(searchResultsList);

        // Add all widgets to main layout
        mainLayout->addWidget(constellationCheckBox);
        mainLayout->addWidget(tableView);
        mainLayout->addWidget(addStarWidget);
        mainLayout->addWidget(searchWidget);
    }

    void updateSearchResults(const QString& searchText) {
        searchResultsList->clear();

        if (searchText.trimmed().isEmpty()) {
            return;
        }

        const QList<Star>& allStars = service->getStars();
        for (const Star& star : allStars) {
            if (star.getName().toLower().contains(searchText.toLower())) {
                QString itemText = QString("%1 (%2) - RA: %3, DEC: %4, Diameter: %5")
                                   .arg(star.getName())
                                   .arg(star.getConstellation())
                                   .arg(star.getRA())
                                   .arg(star.getDEC())
                                   .arg(star.getDiameter());
                searchResultsList->addItem(itemText);
            }
        }
    }
};

#endif //TABLEVIEWASTRONOMERWINDOW_H