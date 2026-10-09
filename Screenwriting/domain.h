//
// Created by Cezar on 24.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <QString>
#include <QList>
#include <QDebug>
class Writer{
  private:
    QString name;
    QString expertise;
  public:
    Writer(const QString &name, const QString &expertise)
        : name(name), expertise(expertise) {}

    QString getName() const { return name; }
    QString getExpertise() const { return expertise; }

    void setName(const QString &newName) { name = newName; }
    void setExpertise(const QString &newExpertise) { expertise = newExpertise; }


};
class Idea{
private:
    QString description;
    QString status; //accepted or rejected
    QString creator; //name of the writer
    int act;
public:
    Idea():  act(0) {}
    Idea(const QString &description, const QString &status, const QString &creator, int act)
        : description(description), status(status), creator(creator), act(act) {}

    QString getDescription() const { return description; }
    QString getStatus() const { return status; }
    QString getCreator() const { return creator; }
    int getAct() const { return act; }

    void setDescription(const QString &newDescription) { description = newDescription; }
    void setStatus(const QString &newStatus) { status = newStatus; }
    void setCreator(const QString &newCreator) { creator = newCreator; }
    void setAct(int newAct) { act = newAct; }
};
#endif //DOMAIN_H
