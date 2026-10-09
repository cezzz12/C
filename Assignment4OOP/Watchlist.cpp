    //
    // Created by Cezar on 05.04.2025.
    //
    #include "Watchlist.h"
    #include <stdexcept>

    void WatchList::addTutorial(const Tutorial& tutorial) {
        if (exists(tutorial)) {
            throw std::runtime_error("Tutorial already in watch list!");
        }
        watchList.add(tutorial);
    }

    void WatchList::removeTutorial(const std::string& title, const std::string& presenter) {
        for (int i = 0; i < watchList.getSize(); ++i) {
            if (watchList[i].getTitle() == title &&
                watchList[i].getPresenter() == presenter) {
                watchList.remove(i);
                return;
                }
        }
        throw std::runtime_error("Tutorial not found in watch list!");
    }

    DynamicArray<Tutorial> WatchList::getAllTutorials() const {
        return watchList;
    }

    bool WatchList::isEmpty() const {
        return watchList.getSize() == 0;
    }

    int WatchList::getSize() const {
        return watchList.getSize();
    }

    bool WatchList::exists(const Tutorial& tutorial) const {
        for (int i = 0; i < watchList.getSize(); ++i) {
            if (watchList[i] == tutorial) {
                return true;
            }
        }
        return false;
    }