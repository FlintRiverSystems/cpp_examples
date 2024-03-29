
cmake_minimum_required(VERSION 3.12)

set(FRSTPSRC $ENV{FRSTPSRC})
message("FRSTPSRC: ${FRSTPSRC}")

set(VCPKG_DIR "${FRSTPSRC}/vcpkg")
message("VCPKG_DIR: ${VCPKG_DIR}")

set(ENV{VCPKG_DISABLE_METRICS} true)
set(ENV{X_VCPKG_ASSET_SOURCES} "clear;x-azurl,file://$ENV{FRSTPSRC}/vcpkg_asset_cache,,readwrite")
set(ENV{VCPKG_BINARY_SOURCES} "clear;files,$ENV{FRSTPSRC}/vcpkg_binary_cache,readwrite")
set(ENV{VCPKG_DOWNLOADS} $ENV{FRSTPSRC}/vcpkg_downloads)
file(MAKE_DIRECTORY $ENV{FRSTPSRC}/vcpkg_asset_cache)
file(MAKE_DIRECTORY $ENV{FRSTPSRC}/vcpkg_binary_cache)

if(WIN32)
        set(VCPKG_TARGET_TRIPLET "x64-windows-static-md") # build static libraries that use DLL runtime
endif()

set(CMAKE_TOOLCHAIN_FILE ${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake CACHE STRING "vcpkg toolchain file")

project(boost_test_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME})

find_package (Boost REQUIRED COMPONENTS filesystem date_time log unit_test_framework)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::log Boost::unit_test_framework)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	source_group(" " REGULAR_EXPRESSION ".*")
	source_group("pch" REGULAR_EXPRESSION "cmake_pch\..*")

	target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
set_source_files_properties(src/main.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)


file(GLOB SRC_HDR src/*.h)
file(GLOB SRC_CPP src/*.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${SRC_HDR} ${SRC_CPP})


