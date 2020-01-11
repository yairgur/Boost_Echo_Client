cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)
include_directories(bin)
include_directories(include)
include_directories(src)

link_libraries("-lboost_system -pthread")


add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/User.h
        include/KeyboardReader.h
        include/FromServerReader.h
        include/Inventory.h
        src/connectionHandler.cpp
        src/FromServerReader.cpp
        src/KeyboardReader.cpp
        src/User.cpp
        src/Inventory.cpp
        src/MainClient.cpp
        )

find_package(Boost 1.65.1 REQUIRED COMPONENTS
        date_time filesystem iostreams system)
find_package(Threads)

