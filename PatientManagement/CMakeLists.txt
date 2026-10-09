cmake_minimum_required(VERSION 3.16)
project(PatientManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(PatientManagement main.cpp
service.cpp
domain.cpp
repository.cpp
mainwindow.cpp
addpatientdialog.cpp
doctorwindow.cpp

)
target_link_libraries(PatientManagement
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

