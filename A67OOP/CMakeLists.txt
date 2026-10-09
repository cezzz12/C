cmake_minimum_required(VERSION 3.16)
project(A67OOP)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(Repository)
include_directories(Service)
include_directories(UI)

add_executable(A67OOP
        Domain/Tutorial.cpp
        Domain/Tutorial.h
        Repository/Repo.cpp
        Repository/Repo.h
        Service/Service.cpp
        Service/Service.h
        UI/Ui.cpp
        UI/Ui.h
        main.cpp
        Repository/FileRepo.cpp
        Repository/FileRepo.h
        Repository/Exceptions.cpp
        Repository/Exceptions.h
        Domain/Utils.cpp
        Domain/Utils.h
        Repository/WatchList.cpp
        Repository/WatchList.h
        Domain/TutorialValidator.cpp
        Domain/TutorialValidator.h
        Repository/FileWatchList.cpp
        Repository/FileWatchList.h
        Repository/CSVWatchList.cpp
        Repository/CSVWatchList.h
        Repository/HTMLWatchList.cpp
        Repository/HTMLWatchList.h
)

