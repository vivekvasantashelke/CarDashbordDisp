cmake_minimum_required(VERSION 3.14)

project(DashBord VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#target_link_libraries(${DashBord} PUBLIC
 #   Qt${QT_VERSION_MAJOR}::Core
  #  Qt${QT_VERSION_MAJOR}::Gui
   # Qt${QT_VERSION_MAJOR}::Qml
    #Qt${QT_VERSION_MAJOR}::QuickControls2)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

add_subdirectory(VheicleDataSender)
set(PROJECT_SOURCES
        main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DashBord
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DashBord APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DashBord SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DashBord
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DashBord
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_link_directories(DashBord PUBLIC VheicleDataSender/)
target_link_libraries(DashBord PUBLIC VheicleDataSender)
set_target_properties(DashBord PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS DashBord
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
target_link_libraries(DashBord PRIVATE Qt6::QuickControls2)

#find_package(Qt6 REQUIRED COMPONENTS import QtQuick.Extras)
#target_link_libraries(DashBord PRIVATE Qt6::import QtQuick.Extras)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
target_link_libraries(DashBord PRIVATE Qt6::Widgets)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(DashBord)
    qt_finalize_executable(DashBord)
endif()
