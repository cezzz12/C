//
// Created by Cezar on 26.03.2025.
//

#include "Tutorial.h"
#include <sstream>

Tutorial::Tutorial() : minutes(0), seconds(0), likes(0) {}

Tutorial::Tutorial(const std::string& title, const std::string& presenter,
                   int minutes, int seconds, int likes, const std::string& link)
    : title(title), presenter(presenter),
      minutes(minutes), seconds(seconds),
      likes(likes), link(link) {}

std::string Tutorial::getTitle() const { return title; }
std::string Tutorial::getPresenter() const { return presenter; }
int Tutorial::getMinutes() const { return minutes; }
int Tutorial::getSeconds() const { return seconds; }
int Tutorial::getLikes() const { return likes; }
std::string Tutorial::getLink() const { return link; }

void Tutorial::setTitle(const std::string& newTitle) { title = newTitle; }
void Tutorial::setPresenter(const std::string& newPresenter) { presenter = newPresenter; }
void Tutorial::setDuration(int newMinutes, int newSeconds) {
    minutes = newMinutes;
    seconds = newSeconds;
}
void Tutorial::setLikes(int newLikes) { likes = newLikes; }
void Tutorial::setLink(const std::string& newLink) { link = newLink; }

bool Tutorial::operator==(const Tutorial& other) const {
    return (title == other.title) && (presenter == other.presenter);
}

bool Tutorial::operator!=(const Tutorial& other) const {
    return !(*this == other);
}

std::string Tutorial::toString() const {
    std::stringstream ss;
    ss << "Tutorial: " << title
       << " | Presenter: " << presenter
       << " | Duration: " << minutes << "m " << seconds << "s"
       << " | Likes: " << likes
       << " | Link: " << link;
    return ss.str();
}
