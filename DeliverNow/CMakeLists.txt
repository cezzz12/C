cmake_minimum_required(VERSION 3.16)
project(DeliverNow)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(DeliverNow main.cpp
domain.cpp
repository.cpp
service.cpp
mainwindow.cpp
        courierwindow.cpp
)
target_link_libraries(DeliverNow
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

