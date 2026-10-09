//
// Created by Cezar on 13.05.2025.
//

#ifndef FILEREPO_H
#define FILEREPO_H
#pragma once

#include "Repo.h"

class FileRepo: public Repo{
private:
    std::string file_name;
public:
    FileRepo(const std::string &filename);
    virtual ~FileRepo();
    void writeToFile() override;
    void readFromFile() override;
    void addRepo(const Tutorial& tutorial) override;
    void deleteRepo(const Tutorial& tutorial) override;
    void updateRepo(int position, const Tutorial& tutorial) override;
    void deleteRepoPosition(int position) override;



};
#endif //FILEREPO_H
