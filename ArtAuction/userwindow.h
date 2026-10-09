#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSplitter>
#include <QGroupBox>
#include <QSet>
#include "domain.h"
#include "service.h"
#include "additemdialog.h"

class UserWindow : public QMainWindow {
    Q_OBJECT

private:
    User user;
    AuctionService* service;
    QTableWidget* itemsTable;
    QTableWidget* offersTable;
    QComboBox* categoryComboBox;
    QPushButton* addItemButton;
    QLabel* selectedItemLabel;

public:
    UserWindow(const User& user, AuctionService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), user(user), service(service) {

        setWindowTitle(user.getName());
        setMinimumSize(1000, 700);

        setupUI();
        populateCategories();
        populateItems();

        // Connect to service signals
        connect(service, &AuctionService::itemsChanged, this, &UserWindow::onItemsChanged);
    }

private slots:
    void onCategoryChanged() {
        populateItems();
    }

    void onItemSelectionChanged() {
        int currentRow = itemsTable->currentRow();
        if (currentRow >= 0) {
            // Get the selected item name
            QString itemName = itemsTable->item(currentRow, 0)->text();

            // Find the item in service data
            const QList<Item>& allItems = service->getItems();
            QString selectedCategory = categoryComboBox->currentText();

            // Filter items based on selected category first
            QList<Item> filteredItems;
            if (selectedCategory == "All Categories") {
                filteredItems = allItems;
            } else {
                for (const Item& item : allItems) {
                    if (item.getCategory() == selectedCategory) {
                        filteredItems.append(item);
                    }
                }
            }

            // Find the selected item
            if (currentRow < filteredItems.size()) {
                const Item& selectedItem = filteredItems[currentRow];
                displayOffersForItem(selectedItem);
            }
        } else {
            clearOffersTable();
        }
    }

    void onAddItemClicked() {
        AddItemDialog dialog(service, this);
        dialog.exec(); // Modal dialog
    }

    void onItemsChanged() {
        // Refresh the UI when items change
        populateCategories();
        populateItems();
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // User info label
        QLabel* userInfoLabel = new QLabel(
            QString("User: %1 (%2) - Type: %3")
            .arg(user.getName())
            .arg(QString::number(user.getId()))
            .arg(user.getType())
        );
        userInfoLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #f0f0f0;");
        mainLayout->addWidget(userInfoLabel);

        // Category filter and add button section
        QHBoxLayout* topLayout = new QHBoxLayout();

        // Category filter
        QLabel* categoryLabel = new QLabel("Filter by Category:");
        categoryLabel->setStyleSheet("font-weight: bold;");
        categoryComboBox = new QComboBox();
        categoryComboBox->setMinimumWidth(200);

        topLayout->addWidget(categoryLabel);
        topLayout->addWidget(categoryComboBox);
        topLayout->addStretch();

        // Add item button (only for administrators)
        if (user.getType() == "administrator") {
            addItemButton = new QPushButton("Add New Item");
            addItemButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px 16px; }");
            connect(addItemButton, &QPushButton::clicked, this, &UserWindow::onAddItemClicked);
            topLayout->addWidget(addItemButton);
        }

        mainLayout->addLayout(topLayout);

        // Connect combo box signal
        connect(categoryComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &UserWindow::onCategoryChanged);

        // Create splitter for items and offers tables
        QSplitter* splitter = new QSplitter(Qt::Horizontal, this);

        // Left side - Items table
        QGroupBox* itemsGroup = new QGroupBox("Items", this);
        QVBoxLayout* itemsLayout = new QVBoxLayout(itemsGroup);

        itemsTable = new QTableWidget(this);
        itemsTable->setColumnCount(4);
        QStringList headers = {"Name", "Category", "Current Price", "Number of Offers"};
        itemsTable->setHorizontalHeaderLabels(headers);

        itemsTable->setAlternatingRowColors(true);
        itemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        itemsTable->setSelectionMode(QAbstractItemView::SingleSelection);

        // Connect selection changed signal
        connect(itemsTable, &QTableWidget::itemSelectionChanged, this, &UserWindow::onItemSelectionChanged);

        itemsLayout->addWidget(itemsTable);
        splitter->addWidget(itemsGroup);

        // Right side - Offers table
        QGroupBox* offersGroup = new QGroupBox("Offers for Selected Item", this);
        QVBoxLayout* offersLayout = new QVBoxLayout(offersGroup);

