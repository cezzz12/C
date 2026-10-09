#include "GUI.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

GUI::GUI(Service* srv, QWidget* parent) : QMainWindow(parent), service(srv), selectedRow(-1), currentFilteredIndex(-1) {
    initializeGUI();
}

void GUI::initializeGUI() {
    centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    createModeSelection();
    createAdminMode();
    createUserMode();

    adminWidget->hide();
    userWidget->hide();

    setMinimumSize(800, 600);
    setWindowTitle("Tutorial Manager");
}

void GUI::createModeSelection() {
    auto* modeLayout = new QHBoxLayout();
    modeGroup = new QButtonGroup(this);
    adminModeRadio = new QRadioButton("Admin Mode");
    userModeRadio = new QRadioButton("User Mode");

    modeGroup->addButton(adminModeRadio);
    modeGroup->addButton(userModeRadio);
    modeLayout->addWidget(adminModeRadio);
    modeLayout->addWidget(userModeRadio);
    mainLayout->addLayout(modeLayout);

    connect(modeGroup, &QButtonGroup::buttonClicked, this, &GUI::onModeChanged);
}

void GUI::createAdminMode() {
    adminWidget = new QWidget();
    auto* layout = new QVBoxLayout(adminWidget);

    tutorialsTable = new QTableWidget();
    tutorialsTable->setColumnCount(5);
    tutorialsTable->setHorizontalHeaderLabels({"Title", "Presenter", "Link", "Duration", "Likes"});
    layout->addWidget(tutorialsTable);

    auto* formLayout = new QVBoxLayout();
    titleEdit = new QLineEdit();
    presenterEdit = new QLineEdit();
    linkEdit = new QLineEdit();
    minutesSpinBox = new QSpinBox();
    secondsSpinBox = new QSpinBox();
    likesSpinBox = new QSpinBox();

    formLayout->addWidget(new QLabel("Title:"));
    formLayout->addWidget(titleEdit);
    formLayout->addWidget(new QLabel("Presenter:"));
    formLayout->addWidget(presenterEdit);
    formLayout->addWidget(new QLabel("Link:"));
    formLayout->addWidget(linkEdit);
    formLayout->addWidget(new QLabel("Duration (min:sec):"));
    auto* durationLayout = new QHBoxLayout();
    durationLayout->addWidget(minutesSpinBox);
    durationLayout->addWidget(secondsSpinBox);
    formLayout->addLayout(durationLayout);
    formLayout->addWidget(new QLabel("Likes:"));
    formLayout->addWidget(likesSpinBox);

    layout->addLayout(formLayout);

    auto* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add");
    updateButton = new QPushButton("Update");
    deleteButton = new QPushButton("Delete");
    undoButton = new QPushButton("Undo");
    redoButton = new QPushButton("Redo");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);
    layout->addLayout(buttonLayout);

    mainLayout->addWidget(adminWidget);

    connect(tutorialsTable, &QTableWidget::itemSelectionChanged, this, &GUI::onTutorialSelected);
    connect(addButton, &QPushButton::clicked, this, &GUI::onAddTutorial);
    connect(updateButton, &QPushButton::clicked, this, &GUI::onUpdateTutorial);
    connect(deleteButton, &QPushButton::clicked, this, &GUI::onDeleteTutorial);
    connect(undoButton, &QPushButton::clicked, this, &GUI::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &GUI::onRedo);

    updateTutorialsTable();
}

