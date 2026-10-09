//
// Created by Cezar on 13.05.2025.
//

#ifndef TUTORIALVALIDATOR_H
#define TUTORIALVALIDATOR_H
#pragma once
#include <iostream>
#include <vector>
class TutorialExceptions : public std::exception
{
private:
    std::vector<std::invalid_argument> errors;

public:
    TutorialExceptions(std::vector<std::invalid_argument> errors);
    TutorialExceptions(std::string error);
    std::vector<std::invalid_argument> returnErrors() const;
};

class TutorialValidator
{
public:
    static void validateTutorialT(const std::string &title);
    static void validateTutorialP(const std::string &presenter);
    static void validateTutorialL(const std::string &link);
    static void validateTutorialNr(int nr);
    static void validateTutorialM(int nr);
    static void validateTutorialS(int nr);
    static void validateTutorial(const std::string &title, const std::string &presenter, const std::string &link, int minutes, int seconds, int likes);
};

#endif //TUTORIALVALIDATOR_H