        selectedItemLabel = new QLabel("No item selected", this);
        selectedItemLabel->setStyleSheet("font-weight: bold; color: #666; padding: 5px;");
        offersLayout->addWidget(selectedItemLabel);

        offersTable = new QTableWidget(this);
        offersTable->setColumnCount(3);
        QStringList offerHeaders = {"User ID", "Date", "Offer Amount"};
        offersTable->setHorizontalHeaderLabels(offerHeaders);

        offersTable->setAlternatingRowColors(true);
        offersTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        offersLayout->addWidget(offersTable);
        splitter->addWidget(offersGroup);

        // Set splitter proportions (60% items, 40% offers)
        splitter->setStretchFactor(0, 3);
        splitter->setStretchFactor(1, 2);

        mainLayout->addWidget(splitter);
    }

    void populateCategories() {
        QString currentSelection = categoryComboBox->currentText();

        // Get all unique categories
        QSet<QString> categories;
        const QList<Item>& items = service->getItems();

        for (const Item& item : items) {
            categories.insert(item.getCategory());
        }

        // Populate combo box
        categoryComboBox->clear();
        categoryComboBox->addItem("All Categories"); // Default option to show all

        QStringList sortedCategories = categories.values();
        sortedCategories.sort();
        categoryComboBox->addItems(sortedCategories);

        // Restore previous selection if it still exists
        int index = categoryComboBox->findText(currentSelection);
        if (index >= 0) {
            categoryComboBox->setCurrentIndex(index);
        }
    }

    void populateItems() {
        const QList<Item>& allItems = service->getItems();
        QString selectedCategory = categoryComboBox->currentText();

        // Filter items based on selected category
        QList<Item> filteredItems;
        if (selectedCategory == "All Categories") {
            filteredItems = allItems;
        } else {
            for (const Item& item : allItems) {
                if (item.getCategory() == selectedCategory) {
                    filteredItems.append(item);
                }
            }
        }

        // Populate table with filtered items
        itemsTable->setRowCount(filteredItems.size());

        for (int i = 0; i < filteredItems.size(); i++) {
            const Item& item = filteredItems[i];

            itemsTable->setItem(i, 0, new QTableWidgetItem(item.getName()));
            itemsTable->setItem(i, 1, new QTableWidgetItem(item.getCategory()));
            itemsTable->setItem(i, 2, new QTableWidgetItem(QString::number(item.getCurrentPrice()) + " $"));
            itemsTable->setItem(i, 3, new QTableWidgetItem(QString::number(item.getOffers().size())));

            // Make items read-only
            for (int j = 0; j < 4; j++) {
                itemsTable->item(i, j)->setFlags(itemsTable->item(i, j)->flags() & ~Qt::ItemIsEditable);
            }
        }

        // Resize columns to content
        itemsTable->resizeColumnsToContents();

        // Clear offers table when items change
        clearOffersTable();
    }

    void displayOffersForItem(const Item& item) {
        selectedItemLabel->setText(QString("Offers for: %1").arg(item.getName()));

        const QList<Offer>& offers = item.getOffers();
        offersTable->setRowCount(offers.size());

        for (int i = 0; i < offers.size(); i++) {
            const Offer& offer = offers[i];

            int userId = std::get<0>(offer);
            QDate date = std::get<1>(offer);
            int amount = std::get<2>(offer);


            User user = service->getUserById(userId);
            QString userDisplay = user.getId() > 0 ?
                QString("%1 (%2)").arg(user.getName()).arg(userId) :
                QString::number(userId);

            offersTable->setItem(i, 0, new QTableWidgetItem(userDisplay));
            offersTable->setItem(i, 1, new QTableWidgetItem(date.toString("yyyy-MM-dd")));
            offersTable->setItem(i, 2, new QTableWidgetItem(QString::number(amount) + " $"));

            // Make items read-only
            for (int j = 0; j < 3; j++) {
                offersTable->item(i, j)->setFlags(offersTable->item(i, j)->flags() & ~Qt::ItemIsEditable);
            }
        }

        // Resize columns to content
        offersTable->resizeColumnsToContents();

        // Sort offers by amount (highest first)
        offersTable->sortItems(2, Qt::DescendingOrder);
    }

    void clearOffersTable() {
        selectedItemLabel->setText("No item selected");
        offersTable->setRowCount(0);
    }
};

#endif // USERWINDOW_H