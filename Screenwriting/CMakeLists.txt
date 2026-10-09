cmake_minimum_required(VERSION 3.16)
project(Screenwriting)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(Screenwriting main.cpp
repository.cpp
service.cpp
        IdealModel.cpp
        TableViewMainWindow.cpp
        TableViewWriterWindow.cpp
)
target_link_libraries(Screenwriting
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

