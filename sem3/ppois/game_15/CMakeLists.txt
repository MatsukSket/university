cmake_minimum_required(VERSION 3.10)

project(MyPuzzle)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")


# *** MAIN *** 
add_executable(main_app
    src/main.cpp
    src/Game.cpp
)

target_include_directories(main_app PRIVATE src)


# *** TESTS ***
add_executable(test_app
    tests/test.cpp
    src/Game.cpp
)

target_include_directories(test_app PRIVATE src)

find_library(UNITTEST_LIB UnitTest++)
if(UNITTEST_LIB)
    target_link_libraries(test_app ${UNITTEST_LIB})
else()
    message(FATAL_ERROR "UnitTest++ not found")
endif()


# *** COVERAGE ***
add_custom_target(coverage
    COMMAND find . -name "*.gcda" -delete
    COMMAND ./test_app
    COMMAND sleep 0.5
    COMMAND echo "=== Game.cpp Coverage ==="
    COMMAND gcov CMakeFiles/test_app.dir/src/Game.cpp.gcda | grep "/lab1/game_15/src/Game.cpp" -A 1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS test_app
)