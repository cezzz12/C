#ifndef SERVICE_H
#define SERVICE_H
#pragma once

#include "Repository.h"
#include "Tutorial.h"
#include "DynamicArray.h"
#include "Watchlist.h"


class Service {
private:
    Repository& repository;
    WatchList watchList;

public:
    Service(Repository& repo);

    void addTutorial(const std::string& title, const std::string& presenter,
                     int minutes, int seconds, int likes, const std::string& link);
    void removeTutorial(const std::string& title, const std::string& presenter);
    void updateTutorial(const std::string& oldTitle, const std::string& oldPresenter,
                        const std::string& newTitle, const std::string& newPresenter,
                        int newMinutes, int newSeconds, int newLikes, const std::string& newLink);

    DynamicArray<Tutorial> getAllTutorials() const;
    DynamicArray<Tutorial> filterTutorialsByPresenter(const std::string& presenter) const;
    void addToWatchList(const Tutorial& tutorial);
    void removeFromWatchList(const std::string& title, const std::string& presenter, bool like);
    DynamicArray<Tutorial> getWatchList() const;
    void likeTutorial(const std::string& title, const std::string& presenter);

private:
    bool validateTutorial(const std::string& title, const std::string& presenter,
                           int minutes, int seconds, int likes, const std::string& link) const;
};

#endif //SERVICE_H