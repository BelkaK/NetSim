cmake_minimum_required(VERSION 3.13)
project(sieci)
set(PROJECT_ID NetSim)
set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/helpers.cpp
        src/nodes.cpp
        include/package.hpp
        include/storage_types.hpp
        include/types.hpp
        include/helpers.hpp
        include/nodes.hpp
        )

set(SOURCES_FILES_TESTS
        test/tests.cpp
        )

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)


include_directories(include)

set(EXEC_DEBUG ${PROJECT_ID}__debug)

if(EXISTS ${PROJECT_SOURCE_DIR}/main.c)
    set(lang_src_extension c)
else()
    set(lang_src_extension cpp)
endif()

add_executable(${EXEC_DEBUG} ${SOURCE_FILES} main.${lang_src_extension})

if(EXISTS ${PROJECT_SOURCE_DIR}/test)
    set(EXEC_TEST ${PROJECT_ID}__test)
    add_executable(${EXEC_TEST} ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

    set(GTEST_ROOT googletest-master)

    target_include_directories(${EXEC_TEST} PUBLIC
            ${GTEST_ROOT}/googlemock/include
            ${GTEST_ROOT}/googletest/include
            )

    add_subdirectory(${GTEST_ROOT} googletest-master)

    target_link_libraries(${EXEC_TEST} gmock)
endif()


