cmake_minimum_required(VERSION 3.28)
project(ExamOOP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Charts Graphs)
qt_standard_project_setup()

find_package(Qt6Widgets REQUIRED)

include_directories(.)

add_executable(ExamOOP
        domain.cpp
        domain.h
        observer.cpp
        observer.h
        repository.cpp
        repository.h
        window.cpp
        window.h
        main.cpp
        main.cpp)

target_link_libraries(ExamOOP Qt6::Core Qt6::Widgets Qt6::Charts Qt6::Graphs)