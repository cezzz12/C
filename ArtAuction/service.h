//
// Created by Cezar on 22.06.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "domain.h"
#include "repository.h"
#include <QObject>
#include <QList>
#include <QSet>
#include <algorithm>

class AuctionService : public QObject {
    Q_OBJECT

  private:
    QList<User> users;
    QList<Item> items;
    QString itemsFileName = "items.txt";

  public:
    explicit AuctionService(QObject* parent = nullptr) : QObject(parent) {}

    bool loadData(const QString& usersFile, const QString& itemsFile) {
        users = UserRepository::loadUsers(usersFile);
        items = ItemRepository::loadItems(itemsFile);

        // Sort items by current price
        std::sort(items.begin(), items.end(),
            [](const Item& a, const Item& b) {
                return a.getCurrentPrice() < b.getCurrentPrice();
            });

        return !users.isEmpty() && !items.isEmpty();
    }
    bool saveData() {
        if (itemsFileName.isEmpty()) {
            return false;
        }
        return ItemRepository::saveItems(itemsFileName, items);
    }

    const QList<User>& getUsers() const { return users; }
    const QList<Item>& getItems() const { return items; }

    User getUserById(int id) const {
        for (const User& user : users) {
            if (user.getId() == id) {
                return user;
            }
        }
        return User(); // Return empty user if not found
    }

    // Add new item (for administrators)
    bool addItem(const QString& name, const QString& category, int currentPrice, QString& errorMessage) {
        // Validate input
        if (name.trimmed().isEmpty()) {
            errorMessage = "Item name cannot be empty.";
            return false;
        }

        if (category.trimmed().isEmpty()) {
            errorMessage = "Category cannot be empty.";
            return false;
        }

        if (currentPrice < 0) {
            errorMessage = "Current price cannot be negative.";
            return false;
        }

        // Check if item with same name already exists
        for (const Item& item : items) {
            if (item.getName().toLower() == name.trimmed().toLower()) {
                errorMessage = "An item with this name already exists.";
                return false;
            }
        }

        // Create and add new item
        Item newItem(name.trimmed(), category.trimmed(), currentPrice);
        items.append(newItem);

        // Re-sort items by current price
        std::sort(items.begin(), items.end(),
            [](const Item& a, const Item& b) {
                return a.getCurrentPrice() < b.getCurrentPrice();
            });

        // Emit signal to notify UI about the change
        emit itemsChanged();

        errorMessage.clear();
        return true;
    }

    // Get all unique categories
    QStringList getCategories() const {
        QSet<QString> categorySet;
        for (const Item& item : items) {
            categorySet.insert(item.getCategory());
        }
        QStringList categories = categorySet.values();
        categories.sort();
        return categories;
    }
    bool saveDataExplicitly() {

        return saveData();
    }

signals:
    void itemsChanged();
};

#endif //SERVICE_H