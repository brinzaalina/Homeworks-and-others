cmake_minimum_required(VERSION 3.19)
project(Vegetables)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_VERSION 5)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

include_directories(Domain)
include_directories(Exceptions)
include_directories(GUI)
include_directories(Repository)
include_directories(Service)

add_executable(Vegetables
        Domain/Domain.cpp
        Domain/Domain.h
        Exceptions/Exceptions.cpp
        Exceptions/Exceptions.h
        GUI/GUI.cpp
        GUI/GUI.h
        Repository/Repository.cpp
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h
        main.cpp)


target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})