void GUI::createUserMode() {
    userWidget = new QWidget();
    auto* layout = new QVBoxLayout(userWidget);

    auto* filterLayout = new QHBoxLayout();
    presenterFilterEdit = new QLineEdit();
    auto* filterButton = new QPushButton("Filter");
    filterLayout->addWidget(new QLabel("Presenter:"));
    filterLayout->addWidget(presenterFilterEdit);
    filterLayout->addWidget(filterButton);
    layout->addLayout(filterLayout);

    filteredTable = new QTableWidget();
    filteredTable->setColumnCount(5);
    filteredTable->setHorizontalHeaderLabels({"Title", "Presenter", "Link", "Duration", "Likes"});
    layout->addWidget(filteredTable);

    currentTutorialLabel = new QLabel();
    layout->addWidget(currentTutorialLabel);

    auto* buttonLayout = new QHBoxLayout();
    watchButton = new QPushButton("Watch");
    nextButton = new QPushButton("Next");
    addToWatchlistButton = new QPushButton("Add to Watchlist");
    likeButton = new QPushButton("Like");

    buttonLayout->addWidget(watchButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->addWidget(addToWatchlistButton);
    buttonLayout->addWidget(likeButton);
    layout->addLayout(buttonLayout);

    watchlistTable = new QTableWidget();
    watchlistTable->setColumnCount(5);
    watchlistTable->setHorizontalHeaderLabels({"Title", "Presenter", "Link", "Duration", "Likes"});
    layout->addWidget(watchlistTable);

    mainLayout->addWidget(userWidget);

    connect(filterButton, &QPushButton::clicked, this, &GUI::onFilterTutorials);
    connect(nextButton, &QPushButton::clicked, this, &GUI::onNextTutorial);
    connect(watchButton, &QPushButton::clicked, this, &GUI::onWatchTutorial);
    connect(addToWatchlistButton, &QPushButton::clicked, this, &GUI::onAddToWatchlist);
    connect(likeButton, &QPushButton::clicked, this, &GUI::onLikeTutorial);
    connect(watchlistTable, &QTableWidget::itemSelectionChanged, this, &GUI::onWatchlistSelected);
}

void GUI::onModeChanged() {
    if (adminModeRadio->isChecked()) {
        service->setAdminMode(1);
        adminWidget->show();
        userWidget->hide();
        updateTutorialsTable();
    } else {
        service->setAdminMode(0);
        adminWidget->hide();
        userWidget->show();
        onFilterTutorials();
        updateWatchlistTable();
    }
}

void GUI::onAddTutorial() {
    try {
        Tutorial tutorial = getTutorialFromFields();
        service->addService(tutorial);
        updateTutorialsTable();
        clearFields();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onUpdateTutorial() {
    if (selectedRow < 0) return;

    try {
        Tutorial tutorial = getTutorialFromFields();
        service->updateService(selectedRow, tutorial);
        updateTutorialsTable();
        clearFields();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onDeleteTutorial() {
    try {
        Tutorial tutorial = getTutorialFromFields();
        service->deleteService(tutorial);
        updateTutorialsTable();
        clearFields();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onFilterTutorials() {
    QString presenter = presenterFilterEdit->text();
    filteredTutorials = service->getTutorialsByPresenter(presenter.toStdString());
    currentFilteredIndex = 0;
    updateFilteredTable();

    if (!filteredTutorials.empty()) {
        Tutorial current = filteredTutorials[0];
        currentTutorialLabel->setText(QString::fromStdString(
            "Current: " + current.getTitle() + " by " + current.getPresenter()));
    } else {
        currentTutorialLabel->setText("No tutorials found");
        currentFilteredIndex = -1;
    }
}

void GUI::onNextTutorial() {
    if (filteredTutorials.empty()) return;

    currentFilteredIndex++;
    if (currentFilteredIndex >= filteredTutorials.size()) {
        currentFilteredIndex = 0;
    }

    Tutorial current = filteredTutorials[currentFilteredIndex];
    currentTutorialLabel->setText(QString::fromStdString(
        "Current: " + current.getTitle() + " by " + current.getPresenter()));
}

void GUI::onWatchTutorial() {
    if (filteredTutorials.empty()) return;

    if (currentFilteredIndex >= 0 && currentFilteredIndex < filteredTutorials.size()) {
        Tutorial current = filteredTutorials[currentFilteredIndex];
        QDesktopServices::openUrl(QUrl(QString::fromStdString(current.getLink())));
    }
}

void GUI::onAddToWatchlist() {
    if (filteredTutorials.empty()) return;

    try {
        Tutorial current = filteredTutorials[currentFilteredIndex];
        service->addToWatchList(current);
        updateWatchlistTable();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onLikeTutorial() {
    if (filteredTutorials.empty()) return;

    try {
        Tutorial current = filteredTutorials[currentFilteredIndex];
        service->increaseLikesTutorial(current);
        updateFilteredTable();
        updateTutorialsTable();

        currentTutorialLabel->setText(QString::fromStdString(
            "Current: " + current.getTitle() + " by " + current.getPresenter()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onWatchlistSelected() {
    auto selected = watchlistTable->selectedItems();
    if (selected.isEmpty()) return;

    int row = selected[0]->row();
    try {
        service->removeWatchList(row);
        updateWatchlistTable();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onTutorialSelected() {
    auto selected = tutorialsTable->selectedItems();
    if (selected.isEmpty()) {
        selectedRow = -1;
        return;
    }

    selectedRow = selected[0]->row();
    Tutorial tutorial = service->getServiceElement(selectedRow);
    setFieldsFromTutorial(tutorial);
}

void GUI::updateTutorialsTable() {
    tutorialsTable->setRowCount(0);
    for (const auto& tutorial : service->getAllService()) {
        int row = tutorialsTable->rowCount();
        tutorialsTable->insertRow(row);
        tutorialsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(tutorial.getTitle())));
        tutorialsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tutorial.getPresenter())));
        tutorialsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tutorial.getLink())));
        tutorialsTable->setItem(row, 3, new QTableWidgetItem(QString::number(tutorial.getMinutes()) + ":" + QString::number(tutorial.getSeconds())));
        tutorialsTable->setItem(row, 4, new QTableWidgetItem(QString::number(tutorial.getLikes())));
    }
}

void GUI::updateFilteredTable() {
    filteredTable->setRowCount(0);
    for (const auto& tutorial : filteredTutorials) {
        int row = filteredTable->rowCount();
        filteredTable->insertRow(row);
        filteredTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(tutorial.getTitle())));
        filteredTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tutorial.getPresenter())));
        filteredTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tutorial.getLink())));
        filteredTable->setItem(row, 3, new QTableWidgetItem(QString::number(tutorial.getMinutes()) + ":" + QString::number(tutorial.getSeconds())));
        filteredTable->setItem(row, 4, new QTableWidgetItem(QString::number(tutorial.getLikes())));
    }
}

