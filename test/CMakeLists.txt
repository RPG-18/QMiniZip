
add_executable(TestArchive TestArchive.cpp)
target_link_libraries(TestArchive qminizip gtest gtest_main)


add_executable(TestReadIterator TestReadIterator.cpp)
target_link_libraries(TestReadIterator  qminizip gtest gtest_main)

configure_file(config.h.in config.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME Archive COMMAND TestArchive)
add_test(NAME ReadIterator COMMAND TestReadIterator)