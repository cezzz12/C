//
// Created by Cezar on 26.03.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#pragma once
#include "DynamicArray.h"
#include "Tutorial.h"

class Repository {
private:
    DynamicArray<Tutorial> tutorials;

public:
    void addTutorial(const Tutorial& tutorial);
    void removeTutorial(const std::string& title, const std::string& presenter);
    void updateTutorial(const Tutorial& oldTutorial, const Tutorial& newTutorial);

    Tutorial findTutorial(const std::string& title, const std::string& presenter) const;
    DynamicArray<Tutorial> getAllTutorials() const;

    bool tutorialExists(const Tutorial& tutorial) const;
    int getSize() const;
};
#endif //REPOSITORY_H
