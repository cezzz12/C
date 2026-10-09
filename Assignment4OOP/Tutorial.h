//
// Created by Cezar on 26.03.2025.
//

#ifndef TUTORIAL_H
#define TUTORIAL_H
#pragma once
#include <string>

class Tutorial {
private:
    std::string title;
    std::string presenter;
    int minutes;
    int seconds;
    int likes;
    std::string link;

public:
    Tutorial();
    Tutorial(const std::string& title, const std::string& presenter,
             int minutes, int seconds, int likes, const std::string& link);

    std::string getTitle() const;
    std::string getPresenter() const;
    int getMinutes() const;
    int getSeconds() const;
    int getLikes() const;
    std::string getLink() const;

    void setTitle(const std::string& title);
    void setPresenter(const std::string& presenter);
    void setDuration(int minutes, int seconds);
    void setLikes(int likes);
    void setLink(const std::string& link);

    bool operator==(const Tutorial& other) const;
    bool operator!=(const Tutorial& other) const;

    std::string toString() const;
};
#endif //TUTORIAL_H
