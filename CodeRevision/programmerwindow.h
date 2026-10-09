#ifndef PROGRAMMERWINDOW_H
#define PROGRAMMERWINDOW_H
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QBrush>
#include <QColor>
#include "domain.h"
#include "service.h"
#include "addfiledialog.h"

class ProgrammerWindow : public QMainWindow {
    Q_OBJECT
private:
    Programmer programmer;
    FileService* service;
    QTableWidget* sourceFilesTable;
    QLabel* programmerInfoLabel;
    QPushButton* addFileButton;
    QPushButton* reviseButton;

public:
    ProgrammerWindow(const Programmer& programmer, FileService* service, QWidget* parent = nullptr)
        : QMainWindow(parent), programmer(programmer), service(service) {

        setWindowTitle("Programmer: " + programmer.getName());
        setMinimumSize(900, 700);

        setupUI();
        populateSourceFiles();
        
        // Connect to service signals
        connect(service, &FileService::filesChanged, this, &ProgrammerWindow::onFilesChanged);
    }

private slots:
    void onAddFileClicked() {
        AddFileDialog dialog(programmer.getName(), service, this);
        dialog.exec();
    }
    
    void onReviseClicked() {
        int currentRow = sourceFilesTable->currentRow();
        if (currentRow < 0) {
            QMessageBox::information(this, "Info", "Please select a file to revise.");
            return;
        }
        
        QString fileName = sourceFilesTable->item(currentRow, 0)->text();
        QString errorMessage;
        
        if (service->reviseFile(fileName, programmer.getName(), errorMessage)) {
            // Check if programmer has completed all required revisions
            Programmer* updatedProgrammer = service->findProgrammer(programmer.getName());
            if (updatedProgrammer && updatedProgrammer->getRemainingFiles() == 0) {
                QMessageBox::information(this, "Congratulations!", 
                    "Congratulations! You have completed all your file revisions!");
            }
        } else {
            QMessageBox::warning(this, "Error", errorMessage);
        }
    }
    
    void onSelectionChanged() {
        updateReviseButton();
    }
    
    void onFilesChanged() {
        // Update programmer info
        Programmer* updatedProgrammer = service->findProgrammer(programmer.getName());
        if (updatedProgrammer) {
            programmer = *updatedProgrammer;
        }
        
        populateSourceFiles();
        updateProgrammerInfo();
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        
        // Programmer info label
        programmerInfoLabel = new QLabel();
        programmerInfoLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #f0f0f0; border: 1px solid #ccc;");
        updateProgrammerInfo();
        mainLayout->addWidget(programmerInfoLabel);
        
        // Source files table
        sourceFilesTable = new QTableWidget(this);
        sourceFilesTable->setColumnCount(4);
        QStringList headers = {"File Name", "Status", "Creator", "Reviewer"};
        sourceFilesTable->setHorizontalHeaderLabels(headers);
        
        // Set headers bold
        QFont boldFont = sourceFilesTable->horizontalHeader()->font();
        boldFont.setBold(true);
        sourceFilesTable->horizontalHeader()->setFont(boldFont);
        
        sourceFilesTable->horizontalHeader()->setStretchLastSection(true);
        sourceFilesTable->setAlternatingRowColors(true);
        sourceFilesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        
        connect(sourceFilesTable, &QTableWidget::itemSelectionChanged, 
                this, &ProgrammerWindow::onSelectionChanged);
        
        mainLayout->addWidget(sourceFilesTable);
        
        // Buttons
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        
        addFileButton = new QPushButton("Add File");
        addFileButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px 16px; }");
        connect(addFileButton, &QPushButton::clicked, this, &ProgrammerWindow::onAddFileClicked);
        
        reviseButton = new QPushButton("Revise");
        reviseButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; font-weight: bold; padding: 8px 16px; }");
        reviseButton->setEnabled(false);
        connect(reviseButton, &QPushButton::clicked, this, &ProgrammerWindow::onReviseClicked);
        
        buttonLayout->addWidget(addFileButton);
        buttonLayout->addWidget(reviseButton);
        buttonLayout->addStretch();
        
        mainLayout->addLayout(buttonLayout);
    }
    
    void updateProgrammerInfo() {
        programmerInfoLabel->setText(
            QString("Programmer: %1 - Revised Files: %2 - Remaining Files: %3")
            .arg(programmer.getName())
            .arg(programmer.getRevisedFiles())
            .arg(programmer.getRemainingFiles())
        );
    }
    
    void populateSourceFiles() {
        const QList<SourceFile>& files = service->getSourceFiles();
        sourceFilesTable->setRowCount(files.size());
        
        for (int i = 0; i < files.size(); ++i) {
            const SourceFile& file = files[i];
            QTableWidgetItem* nameItem = new QTableWidgetItem(file.getName());
            QTableWidgetItem* statusItem = new QTableWidgetItem(file.getStatus());
            QTableWidgetItem* creatorItem = new QTableWidgetItem(file.getCreator());
            QTableWidgetItem* reviewerItem = new QTableWidgetItem(file.getReviewer());
            
            // Style based on status
            if (file.getStatus() == "not revised") {
                // Make unrevised files bold
                QFont boldFont;
                boldFont.setBold(true);
                nameItem->setFont(boldFont);
                statusItem->setFont(boldFont);
                creatorItem->setFont(boldFont);
                reviewerItem->setFont(boldFont);
            } else if (file.getStatus() == "revised") {
                // Make revised files have green background
                QBrush greenBrush(QColor(200, 255, 200));
                nameItem->setBackground(greenBrush);
                statusItem->setBackground(greenBrush);
                creatorItem->setBackground(greenBrush);
                reviewerItem->setBackground(greenBrush);
            }
            
            sourceFilesTable->setItem(i, 0, nameItem);
            sourceFilesTable->setItem(i, 1, statusItem);
            sourceFilesTable->setItem(i, 2, creatorItem);
            sourceFilesTable->setItem(i, 3, reviewerItem);
        }
        
        sourceFilesTable->resizeColumnsToContents();
        updateReviseButton();
    }
    
    void updateReviseButton() {
        int currentRow = sourceFilesTable->currentRow();
        bool canRevise = false;
        
        if (currentRow >= 0) {
            QString status = sourceFilesTable->item(currentRow, 1)->text();
            QString creator = sourceFilesTable->item(currentRow, 2)->text();
            
            canRevise = (status == "not revised") && (creator != programmer.getName());
        }
        
        reviseButton->setEnabled(canRevise);
    }
};
#endif
