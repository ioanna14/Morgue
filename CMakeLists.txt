cmake_minimum_required(VERSION 3.10)
project(Morgue)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\mingw73_64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES main.cpp
        CSVRepository.h
        HTMLRepository.h
        FileRepository.h
        MainRepository.h
        Service.h
        Service.cpp
        Domain.h
        GUI.cpp
        GUI.h
        Action.cpp
        Action.h
        MyListTable.cpp
        MyListTable.h
        )

set(EXTRA_FILES)

add_executable(Morgue ${SOURCE_FILES} ${EXTRA_FILES})

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
target_link_libraries(Morgue Qt5::Core Qt5::Gui Qt5::Widgets)
