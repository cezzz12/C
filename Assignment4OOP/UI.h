//
// Created by Cezar on 26.03.2025.
//

#ifndef UI_H
#define UI_H
#pragma once
#include "Service.h"
#include "Tutorial.h"

class UI {
private:
    Service& service;

    void adminMenu();
    void userMenu();
    Tutorial readTutorialInput();
    void printAllTutorials();
    void browseMode();
    void showWatchList();
    void playTutorial(const Tutorial& tutorial);


public:
    UI(Service& serv);
    void run();
};
#endif //UI_H
