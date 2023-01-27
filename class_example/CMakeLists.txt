
cmake_minimum_required(VERSION 3.12)

project(class_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(class_example)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	source_group(" " REGULAR_EXPRESSION ".*")
endif()

file(GLOB SRC_HDR *.h)
file(GLOB SRC_CPP *.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${SRC_HDR} ${SRC_CPP})

