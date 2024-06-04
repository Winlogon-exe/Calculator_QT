cmake_minimum_required(VERSION 3.5)

project(Cal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:/QT/6.7.1/msvc2019_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        inc/calculatormodel.h
        inc/view.h

        src/main.cpp
        src/calculatormodel.cpp
        src/view.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Cal
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Cal SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(Cal
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Cal PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Cal PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Cal
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Cal)
endif()
