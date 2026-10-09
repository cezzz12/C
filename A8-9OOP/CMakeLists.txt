cmake_minimum_required(VERSION 3.16)
project(A8_9OOP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(A8_9OOP main.cpp
        Domain/Tutorial.cpp
        Domain/Tutorial.h
        Domain/TutorialValidator.cpp
        Domain/TutorialValidator.h
        Domain/Utils.cpp
        Domain/Utils.h
        Repository/CSVWatchList.cpp
        Repository/CSVWatchList.h
        Repository/Exceptions.cpp
        Repository/Exceptions.h
        Repository/FileRepo.cpp
        Repository/FileRepo.h
        Repository/FileWatchList.cpp
        Repository/FileWatchList.h
        Repository/HTMLWatchList.cpp
        Repository/HTMLWatchList.h
        Repository/Repo.cpp
        Repository/Repo.h
        Repository/WatchList.cpp
        Repository/WatchList.h
        Service/Service.cpp
        Service/Service.h
        Service/Action.h
        Service/Action.cpp
        GUI.cpp
        GUI.h
)
target_link_libraries(A8_9OOP
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

