cmake_minimum_required(VERSION 3.5.1)

option(test "Build all tests." ON) # Makes boolean 'test' available.

project(GamblingMachine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

find_package(Boost COMPONENTS system filesystem REQUIRED)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(CLIENT_SOURCES ${SOURCE_FILES})
list(REMOVE_ITEM CLIENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main_server.cpp)

set(SERVER_SOURCES ${SOURCE_FILES})
list(REMOVE_ITEM SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main_client.cpp)

add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})

message(${CLIENT_SOURCES})
message(${SERVER_SOURCES})

target_link_libraries(client
		pthread
        ${Boost_LIBRARIES}
)

target_link_libraries(server
		pthread
        ${Boost_LIBRARIES}
)