cmake_minimum_required(VERSION 3.19)
project(Template)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_VERSION 5)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(.)
include_directories(domain)
include_directories(exceptions)
include_directories(gui)
include_directories(repository)
include_directories(service)

add_executable(Template
        domain/Domain.cpp
        domain/Domain.h
        exceptions/Exceptions.cpp
        exceptions/Exceptions.h
        gui/GUI.cpp
        gui/GUI.h
        repository/Repository.cpp
        repository/Repository.h
        service/Service.cpp
        service/Service.h
        main.cpp
        observer/Observer.h)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})