cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread ")

find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(server main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_LIBRARIES}
        Boost::filesystem
        Boost::system
        )