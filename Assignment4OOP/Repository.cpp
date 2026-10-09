//
// Created by Cezar on 26.03.2025.
//
#include "Repository.h"
#include <stdexcept>

void Repository::addTutorial(const Tutorial& tutorial) {
    if (tutorialExists(tutorial)) {
        throw std::runtime_error("Tutorial already exists!");
    }
    tutorials.add(tutorial);
}

void Repository::removeTutorial(const std::string& title, const std::string& presenter) {
    for (int i = 0; i < tutorials.getSize(); ++i) {
        if (tutorials[i].getTitle() == title &&
            tutorials[i].getPresenter() == presenter) {
            tutorials.remove(i);
            return;
            }
    }
    throw std::runtime_error("Tutorial not found!");
}

void Repository::updateTutorial(const Tutorial& oldTutorial, const Tutorial& newTutorial) {
    for (int i = 0; i < tutorials.getSize(); ++i) {
        if (tutorials[i] == oldTutorial) {
            tutorials[i] = newTutorial;
            return;
        }
    }
    throw std::runtime_error("Tutorial to update not found!");
}

Tutorial Repository::findTutorial(const std::string& title, const std::string& presenter) const {
    for (int i = 0; i < tutorials.getSize(); ++i) {
        if (tutorials[i].getTitle() == title &&
            tutorials[i].getPresenter() == presenter) {
            return tutorials[i];
            }
    }
    throw std::runtime_error("Tutorial not found!");
}

DynamicArray<Tutorial> Repository::getAllTutorials() const {
    return tutorials;
}

bool Repository::tutorialExists(const Tutorial& tutorial) const {
    for (int i = 0; i < tutorials.getSize(); ++i) {
        if (tutorials[i] == tutorial) {
            return true;
        }
    }
    return false;
}

int Repository::getSize() const {
    return tutorials.getSize();
}
