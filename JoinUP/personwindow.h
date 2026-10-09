//
// Created by Cezar on 25.06.2025.
//
#ifndef PERSONWINDOW_H
#define PERSONWINDOW_H
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include "domain.h"
#include "service.h"
#include "addeventdialog.h"

class PersonWindow : public QMainWindow {
    Q_OBJECT
private:
    Person person;
    EventService* service;
    QTableWidget* eventsTable;
    QPushButton* addEventButton;
    QLabel* personInfoLabel;
    QCheckBox* showNearEventsCheckBox;
    QPushButton* goingButton;

public:
    PersonWindow(const Person& person, EventService* service, QWidget* parent = nullptr);

private:
    void setupUI();
    void populateEvents();
    void updatePersonInfo();
private slots:
    void onAddEventClicked();
    void onEventsChanged();
    void onShowNearEventsToggled();
    void onGoingButtonClicked();
};

#endif