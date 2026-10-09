//
// Created by Cezar on 13.05.2025.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#pragma once
#include <exception>
#include <string>
#include <vector>

class FileException : public std::exception
{
private:
    std::string message;

public:
    FileException(const std::string &message);
    virtual const char *what();
};

class RepositoryException : public std::exception
{
protected:
    std::string message;

public:
    RepositoryException();
    RepositoryException(const std::string &message);
    virtual ~RepositoryException(){};
    virtual const char *what();
};

class DuplicateTutException : public RepositoryException
{
public:
    const char *what();
};

class InvalidPositionException : public RepositoryException
{
public:
    const char *what();
};

#endif //EXCEPTIONS_H
