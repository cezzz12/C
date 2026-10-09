//
// Created by Cezar on 13.05.2025.
//

#include "FileWatchList.h"

void FileWatchList::openInApp() const {
    this->writeToFile();
    std::string cmd = "open " + this->filename;
    system(cmd.c_str());
}
