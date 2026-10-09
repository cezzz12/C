//
// Created by Cezar on 05.04.2025.
//
#ifndef WATCHLIST_H
#define WATCHLIST_H
#pragma once
#include "DynamicArray.h"
#include "Tutorial.h"

class WatchList {
private:
    DynamicArray<Tutorial> watchList;

public:
    void addTutorial(const Tutorial& tutorial);
    void removeTutorial(const std::string& title, const std::string& presenter);
    DynamicArray<Tutorial> getAllTutorials() const;
    bool isEmpty() const;
    int getSize() const;
    bool exists(const Tutorial& tutorial) const;
};

#endif //WATCHLIST_H
