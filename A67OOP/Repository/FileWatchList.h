//
// Created by Cezar on 13.05.2025.
//

#ifndef FILEWATCHLIST_H
#define FILEWATCHLIST_H
#pragma once
#include "WatchList.h"

class FileWatchList: public WatchList{
protected:
    std::string filename;
public:
    FileWatchList(const std::string &fileName) : filename{fileName} {}
    virtual void writeToFile() const = 0;
    void openInApp() const;
    virtual ~FileWatchList(){};
};

#endif //FILEWATCHLIST_H
