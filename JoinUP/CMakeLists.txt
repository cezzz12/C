cmake_minimum_required(VERSION 3.16)
project(JoinUP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(JoinUP main.cpp
        domain.cpp
        domain.h
        repository.cpp
        repository.h
        service.cpp
        service.h
        mainwindow.cpp
        mainwindow.h
        personwindow.cpp
        personwindow.h
        addeventdialog.cpp
        addeventdialog.h
)
target_link_libraries(JoinUP
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

