cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

link_libraries("-lpthread")

include_directories(.)
include_directories(bin)
include_directories(include)
include_directories(src)

add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/User.h
        include/Writer.h
        include/Reader.h
        include/Inventory.h
        include/DB.h
        src/connectionHandler.cpp
        src/echoClient.cpp
        src/Reader.cpp
        src/Writer.cpp
        src/User.cpp
        src/Inventory.cpp
        src/DB.cpp
        src/MainClient.cpp
        )

