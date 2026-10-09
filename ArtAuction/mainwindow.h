//
// Created by Cezar on 22.06.2025.
//
#ifndef MAINAPP_H
#define MAINAPP_H

#include <QApplication>
#include <QMessageBox>
#include <QList>
#include "userwindow.h"
#include "service.h"

class MainApplication : public QObject {
    Q_OBJECT

private:
    AuctionService service;
    QList<UserWindow*> userWindows;

public:
    MainApplication(QObject* parent = nullptr) : QObject(parent) {}

    ~MainApplication() {
        service.saveDataExplicitly(); // Save data before exiting
        for (UserWindow* window : userWindows) {
            delete window;
        }
    }

    bool initialize(const QString& usersFile = "users.txt",
                   const QString& itemsFile = "items.txt") {
        if (!service.loadData(usersFile, itemsFile)) {
            QMessageBox::critical(nullptr, "Error",
                "Failed to load data files. Please check that users.txt and items.txt exist.");
            return false;
        }

        // Create windows for each user
        const QList<User>& users = service.getUsers();
        for (const User& user : users) {
            UserWindow* window = new UserWindow(user, &service);
            userWindows.append(window);
            window->show();
        }

        return true;
    }
private slots:
    void onApplicationAboutToQuit() {
        // Save data when application is about to quit
        service.saveDataExplicitly();
    }
};


#endif
