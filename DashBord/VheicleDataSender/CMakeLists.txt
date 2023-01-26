cmake_minimum_required(VERSION 3.5)

project(VheicleDataSender)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)
add_library(VheicleDataSender SHARED VheicleDataSender.cpp VheicleDataSender.h )

target_link_libraries(VheicleDataSender PRIVATE Qt6::Gui Qt6::Quick)
