//
// Created by Cezar on 13.05.2025.
//

#ifndef CSVWATCHLIST_H
#define CSVWATCHLIST_H
#pragma once
#include "FileWatchList.h"
#include <fstream>

class CSVWatchList: public FileWatchList{
public:
    CSVWatchList(const std::string &fileName) : FileWatchList{fileName} {}
    void writeToFile() const override;
};
#endif //CSVWATCHLIST_H
