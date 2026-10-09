//
// Created by Cezar on 13.05.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#pragma once
#include "../Repository/Repo.h"
#include "../Repository/FileWatchList.h"
#include "../Domain/TutorialValidator.h"
#include <fstream>


class Service {
private:
    Repo* repository;
    int adminMode;
    std::vector<int> indexesOfLikedTutorials;
    FileWatchList* watchList;
public:
    Service();
    ~Service();
    int getAdminMode() const;
    void generateTutorials();
    void addService(Tutorial tutorial);
    void deleteService(Tutorial tutorial);
    void updateService(int position, Tutorial tutorial);
    void deleteServicePosition(int position);
    std::vector<Tutorial> getAllService() const;
    int getSizeService() const;
    int returnPositionService(const Tutorial& tutorial);
    Tutorial getServiceElement(int position);
    void setAdminMode(int mode);

    std::vector<int> getPositionsTutByPresenter(const std::string &presenter);
    std::vector<Tutorial> getTutorialsByPresenter(const std::string &presenter);
    std::vector<int> getIndexesOfLikedTutorials();
    void openTutorialInBrowser(int position);
    void addToWatchList(Tutorial tut);
    void removeWatchList(int pos);
    void increaseLikesTutorial(Tutorial &t);
    std::vector <Tutorial> getWatchList();

    void setTypeOfRepo(Repo* r);
    void setTypeOfWatchList(FileWatchList* w);
    void displaylist();
    void checkIfTutorialIsAlreadyInTheList(const Tutorial &);
    void clearFile(const std::string &);
};

#endif //SERVICE_H
