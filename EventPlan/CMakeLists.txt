cmake_minimum_required(VERSION 3.16)
project(EventPlan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(EventPlan main.cpp
domain.cpp
        repository.cpp
        service.cpp
        mainwindow.cpp
        addeventdialog.cpp
        personwindow.cpp
)
target_link_libraries(EventPlan
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

