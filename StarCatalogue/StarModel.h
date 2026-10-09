//
// Created by Cezar on 24.06.2025.
//

//
// Created by Cezar on 24.06.2025.
//

#ifndef STARMODEL_H
#define STARMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "domain.h"
#include "service.h"

class StarModel : public QAbstractTableModel {
    Q_OBJECT

private:
    StarService* service;
    QList<Star> displayedStars;
    QString constellationFilter;
    bool showOnlyConstellation;

public:
    explicit StarModel(StarService* service, QObject* parent = nullptr)
        : QAbstractTableModel(parent), service(service), showOnlyConstellation(false) {

        connect(service, &StarService::starsChanged, this, &StarModel::onStarsChanged);
        updateDisplayedStars();
    }

    // QAbstractTableModel interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return displayedStars.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return 5; // Name, Constellation, RA, DEC, Diameter
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= displayedStars.size()) {
            return QVariant();
        }

        const Star& star = displayedStars[index.row()];

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return star.getName();
                case 1: return star.getConstellation();
                case 2: return star.getRA();
                case 3: return star.getDEC();
                case 4: return star.getDiameter();
            }
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            switch (section) {
                case 0: return "Name";
                case 1: return "Constellation";
                case 2: return "RA";
                case 3: return "DEC";
                case 4: return "Diameter";
            }
        }
        return QVariant();
    }

    // Custom methods
    void setConstellationFilter(const QString& constellation, bool showOnly) {
        constellationFilter = constellation;
        showOnlyConstellation = showOnly;
        updateDisplayedStars();
    }

    void refreshData() {
        updateDisplayedStars();
    }

private slots:
    void onStarsChanged() {
        updateDisplayedStars();
    }

private:
    void updateDisplayedStars() {
        beginResetModel();

        if (showOnlyConstellation && !constellationFilter.isEmpty()) {
            displayedStars = service->filterStarsByConstellation(constellationFilter);
        } else {
            displayedStars = service->getStars();
        }

        endResetModel();
    }
};

#endif // STARMODEL_H