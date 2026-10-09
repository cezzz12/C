//
// Created by Cezar on 13.05.2025.
//

#ifndef WATCHLIST_H
#define WATCHLIST_H
#pragma once
#include "../Domain/Tutorial.h"
#include "Exceptions.h"

class WatchList {
protected:
    std::vector<Tutorial> tutorials;

public:
    WatchList() {};
    virtual ~WatchList() {}
    void addTutorial(const Tutorial &);
    void removeTutorialFromPlaylist(int);
    bool isEmpty();
    void checkIfTutorialIsAlreadyInTheList(const Tutorial &);
    std::vector<Tutorial> getTutorials() const { return this->tutorials; }
};

#endif //WATCHLIST_H
