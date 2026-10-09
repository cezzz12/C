//
// Created by Cezar on 22.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H

#include <QDate>
#include <QList>
#include <QString>
#include <tuple>

class User {
private:
    QString name;
    int id;
    QString type;
public:
    User(): id(0) {}
    User(const QString &name, int id, const QString &type)
        : name(name), id(id), type(type) {}

    QString getName() const { return name; }
    int getId() const { return id; }
    QString getType() const { return type; }


    void setName(const QString &newName) { this->name = newName; }
    void setId(int newId) { this->id = newId; }
    void setType(const QString &newType) { this->type = newType; }
};

using Offer = std::tuple<int, QDate, int>;
class Item{
private:
    QString name;
    QString category;
    int currentPrice;
    QList<Offer> offers;
public:
    Item() : currentPrice(0) {}
    Item(const QString &name, const QString &category, int currentPrice)
        : name(name), category(category), currentPrice(currentPrice) {}

    QString getName() const { return name; }
    QString getCategory() const { return category; }
    int getCurrentPrice() const { return currentPrice; }
    QList<Offer> getOffers() const { return offers; }


    void setName(const QString &newName) { this->name = newName; }
    void setCategory(const QString &newCategory) { this->category = newCategory; }
    void setCurrentPrice(int newCurrentPrice) { this->currentPrice = newCurrentPrice; }
    void addOffer(const Offer &offer) { this->offers.append(offer); }
    void setOffers(const QList<Offer> &newOffers) { this->offers = newOffers; }

};

#endif //DOMAIN_H