void GUI::updateWatchlistTable() {
    watchlistTable->setRowCount(0);
    for (const auto& tutorial : service->getWatchList()) {
        int row = watchlistTable->rowCount();
        watchlistTable->insertRow(row);
        watchlistTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(tutorial.getTitle())));
        watchlistTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tutorial.getPresenter())));
        watchlistTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tutorial.getLink())));
        watchlistTable->setItem(row, 3, new QTableWidgetItem(QString::number(tutorial.getMinutes()) + ":" + QString::number(tutorial.getSeconds())));
        watchlistTable->setItem(row, 4, new QTableWidgetItem(QString::number(tutorial.getLikes())));
    }
}

Tutorial GUI::getTutorialFromFields() {
    std::string title = titleEdit->text().toStdString();
    std::string presenter = presenterEdit->text().toStdString();
    std::string link = linkEdit->text().toStdString();
    int minutes = minutesSpinBox->value();
    int seconds = secondsSpinBox->value();
    int likes = likesSpinBox->value();

    return Tutorial(title, presenter, link, minutes, seconds, likes);
}

void GUI::clearFields() {
    titleEdit->clear();
    presenterEdit->clear();
    linkEdit->clear();
    minutesSpinBox->setValue(0);
    secondsSpinBox->setValue(0);
    likesSpinBox->setValue(0);
    selectedRow = -1;
}

void GUI::setFieldsFromTutorial(const Tutorial& tutorial) {
    titleEdit->setText(QString::fromStdString(tutorial.getTitle()));
    presenterEdit->setText(QString::fromStdString(tutorial.getPresenter()));
    linkEdit->setText(QString::fromStdString(tutorial.getLink()));
    minutesSpinBox->setValue(tutorial.getMinutes());
    secondsSpinBox->setValue(tutorial.getSeconds());
    likesSpinBox->setValue(tutorial.getLikes());
}

void GUI::onUndo() {
    try {
        service->undo();
        updateTutorialsTable();
        clearFields();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::onRedo() {
    try {
        service->redo();
        updateTutorialsTable();
        clearFields();
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void GUI::showError(const std::string& message) {
    QMessageBox::critical(this, "Error", QString::fromStdString(message));
}