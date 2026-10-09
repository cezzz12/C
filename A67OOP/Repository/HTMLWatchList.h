//
// Created by Cezar on 13.05.2025.
//

#ifndef HTMLWATCHLIST_H
#define HTMLWATCHLIST_H
#pragma once
#include "FileWatchList.h"
#include <fstream>

class HTMLWatchList: public FileWatchList{
public:
    HTMLWatchList(const std::string &fileName) : FileWatchList{fileName} {}
    void writeToFile() const override;
};


#endif //HTMLWATCHLIST_H
