//
// Created by Cezar on 24.06.2025.
//

#ifndef IDEALMODEL_H
#define IDEALMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "domain.h"
#include "service.h"
class IdealModel : public QAbstractTableModel {
    Q_OBJECT
private:
  //we will use this model to display ideas in the TableViewWriterWindow ,add ideas, accept them
    IdeaService* service;
    QList<Idea> displayedIdeas;
    QString filterStatus; // Filter by status (e.g., "accepted", "rejected", "proposed")
    bool showOnlyFilteredStatus;
public:
    explicit IdealModel(IdeaService* service, QObject* parent = nullptr)
        : QAbstractTableModel(parent), service(service), showOnlyFilteredStatus(false) {

        connect(service, &IdeaService::ideasChanged, this, &IdealModel::onIdeasChanged);
        updateDisplayedIdeas();
    }

    // QAbstractTableModel interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return displayedIdeas.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return 4; // Description, Status, Creator, Act
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= displayedIdeas.size()) {
            return QVariant();
        }

        const Idea& idea = displayedIdeas[index.row()];

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return idea.getDescription();
                case 1: return idea.getStatus();
                case 2: return idea.getCreator();
                case 3: return idea.getAct();
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "Description";
                    case 1: return "Status";
                    case 2: return "Creator";
                    case 3: return "Act";
                }
            }
        }
        return QVariant();
    }
private slots:
    void onIdeasChanged() {
        updateDisplayedIdeas();
        emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
    }
private:
    void updateDisplayedIdeas() {
        displayedIdeas = service->getIdeas();

        if (showOnlyFilteredStatus && !filterStatus.isEmpty()) {
            displayedIdeas.erase(std::remove_if(displayedIdeas.begin(), displayedIdeas.end(),
                [this](const Idea& idea) { return idea.getStatus().toLower() != filterStatus.toLower(); }),
                displayedIdeas.end());
        }
    }
    };
#endif //IDEALMODEL_H
