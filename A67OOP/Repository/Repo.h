//
// Created by Cezar on 13.05.2025.
//

#ifndef REPO_H
#define REPO_H
#pragma ONCE
#include <vector>
#include "../Domain/Tutorial.h"

class Repo {
protected:
    std::vector<Tutorial> tutorials;
public:
    Repo();
    virtual ~Repo();
    virtual void addRepo(const Tutorial& tutorial);
    virtual void deleteRepo(const Tutorial& tutorial);
    virtual void updateRepo(int position, const Tutorial& tutorial);
    virtual void deleteRepoPosition(int position);
    virtual void writeToFile() {};
    virtual void readFromFile() {};

    std::vector<Tutorial> getAllRepo() const;
    bool validatePosition(int position);
    int getSizeRepo() const;
    int returnPosition(const Tutorial& tutorial) const;
    Tutorial getRepoElement(int position);
    void modifyLikesPosition(int position, int new_likes);

};
#endif //REPO_H
