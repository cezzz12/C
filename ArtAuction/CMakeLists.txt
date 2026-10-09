cmake_minimum_required(VERSION 3.16)
project(ArtAuction)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(ArtAuction
        main.cpp
mainwindow.cpp
service.cpp
repository.cpp
domain.cpp
userwindow.cpp
additemdialog.cpp)
target_link_libraries(ArtAuction
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

