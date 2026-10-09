//
// Created by Cezar on 26.03.2025.
//

#include "Service.h"
#include <stdexcept>
#include <algorithm>

Service::Service(Repository& repo) : repository(repo) {}

void Service::addTutorial(const std::string& title, const std::string& presenter,
                           int minutes, int seconds, int likes, const std::string& link) {
    if (!validateTutorial(title, presenter, minutes, seconds, likes, link)) {
        throw std::invalid_argument("Invalid tutorial data!");
    }

    Tutorial newTutorial(title, presenter, minutes, seconds, likes, link);
    repository.addTutorial(newTutorial);
}

void Service::removeTutorial(const std::string& title, const std::string& presenter) {
    repository.removeTutorial(title, presenter);
}

void Service::updateTutorial(const std::string& oldTitle, const std::string& oldPresenter,
                              const std::string& newTitle, const std::string& newPresenter,
                              int newMinutes, int newSeconds, int newLikes, const std::string& newLink) {
    if (!validateTutorial(newTitle, newPresenter, newMinutes, newSeconds, newLikes, newLink)) {
        throw std::invalid_argument("Invalid tutorial data!");
    }

    Tutorial oldTutorial = repository.findTutorial(oldTitle, oldPresenter);
    Tutorial newTutorial(newTitle, newPresenter, newMinutes, newSeconds, newLikes, newLink);

    repository.updateTutorial(oldTutorial, newTutorial);
}

DynamicArray<Tutorial> Service::getAllTutorials() const {
    return repository.getAllTutorials();
}

bool Service::validateTutorial(const std::string& title, const std::string& presenter,
                                int minutes, int seconds, int likes, const std::string& link) const {
    if (title.empty() || presenter.empty()) return false;
    if (minutes < 0 || seconds < 0 || seconds >= 60) return false;
    if (likes < 0) return false;
    if (link.empty() || link.find("http") == std::string::npos) return false;

    return true;
}
DynamicArray<Tutorial> Service::filterTutorialsByPresenter(const std::string& presenter) const {
    if (presenter.empty()) {
        return repository.getAllTutorials();
    }

    DynamicArray<Tutorial> filteredTutorials;
    DynamicArray<Tutorial> allTutorials = repository.getAllTutorials();

    for (int i = 0; i < allTutorials.getSize(); ++i) {
        if (allTutorials[i].getPresenter() == presenter) {
            filteredTutorials.add(allTutorials[i]);
        }
    }

    return filteredTutorials;
}

void Service::addToWatchList(const Tutorial& tutorial) {
    watchList.addTutorial(tutorial);
}

void Service::removeFromWatchList(const std::string& title, const std::string& presenter, bool like) {
    if (like) {
        likeTutorial(title, presenter);
    }
    watchList.removeTutorial(title, presenter);
}

DynamicArray<Tutorial> Service::getWatchList() const {
    return watchList.getAllTutorials();
}

void Service::likeTutorial(const std::string& title, const std::string& presenter) {
    Tutorial tutorial = repository.findTutorial(title, presenter);
    Tutorial updatedTutorial = tutorial;
    updatedTutorial.setLikes(tutorial.getLikes() + 1);
    repository.updateTutorial(tutorial, updatedTutorial);
}