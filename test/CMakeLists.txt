
add_executable(TestArchive TestArchive.cpp)
target_link_libraries(TestArchive gtest gtest_main)
target_link_libraries(TestArchive qminizip)


configure_file(config.h.in config.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME Archive COMMAND TestArchive)