find_package(Catch2 QUIET)
if(NOT Catch2_FOUND)
    message(STATUS "Catch2 not found, using FetchContent to download it.")
    include(FetchContent)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG v3.11.0
    )

    FetchContent_MakeAvailable(Catch2)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()
message(STATUS "Catch2 found, version ${Catch2_VERSION}")

add_executable(simple_test simple_test.cpp)
target_link_libraries(simple_test PRIVATE Catch2::Catch2WithMain)

# For Windows: Copy Catch2 DLL next to the test executable
if(WIN32)
    add_custom_command(TARGET simple_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Catch2::Catch2>
        $<TARGET_FILE_DIR:simple_test>
    )
    add_custom_command(TARGET simple_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Catch2::Catch2WithMain>
        $<TARGET_FILE_DIR:simple_test>
    )
endif()

include(Catch)
catch_discover_tests(simple_test
    DISCOVERY_MODE PRE_TEST
)
add_test(NAME simple_test COMMAND $<TARGET_FILE:simple_test>)