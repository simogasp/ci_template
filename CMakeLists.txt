cmake_minimum_required(VERSION 3.10)

project(ci-template VERSION 1.0.0 LANGUAGES CXX)

option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
        message(STATUS "spdlog not found, retrieving it via FetchContent")
        include(FetchContent)
        FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG   v1.16.0
        )

        FetchContent_GetProperties(spdlog)
        if(NOT spdlog_POPULATED)
            FetchContent_Populate(spdlog)
            add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
        endif()

endif()
message(STATUS "spdlog found, version: ${spdlog_VERSION}")


add_executable(hello src/main.cpp)
target_link_libraries(hello PRIVATE spdlog::spdlog)

if(BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(tests)
endif()