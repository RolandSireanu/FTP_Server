cmake_minimum_required(VERSION 3.1.0)
project(FTS)
set(CMAKE_BUILD_TYPE Debug)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

add_subdirectory(headers)
add_subdirectory(sources)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE pthread)

if(EnableTests)
    message("========= GTests enabled ! ===========")
    add_definitions(-DEnableTests)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    target_sources(${CMAKE_PROJECT_NAME} PRIVATE "./tests/DequeTests.cc" "./tests/MultithreadingDequeTests.cc")

    target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        gtest_main
        gtest
        )
    
    include(GoogleTest)
    gtest_discover_tests(${CMAKE_PROJECT_NAME})
endif()
