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

public:
    PersonWindow(const Person& person, EventService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), person(person), service(service) {

        setWindowTitle("Person: " + person.getName());
        setMinimumSize(800, 600);

        setupUI();
        populateEvents();

        // Connect to service signals
        connect(service, &EventService::eventsChanged, this, &PersonWindow::onEventsChanged);
    }


private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // Person info label
        personInfoLabel = new QLabel();
        personInfoLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #f0f0f0; border: 1px solid #ccc;");
        updatePersonInfo();
        mainLayout->addWidget(personInfoLabel);

        // Checkbox for filtering near events
        showNearEventsCheckBox = new QCheckBox("Show only events near me (within 5 units)");
        connect(showNearEventsCheckBox, &QCheckBox::toggled, this, &PersonWindow::onShowNearEventsToggled);
        mainLayout->addWidget(showNearEventsCheckBox);

        // Events table
        eventsTable = new QTableWidget(this);
        eventsTable->setColumnCount(5);
        QStringList headers = {"Event Name", "Organizer", "Latitude", "Longitude", "Date"};
        eventsTable->setHorizontalHeaderLabels(headers);

        // Set headers bold
        QFont boldFont = eventsTable->horizontalHeader()->font();
        boldFont.setBold(true);
        eventsTable->horizontalHeader()->setFont(boldFont);

        eventsTable->horizontalHeader()->setStretchLastSection(true);
        eventsTable->setAlternatingRowColors(true);
        eventsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        mainLayout->addWidget(eventsTable);

        // Buttons
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        if (person.getStatus()) { // Only show Add Event button for organizers
            addEventButton = new QPushButton("Add Event");
            addEventButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px 16px; }");
            connect(addEventButton, &QPushButton::clicked, this, &PersonWindow::onAddEventClicked);
            buttonLayout->addWidget(addEventButton);
        }

        buttonLayout->addStretch();
        mainLayout->addLayout(buttonLayout);
    }

    void populateEvents() {
        QList<Event> eventsToShow;
        
        if (showNearEventsCheckBox->isChecked()) {
            eventsToShow = service->getEventsCloseToPerson(person, 5.0);
        } else {
            eventsToShow = service->getEvents();
        }
        
        eventsTable->setRowCount(eventsToShow.size());

        for (int i = 0; i < eventsToShow.size(); ++i) {
            const Event& event = eventsToShow[i];
            
            QTableWidgetItem* nameItem = new QTableWidgetItem(event.getName());
            QTableWidgetItem* organizerItem = new QTableWidgetItem(event.getOrganizer());
            QTableWidgetItem* latitudeItem = new QTableWidgetItem(QString::number(event.getLatitude()));
            QTableWidgetItem* longitudeItem = new QTableWidgetItem(QString::number(event.getLongitude()));
            QTableWidgetItem* dateItem = new QTableWidgetItem(event.getDate().toString("yyyy-MM-dd"));

            // Highlight events organized by this person with green background
            if (person.getStatus() && event.getOrganizer() == person.getName()) {
                nameItem->setBackground(QColor(144, 238, 144)); // Light green
                organizerItem->setBackground(QColor(144, 238, 144));
                latitudeItem->setBackground(QColor(144, 238, 144));
                longitudeItem->setBackground(QColor(144, 238, 144));
                dateItem->setBackground(QColor(144, 238, 144));
            }

            eventsTable->setItem(i, 0, nameItem);
            eventsTable->setItem(i, 1, organizerItem);
            eventsTable->setItem(i, 2, latitudeItem);
            eventsTable->setItem(i, 3, longitudeItem);
            eventsTable->setItem(i, 4, dateItem);
        }

        eventsTable->resizeColumnsToContents();
    }

    void updatePersonInfo() {
        personInfoLabel->setText(
            QString("Name: %1 - Location: (%2, %3) - Organizer: %4")
            .arg(person.getName())
            .arg(person.getLatitude())
            .arg(person.getLongitude())
            .arg(person.getStatus() ? "Yes" : "No")
        );
    }

private slots:
    void onAddEventClicked() {
        AddEventDialog dialog(person.getName(), service, this);
        if (dialog.exec() == QDialog::Accepted) {
            populateEvents();
        }
    }

    void onEventsChanged() {
        populateEvents();
    }

    void onShowNearEventsToggled() {
        populateEvents();
    }
};
#endif