
add_executable(TestArchive TestArchive.cpp)
target_link_libraries(TestArchive gtest gtest_main)
target_link_libraries(TestArchive qminizip)

add_test(NAME Archive COMMAND TestArchive)