cmake_minimum_required(VERSION 3.16)
project(CodeRevision)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(CodeRevision
        main.cpp
    mainwindow.cpp
    service.cpp
    repository.cpp
        domain.cpp
        programmerwindow.cpp
        addfiledialog.cpp
)
target_link_libraries(CodeRevision
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

