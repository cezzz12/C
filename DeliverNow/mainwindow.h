#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QApplication>
#include <QCheckBox>
#include "domain.h"
#include "service.h"
#include "courierwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    DeliveryService* service;
    QTableWidget* packagesTable;
    QList<CourierWindow*> courierWindows;

    // Add package form
    QLineEdit* recipientLineEdit;
    QLineEdit* streetLineEdit;
    QSpinBox* numberSpinBox;
    QDoubleSpinBox* locationXSpinBox;
    QDoubleSpinBox* locationYSpinBox;
    QPushButton* addPackageButton;

    QLabel* statsLabel;

public:
    MainWindow(DeliveryService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), service(service) {

        setWindowTitle("Courier Company - Package Management");
        setMinimumSize(1200, 800);

        setupUI();
        populatePackages();
        updateStats();

        // Connect to service signals
        connect(service, &DeliveryService::packagesChanged, this, &MainWindow::onPackagesChanged);

        // Create courier windows
        createCourierWindows();
    }

    ~MainWindow() {
        // Clean up courier windows
        for (CourierWindow* window : courierWindows) {
            if (window) {
                window->close();
                delete window;
            }
        }
    }

private slots:
    void onAddPackage() {
        QString recipient = recipientLineEdit->text().trimmed();
        QString street = streetLineEdit->text().trimmed();
        int number = numberSpinBox->value();
        double locationX = locationXSpinBox->value();
        double locationY = locationYSpinBox->value();

        QString errorMessage;
        if (service->addPackage(recipient, street, number, locationX, locationY, errorMessage)) {
            QMessageBox::information(this, "Success", "Package added successfully!");

            // Clear form
            recipientLineEdit->clear();
            streetLineEdit->clear();
            numberSpinBox->setValue(1);
            locationXSpinBox->setValue(0.0);
            locationYSpinBox->setValue(0.0);
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }

    void onPackagesChanged() {
        populatePackages();
        updateStats();
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // Title
        QLabel* titleLabel = new QLabel("Courier Company - Package Management System");
        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; padding: 10px; background-color: #2196F3; color: white; border-radius: 5px;");
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);

        // Statistics
        statsLabel = new QLabel();
        statsLabel->setStyleSheet("padding: 8px; background-color: #f0f0f0; border-radius: 3px; font-weight: bold;");
        mainLayout->addWidget(statsLabel);

        // Main content area
        QHBoxLayout* contentLayout = new QHBoxLayout();

        // Left side - Package list
        QGroupBox* packagesGroup = new QGroupBox("All Packages");
        QVBoxLayout* packagesLayout = new QVBoxLayout(packagesGroup);

        packagesTable = new QTableWidget(this);
        packagesTable->setColumnCount(6);
        QStringList headers = {"Recipient", "Address", "Location", "Status", "Assigned Courier", "Actions"};
        packagesTable->setHorizontalHeaderLabels(headers);

        packagesTable->setAlternatingRowColors(true);
        packagesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        packagesTable->setSelectionMode(QAbstractItemView::SingleSelection);

        packagesLayout->addWidget(packagesTable);

        // Right side - Add package form
        QGroupBox* addPackageGroup = new QGroupBox("Add New Package");
        addPackageGroup->setMaximumWidth(350);
        QFormLayout* formLayout = new QFormLayout(addPackageGroup);

        recipientLineEdit = new QLineEdit();
        recipientLineEdit->setPlaceholderText("Enter recipient name");
        formLayout->addRow("Recipient:", recipientLineEdit);

        streetLineEdit = new QLineEdit();
        streetLineEdit->setPlaceholderText("Enter street name");
        formLayout->addRow("Street:", streetLineEdit);

        numberSpinBox = new QSpinBox();
        numberSpinBox->setRange(1, 9999);
        numberSpinBox->setValue(1);
        formLayout->addRow("Number:", numberSpinBox);

        locationXSpinBox = new QDoubleSpinBox();
        locationXSpinBox->setRange(-1000.0, 1000.0);
        locationXSpinBox->setDecimals(1);
        locationXSpinBox->setSingleStep(0.1);
        formLayout->addRow("Location X:", locationXSpinBox);

        locationYSpinBox = new QDoubleSpinBox();
        locationYSpinBox->setRange(-1000.0, 1000.0);
        locationYSpinBox->setDecimals(1);
        locationYSpinBox->setSingleStep(0.1);
        formLayout->addRow("Location Y:", locationYSpinBox);

        addPackageButton = new QPushButton("Add Package");
        addPackageButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 10px; border-radius: 5px; }");
        connect(addPackageButton, &QPushButton::clicked, this, &MainWindow::onAddPackage);
        formLayout->addRow(addPackageButton);

        // Add to content layout
        contentLayout->addWidget(packagesGroup, 3);
        contentLayout->addWidget(addPackageGroup, 1);

        mainLayout->addLayout(contentLayout);
    }

    void populatePackages() {
        const QList<Package>& allPackages = service->getPackages();
        const QList<Courier>& allCouriers = service->getCouriers();

        packagesTable->setRowCount(allPackages.size());

        for (int i = 0; i < allPackages.size(); i++) {
            const Package& package = allPackages[i];

            packagesTable->setItem(i, 0, new QTableWidgetItem(package.getRecipient()));
            packagesTable->setItem(i, 1, new QTableWidgetItem(package.getFullAddress()));
            packagesTable->setItem(i, 2, new QTableWidgetItem(
                QString("(%.1f, %.1f)").arg(package.getLocationX()).arg(package.getLocationY())
            ));
            packagesTable->setItem(i, 3, new QTableWidgetItem(
                package.getDeliveryStatus() ? "Delivered" : "Pending"
            ));

            // Find assigned courier
            QString assignedCourier = "Not Assigned";
            for (const Courier& courier : allCouriers) {
                if (package.isAssignedToCourier(courier)) {
                    assignedCourier = courier.getName();
                    break;
                }
            }
            packagesTable->setItem(i, 4, new QTableWidgetItem(assignedCourier));
            packagesTable->setItem(i, 5, new QTableWidgetItem("View Details"));

            // Set background color for delivered packages
            if (package.getDeliveryStatus()) {
                for (int j = 0; j < 6; j++) {
                    packagesTable->item(i, j)->setBackground(QColor(144, 238, 144)); // Light green
                }
            }

            // Make items read-only
            for (int j = 0; j < 6; j++) {
                packagesTable->item(i, j)->setFlags(packagesTable->item(i, j)->flags() & ~Qt::ItemIsEditable);
            }
        }

        packagesTable->resizeColumnsToContents();
    }

    void updateStats() {
        int total = service->getTotalPackages();
        int delivered = service->getDeliveredPackages();
        int pending = service->getUndeliveredPackages();

        statsLabel->setText(QString("Package Statistics: %1 Total | %2 Delivered | %3 Pending")
                           .arg(total).arg(delivered).arg(pending));
    }

    void createCourierWindows() {
        const QList<Courier>& couriers = service->getCouriers();

        for (const Courier& courier : couriers) {
            CourierWindow* courierWindow = new CourierWindow(courier, service);
            courierWindows.append(courierWindow);
            courierWindow->show();

            // Position windows in a cascade
            int index = courierWindows.size() - 1;
            courierWindow->move(100 + index * 50, 100 + index * 50);
        }
    }
};

// Main Application class to handle initialization
class MainApplication {
private:
    DeliveryService* service;
    MainWindow* mainWindow;

public:
    MainApplication() : service(nullptr), mainWindow(nullptr) {}

    ~MainApplication() {
        delete mainWindow;
        delete service;
    }

    bool initialize() {
        service = new DeliveryService();

        // Try to load data from files
        if (!service->loadData("couriers.txt", "packages.txt")) {
            QMessageBox::critical(nullptr, "Error",
                "Failed to load data files (couriers.txt and packages.txt).\n"
                "Please ensure the files exist and are properly formatted.");
            return false;
        }

        // Create main window
        mainWindow = new MainWindow(service);
        mainWindow->show();

        return true;
    }
};

#endif //MAINWINDOW_H