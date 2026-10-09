//
// Created by Cezar on 22.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QList>
#include <QString>
#include "domain.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

class UserRepository {
  public:
    static QList<User> loadUsers(const QString &fileName) {
        QList<User> users;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for reading:" << fileName;
            return users;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3) {
                users.append(User(parts[0], parts[1].toInt(), parts[2]));
            }
        }
        file.close();
        return users;
    }
};
class ItemRepository {
public:
    static QList<Item> loadItems(const QString& filename) {
        QList<Item> items;
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open items file:" << filename;
            return items;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;
            QStringList parts = line.split(',');
            if (parts.size() >= 3) {
                QString name = parts[0].trimmed();
                QString category = parts[1].trimmed();
                int currentPrice = parts[2].trimmed().toInt();

                Item item(name, category, currentPrice);
                for (int i = 3; i < parts.size(); i++) {
                    QString offerStr = parts[i].trimmed();
                    QStringList offerParts = offerStr.split(':');
                    if (offerParts.size() >= 3) {
                        int userId = offerParts[0].toInt();
                        QDate date = QDate::fromString(offerParts[1], "yyyy-MM-dd");
                        int sum = offerParts[2].toInt();
                        item.addOffer(std::make_tuple(userId, date, sum));
                    }
                }

                items.append(item);
            }
        }

        return items;
    }
    static bool saveItems(const QString& filename, const QList<Item>& items) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Cannot open items file for writing:" << filename;
            return false;
        }

        QTextStream out(&file);
        for (const Item& item : items) {
            // Write basic item info: name,category,currentPrice
            out << item.getName() << ","
                << item.getCategory() << ","
                << item.getCurrentPrice();

            // Write offers: userId:date:amount
            const QList<Offer>& offers = item.getOffers();
            for (const Offer& offer : offers) {
                int userId = std::get<0>(offer);
                QDate date = std::get<1>(offer);
                int amount = std::get<2>(offer);

                out << "," << userId << ":" << date.toString("yyyy-MM-dd") << ":" << amount;
            }

            out << "\n";
        }

        file.close();
        qDebug() << "Successfully saved" << items.size() << "items to" << filename;
        return true;
    }
};

#endif //REPOSITORY_H
