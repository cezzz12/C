//
// Created by Cezar on 13.05.2025.
//
#include <string>
#include <iostream>
#ifndef TUTORIAL_H
#define TUTORIAL_H
#pragma once
class Tutorial {
private:
    std::string title,presenter,link;
    int minutes,seconds,likes;
public:
    Tutorial(const std::string &title="",const std::string &presenter="",const std::string &link="", int minutes=0, int seconds=0,
             int likes=0);
    Tutorial(const Tutorial &t);
    ~Tutorial();
    Tutorial& operator=(const Tutorial &t);

    friend std::ostream &operator<<(std::ostream &os, const Tutorial &tutorial);
    friend std::istream &operator>>(std::istream &is, Tutorial &tutorial);

    std::string getTitle() const;
    std::string getPresenter() const;
    std::string getLink() const;
    int getMinutes() const;
    int getSeconds() const;
    int getLikes() const;
    void setTitle(const std::string &title);
    void setPresenter(const std::string &presenter);
    void setLink(const std::string &link);
    void setMinutes(int minutes);
    void setSeconds(int seconds);
    void setLikes(int likes);
    bool operator==(const Tutorial &t) const;
    void validateTitle(const std::string &title);
    void validatePresenter(const std::string &presenter);
    void validateLink(const std::string &link);
    void validateMinutes(int minutes);
    void validateSeconds(int seconds);
    void validateLikes(int likes);
    void validateTutorial();


};

#endif //TUTORIAL_H
