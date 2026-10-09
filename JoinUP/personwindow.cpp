//
// Created by Cezar on 25.06.2025.
//
#include "personwindow.h"

PersonWindow::PersonWindow(const Person& person, EventService* service, QWidget* parent)
    : QMainWindow(parent), person(person), service(service) {
    setWindowTitle("Person: " + person.getName());
    setMinimumSize(600, 400);
    setupUI();
    populateEvents();
    connect(service, &EventService::eventsChanged, this, &PersonWindow::onEventsChanged);
}

void PersonWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    // person label
    personInfoLabel = new QLabel();
    personInfoLabel->setStyleSheet("font-weight: bold; padding: 10px");
    updatePersonInfo();
    mainLayout->addWidget(personInfoLabel);

    //check box for showing near events
    showNearEventsCheckBox = new QCheckBox("Show only events near me (within 5 units)");
    connect(showNearEventsCheckBox, &QCheckBox::toggled, this, &PersonWindow::onShowNearEventsToggled);
    mainLayout->addWidget(showNearEventsCheckBox);
    eventsTable = new QTableWidget(this);
    eventsTable->setColumnCount(5);
    QStringList headers = {"Event Name", "Organizer", "Latitude", "Longitude", "Date"};
    eventsTable->setHorizontalHeaderLabels(headers);
    //bold font + alternating row colors
    QFont boldFont = eventsTable->horizontalHeader()->font();
    boldFont.setBold(true);
    eventsTable->setAlternatingRowColors(true);
    eventsTable->horizontalHeader()->setFont(boldFont);
    eventsTable->horizontalHeader()->setStretchLastSection(true);
    eventsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(eventsTable);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    if (person.getStatus()) {
        addEventButton = new QPushButton("Add Event");
        addEventButton->setStyleSheet("QPushButton { background-color: #4CAF51; color: white; font-weight: bold; padding: 8px 16px; }");
        connect(addEventButton, &QPushButton::clicked, this, &PersonWindow::onAddEventClicked);
        buttonLayout->addWidget(addEventButton);
    }
    //if not organizer, going button that goes to selected event
    else {
        goingButton = new QPushButton("Going");
        goingButton->setStyleSheet("QPushButton { background-color: #FF9800; color: white; font-weight: bold; padding: 8px 16px; }");
        connect(goingButton, &QPushButton::clicked, this, &PersonWindow::onGoingButtonClicked);
        buttonLayout->addWidget(goingButton);
    }
    //when we click on event only if not organizer, we get message box with description of selected event
    if (!person.getStatus()) {
        connect(eventsTable, &QTableWidget::itemSelectionChanged, this, [this]() {
        if (eventsTable->currentRow() >= 0) {
            QTableWidgetItem* item = eventsTable->item(eventsTable->currentRow(), 0);
            if (item) {
                QString eventName = item->text();
                for (const Event& event : service->getEvents()) {
                    if (event.getName() == eventName) {
                        QMessageBox::information(this, "Event Description", event.getDescription());
                        break;
                    }
                }
            }
        }
    });goingButton->setEnabled(true);
    }

    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

void PersonWindow::populateEvents() { //populate the table with events
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

        if (person.getStatus() && event.getOrganizer() == person.getName()) {
            QColor green(144, 238, 144);
            nameItem->setBackground(green);
            organizerItem->setBackground(green);
            latitudeItem->setBackground(green);
            longitudeItem->setBackground(green);
            dateItem->setBackground(green);
        }

        eventsTable->setItem(i, 0, nameItem);
        eventsTable->setItem(i, 1, organizerItem);
        eventsTable->setItem(i, 2, latitudeItem);
        eventsTable->setItem(i, 3, longitudeItem);
        eventsTable->setItem(i, 4, dateItem);
    }

    eventsTable->resizeColumnsToContents();
}

void PersonWindow::updatePersonInfo() {
    personInfoLabel->setText(
        QString("Name: %1 - Location: (%2, %3) - Organizer: %4")
        .arg(person.getName())
        .arg(person.getLatitude())
        .arg(person.getLongitude())
        .arg(person.getStatus() ? "Yes" : "No")
    );
}

void PersonWindow::onAddEventClicked() {
    AddEventDialog dialog(person.getName(), service, this);
    if (dialog.exec() == QDialog::Accepted) {
        populateEvents();
    }
}
void PersonWindow::onGoingButtonClicked() {
    QMessageBox::information(this, "Info", "Going to the selected event");
}
void PersonWindow::onEventsChanged() { //when signal emitted by Event Service we populate table
    populateEvents();
}

void PersonWindow::onShowNearEventsToggled() { // when checkbox activated we populate again
    populateEvents();
}