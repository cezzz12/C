//
// Created by Cezar on 13.05.2025.
//

#include "FileRepo.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string &filename): file_name{filename}{

}

FileRepo::~FileRepo() {
    this->writeToFile();
}

void FileRepo::writeToFile() {
    std::ofstream file(this->file_name);
    if(!file.is_open())
        throw FileException("The file could not be opened!");
    for(auto &tutorial: this->tutorials)
        file << tutorial<<'\n';
    file.close();
}

void FileRepo::readFromFile() {
    std::ifstream fin(this->file_name);
    if (!fin.is_open()) {
        throw FileException("The file could not be opened!");
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string title, presenter, link;
        int minutes, seconds, likes;

        std::getline(ss, title, ',');
        std::getline(ss, presenter, ',');
        std::getline(ss, link, ',');
        ss >> minutes;
        ss.ignore();
        ss >> seconds;
        ss.ignore();
        ss >> likes;

        Tutorial t(title, presenter, link, minutes, seconds, likes);
        this->tutorials.push_back(t);
    }
    fin.close();
}

void FileRepo::addRepo(const Tutorial &tutorial) {
    Repo::addRepo(tutorial);
    this->writeToFile();
}

void FileRepo::deleteRepo(const Tutorial &tutorial) {
    Repo::deleteRepo(tutorial);
    this->writeToFile();
}

void FileRepo::updateRepo(int position, const Tutorial &tutorial) {
    Repo::updateRepo(position, tutorial);
    this->writeToFile();
}

void FileRepo::deleteRepoPosition(int position) {
    Repo::deleteRepoPosition(position);
    this->writeToFile();
}
