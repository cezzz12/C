//
// Created by Cezar on 24.06.2025.
//

#ifndef TABLEVIEWWRITERWINDOW_H
#define TABLEVIEWWRITERWINDOW_H
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include "service.h"
class TableViewWriterWindow : public QMainWindow {
    Q_OBJECT
private:
    Writer writer;
    IdeaService* service;
    QTableWidget* tableWidget;
    QLineEdit* ideaDescriptionEdit;
    QSpinBox* actSpinBox;
    QPushButton* addIdeaButton;
    QPushButton* acceptIdeaButton;
    QPushButton* rejectIdeaButton;
    QLabel* writerInfoLabel;
public:
    explicit TableViewWriterWindow(const Writer& writer, IdeaService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), writer(writer), service(service) {
        setWindowTitle(writer.getName() + " - " + writer.getExpertise());
        setMinimumSize(800, 600);

        setupUI();
        connect(service, &IdeaService::ideasChanged, this, &TableViewWriterWindow::loadIdeas);
    }
private:
  void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // Writer info label
        writerInfoLabel = new QLabel(QString("%1 (%2)").arg(writer.getName(), writer.getExpertise()), this);
        writerInfoLabel->setStyleSheet("font-weight: bold; font-size: 14px; margin: 10px;");
        mainLayout->addWidget(writerInfoLabel);

        // Table widget for ideas
        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(4);
        tableWidget->setHorizontalHeaderLabels({"Description", "Status", "Creator", "Act"});
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setAlternatingRowColors(true);
        mainLayout->addWidget(tableWidget);

        // Add idea section
        QHBoxLayout* addIdeaLayout = new QHBoxLayout();
        ideaDescriptionEdit = new QLineEdit(this);
        ideaDescriptionEdit->setPlaceholderText("Enter idea description...");
        actSpinBox = new QSpinBox(this);
        actSpinBox->setRange(1, 3);
        addIdeaButton = new QPushButton("Add Idea", this);
        connect(addIdeaButton, &QPushButton::clicked, this, &TableViewWriterWindow::onAddIdeaClicked);

        addIdeaLayout->addWidget(new QLabel("Description:", this));
        addIdeaLayout->addWidget(ideaDescriptionEdit);
        addIdeaLayout->addWidget(new QLabel("Act:", this));
        addIdeaLayout->addWidget(actSpinBox);
        addIdeaLayout->addWidget(addIdeaButton);

        mainLayout->addLayout(addIdeaLayout);

        // Revision buttons (only for Senior writers)
        if (writer.getExpertise().toLower() == "senior") {
            QHBoxLayout* revisionLayout = new QHBoxLayout();

            acceptIdeaButton = new QPushButton("Accept Idea", this);
            rejectIdeaButton = new QPushButton("Reject Idea", this);

            acceptIdeaButton->setStyleSheet("background-color: #4CAF50; color: white;");
            rejectIdeaButton->setStyleSheet("background-color: #f44336; color: white;");

            connect(acceptIdeaButton, &QPushButton::clicked, this, &TableViewWriterWindow::onAcceptIdeaClicked);
            connect(rejectIdeaButton, &QPushButton::clicked, this, &TableViewWriterWindow::onRejectIdeaClicked);

            revisionLayout->addWidget(acceptIdeaButton);
            revisionLayout->addWidget(rejectIdeaButton);
            revisionLayout->addStretch(); // Add stretch to push buttons to the left

            mainLayout->addLayout(revisionLayout);
        }

        loadIdeas();
    }

    void loadIdeas() {
        const QList<Idea>& ideas = service->getIdeas();
        tableWidget->setRowCount(ideas.size());

        for (int i = 0; i < ideas.size(); ++i) {
            const Idea& idea = ideas[i];
            tableWidget->setItem(i, 0, new QTableWidgetItem(idea.getDescription()));
            tableWidget->setItem(i, 1, new QTableWidgetItem(idea.getStatus()));
            tableWidget->setItem(i, 2, new QTableWidgetItem(idea.getCreator()));
            tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(idea.getAct())));

            // Color coding for status
            QColor rowColor;
            if (idea.getStatus().toLower() == "accepted") {
                rowColor = QColor(200, 255, 200); // Light green
            } else if (idea.getStatus().toLower() == "rejected") {
                rowColor = QColor(255, 200, 200); // Light red
            } else {
                rowColor = QColor(255, 255, 200); // Light yellow for proposed
            }

            for (int j = 0; j < 4; ++j) {
                tableWidget->item(i, j)->setBackground(rowColor);
            }
        }

        // Resize columns to content
        tableWidget->resizeColumnsToContents();
    }
private slots:
    void onAddIdeaClicked() {
        QString description = ideaDescriptionEdit->text().trimmed();
        int act = actSpinBox->value();

        QString errorMessage;
        if (service->addIdea(description, act, writer.getName(), errorMessage)) {
            ideaDescriptionEdit->clear();
            actSpinBox->setValue(1);
            QMessageBox::information(this, "Success", "Idea added successfully!");
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }

    void onAcceptIdeaClicked() {
        reviseSelectedIdea("accepted");
    }

    void onRejectIdeaClicked() {
        reviseSelectedIdea("rejected");
    }

    void reviseSelectedIdea(const QString& newStatus) {
        int currentRow = tableWidget->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "Error", "Please select an idea to revise.");
            return;
        }

        QString errorMessage;
        if (service->reviseIdea(currentRow, newStatus, writer.getName(), errorMessage)) {
            QMessageBox::information(this, "Success",
                QString("Idea %1 successfully!").arg(newStatus));
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }
};
#endif //TABLEVIEWWRITERWINDOW_H