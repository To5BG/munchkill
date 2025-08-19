file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(munchkill_test ${TEST_SOURCES} ${SOURCES})

target_link_libraries(munchkill_test PRIVATE fmt::fmt spdlog::spdlog)
target_include_directories(munchkill_test 
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

include(CTest)
add_test(NAME munchkill_test COMMAND munchkill_test)