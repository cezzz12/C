#ifndef COURIERWINDOW_H
#define COURIERWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QSplitter>
#include "domain.h"
#include "service.h"

class CourierWindow : public QMainWindow {
    Q_OBJECT

private:
    Courier courier;
    DeliveryService* service;
    QTableWidget* packagesTable;
    QComboBox* streetComboBox;
    QPushButton* deliverButton;
    QGraphicsView* zoneView;
    QGraphicsScene* zoneScene;
    QLabel* statsLabel;

public:
    CourierWindow(const Courier& courier, DeliveryService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), courier(courier), service(service) {
        
        setWindowTitle(QString("Courier: %1").arg(courier.getName()));
        setMinimumSize(1000, 700);
        
        setupUI();
        setupZoneVisualization();
        populateStreets();
        populatePackages();
        updateStats();
        
        // Connect to service signals
        connect(service, &DeliveryService::packagesChanged, this, &CourierWindow::onPackagesChanged);
    }

private slots:
    void onStreetChanged() {
        populatePackages();
        updateStats();
    }
    
    void onDeliverClicked() {
        int currentRow = packagesTable->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "No Selection", "Please select a package to deliver.");
            return;
        }
        
        QString recipient = packagesTable->item(currentRow, 0)->text();
        QString address = packagesTable->item(currentRow, 1)->text();
        
        // Parse street and number from address
        QStringList addressParts = address.split(' ');
        if (addressParts.size() < 2) {
            QMessageBox::warning(this, "Error", "Invalid address format.");
            return;
        }
        
        QString street = addressParts.mid(0, addressParts.size() - 1).join(' ');
        int number = addressParts.last().toInt();
        
        QString errorMessage;
        if (service->deliverPackage(recipient, street, number, errorMessage)) {
            QMessageBox::information(this, "Success", "Package delivered successfully!");
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }
    
    void onPackageSelectionChanged() {
        deliverButton->setEnabled(packagesTable->currentRow() >= 0);
    }
    
    void onPackagesChanged() {
        populateStreets();
        populatePackages();
        updateStats();
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
        
        // Left side - Packages and controls
        QWidget* leftWidget = new QWidget();
        QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);
        
        // Courier info
        QLabel* courierInfoLabel = new QLabel(
            QString("Courier: %1\nZone: Center(%.1f, %.1f) Radius: %.1f")
            .arg(courier.getName())
            .arg(courier.getCenterX())
            .arg(courier.getCenterY())
            .arg(courier.getRadius())
        );
        courierInfoLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #e3f2fd; border-radius: 5px;");
        leftLayout->addWidget(courierInfoLabel);
        
        // Statistics
        statsLabel = new QLabel();
        statsLabel->setStyleSheet("padding: 5px; background-color: #f5f5f5; border-radius: 3px;");
        leftLayout->addWidget(statsLabel);
        
        // Street filter
        QHBoxLayout* filterLayout = new QHBoxLayout();
        QLabel* streetLabel = new QLabel("Filter by Street:");
        streetLabel->setStyleSheet("font-weight: bold;");
        streetComboBox = new QComboBox();
        streetComboBox->setMinimumWidth(200);
        
        filterLayout->addWidget(streetLabel);
        filterLayout->addWidget(streetComboBox);
        filterLayout->addStretch();
        
        leftLayout->addLayout(filterLayout);
        
        // Connect combo box signal
        connect(streetComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CourierWindow::onStreetChanged);
        
        // Packages table
        packagesTable = new QTableWidget(this);
        packagesTable->setColumnCount(5);
        QStringList headers = {"Recipient", "Address", "Location", "Status", "Actions"};
        packagesTable->setHorizontalHeaderLabels(headers);
        
        packagesTable->setAlternatingRowColors(true);
        packagesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        packagesTable->setSelectionMode(QAbstractItemView::SingleSelection);
        
        // Connect selection changed signal
        connect(packagesTable, &QTableWidget::itemSelectionChanged, 
                this, &CourierWindow::onPackageSelectionChanged);
        
        leftLayout->addWidget(packagesTable);
        
        // Deliver button
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        deliverButton = new QPushButton("Deliver Selected Package");
        deliverButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 10px 20px; border-radius: 5px; }");
        deliverButton->setEnabled(false);
        connect(deliverButton, &QPushButton::clicked, this, &CourierWindow::onDeliverClicked);
        
        buttonLayout->addStretch();
        buttonLayout->addWidget(deliverButton);
        leftLayout->addLayout(buttonLayout);
        
        // Right side - Zone visualization
        QGroupBox* zoneGroup = new QGroupBox("Delivery Zone", this);
        QVBoxLayout* zoneLayout = new QVBoxLayout(zoneGroup);
        
        zoneView = new QGraphicsView(this);
        zoneScene = new QGraphicsScene(this);
        zoneView->setScene(zoneScene);
        zoneView->setMinimumSize(400, 400);
        
        zoneLayout->addWidget(zoneView);
        
        // Add widgets to main layout
        mainLayout->addWidget(leftWidget, 2);
        mainLayout->addWidget(zoneGroup, 1);
    }
    
    void setupZoneVisualization() {
        zoneScene->clear();
        
        // Set scene rectangle
        double margin = courier.getRadius() * 0.3;
        double sceneSize = (courier.getRadius() + margin) * 2;
        zoneScene->setSceneRect(-sceneSize/2, -sceneSize/2, sceneSize, sceneSize);
        
        // Draw courier zone (circle)
        QGraphicsEllipseItem* zoneCircle = zoneScene->addEllipse(
            courier.getCenterX() - courier.getRadius(),
            courier.getCenterY() - courier.getRadius(),
            courier.getRadius() * 2,
            courier.getRadius() * 2,
            QPen(Qt::blue, 2),
            QBrush(Qt::blue, Qt::DiagCrossPattern)
        );
        zoneCircle->setOpacity(0.3);
        
        // Draw center point
        zoneScene->addEllipse(
            courier.getCenterX() - 3,
            courier.getCenterY() - 3,
            6, 6,
            QPen(Qt::red, 2),
            QBrush(Qt::red)
        );
        
        // Add label for center
        QGraphicsTextItem* centerLabel = zoneScene->addText(
            QString("Center\n(%.1f, %.1f)").arg(courier.getCenterX()).arg(courier.getCenterY()),
            QFont("Arial", 8)
        );
        centerLabel->setPos(courier.getCenterX() + 5, courier.getCenterY() + 5);
        
        // Draw packages
        updatePackageVisualization();
        
        // Fit view
        zoneView->fitInView(zoneScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    
    void updatePackageVisualization() {
        // Remove existing package items (keep zone circle and center)
        QList<QGraphicsItem*> items = zoneScene->items();
        for (QGraphicsItem* item : items) {
            if (item->data(0).toString() == "package") {
                zoneScene->removeItem(item);
                delete item;
            }
        }
        
        // Add packages
        QList<Package> courierPackages = service->getPackagesForCourier(courier, false);
        for (const Package& package : courierPackages) {
            QColor color = package.getDeliveryStatus() ? Qt::green : Qt::red;
            QGraphicsEllipseItem* packageItem = zoneScene->addEllipse(
                package.getLocationX() - 2,
                package.getLocationY() - 2,
                4, 4,
                QPen(color, 1),
                QBrush(color)
            );
            packageItem->setData(0, "package");
            packageItem->setToolTip(QString("%1\n%2").arg(package.getRecipient()).arg(package.getFullAddress()));
        }
    }
    
    void populateStreets() {
        QString currentSelection = streetComboBox->currentText();
        
        QStringList streets = service->getStreetsForCourier(courier);
        
        streetComboBox->clear();
        streetComboBox->addItem("All Streets");
        streetComboBox->addItems(streets);
        
        // Restore previous selection if it still exists
        int index = streetComboBox->findText(currentSelection);
        if (index >= 0) {
            streetComboBox->setCurrentIndex(index);
        }
    }
    
    void populatePackages() {
        QString selectedStreet = streetComboBox->currentText();
        
        QList<Package> packages;
        if (selectedStreet == "All Streets") {
            packages = service->getPackagesForCourier(courier, true); // Only undelivered
        } else {
            packages = service->getPackagesForStreet(courier, selectedStreet, true); // Only undelivered
        }
        
        packagesTable->setRowCount(packages.size());
        
        for (int i = 0; i < packages.size(); i++) {
            const Package& package = packages[i];
            
            packagesTable->setItem(i, 0, new QTableWidgetItem(package.getRecipient()));
            packagesTable->setItem(i, 1, new QTableWidgetItem(package.getFullAddress()));
            packagesTable->setItem(i, 2, new QTableWidgetItem(
                QString("(%.1f, %.1f)").arg(package.getLocationX()).arg(package.getLocationY())
            ));
            packagesTable->setItem(i, 3, new QTableWidgetItem(
                package.getDeliveryStatus() ? "Delivered" : "Pending"
            ));
            packagesTable->setItem(i, 4, new QTableWidgetItem("Ready to deliver"));
            
            // Make items read-only
            for (int j = 0; j < 5; j++) {
                packagesTable->item(i, j)->setFlags(packagesTable->item(i, j)->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        packagesTable->resizeColumnsToContents();
        updatePackageVisualization();
    }
    
    void updateStats() {
        QList<Package> allPackages = service->getPackagesForCourier(courier, false);
        int total = allPackages.size();
        int delivered = 0;
        for (const Package& package : allPackages) {
            if (package.getDeliveryStatus()) delivered++;
        }
        int pending = total - delivered;
        
        statsLabel->setText(QString("Packages: %1 Total | %2 Delivered | %3 Pending")
                           .arg(total).arg(delivered).arg(pending));
    }
};

#endif // COURIERWINDOW_H