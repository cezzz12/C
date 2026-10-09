#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>

#include "Service/Service.h"
#include "Domain/TutorialValidator.h"

class GUI : public QMainWindow {
    Q_OBJECT

private:
    Service* service;
    TutorialValidator validator;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;

    QButtonGroup* modeGroup;
    QRadioButton* adminModeRadio;
    QRadioButton* userModeRadio;

    QWidget* adminWidget;
    QTableWidget* tutorialsTable;
    QLineEdit* titleEdit;
    QLineEdit* presenterEdit;
    QLineEdit* linkEdit;
    QSpinBox* minutesSpinBox;
    QSpinBox* secondsSpinBox;
    QSpinBox* likesSpinBox;
    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* deleteButton;
    QPushButton* undoButton;
    QPushButton* redoButton;

    QWidget* userWidget;
    QLineEdit* presenterFilterEdit;
    QTableWidget* filteredTable;
    QLabel* currentTutorialLabel;
    QPushButton* nextButton;
    QPushButton* watchButton;
    QPushButton* addToWatchlistButton;
    QPushButton* likeButton;
    QTableWidget* watchlistTable;

    int selectedRow;
    std::vector<Tutorial> filteredTutorials;
    int currentFilteredIndex;

    void initializeGUI();
    void createModeSelection();
    void createAdminMode();
    void createUserMode();
    void updateTutorialsTable();
    void updateFilteredTable();
    void updateWatchlistTable();
    void clearFields();
    Tutorial getTutorialFromFields();
    void setFieldsFromTutorial(const Tutorial& tutorial);
    void showError(const std::string& message);

private slots:
    void onModeChanged();

    void onAddTutorial();
    void onUpdateTutorial();
    void onDeleteTutorial();
    void onTutorialSelected();
    void onUndo();
    void onRedo();

    void onFilterTutorials();
    void onNextTutorial();
    void onWatchTutorial();
    void onAddToWatchlist();
    void onLikeTutorial();
    void onWatchlistSelected();

public:
    explicit GUI(Service* srv, QWidget* parent = nullptr);
    ~GUI() = default;
};

#endif // GUI_H