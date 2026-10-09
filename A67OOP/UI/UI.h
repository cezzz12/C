//
// Created by Cezar on 13.05.2025.
//

#ifndef UI_H
#define UI_H
#include "../Service/Service.h"

class Ui {
private:
    Service service;
public:
    Ui();
    ~Ui();
    void chooseWLtype();
    void chooseRepoType();
    void printMenu();
    void printMenuAdmin();
    void printMenuUser();
    void addTutorial();
    void deleteTutorial();
    void updateTutorial();
    void printAllTutorials();
    void run();
    void getTutorialByPresenter();
    void seeWatchList();
    void deleteFromWatchList();

};

#endif //UI_H
