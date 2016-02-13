include_directories(minizip)
add_subdirectory(minizip)

set(SRC ZipFile.cpp
        ZipFileImpl.cpp
        Archive.cpp
        Compressor.cpp
        NewFileInfo.cpp)
        
set(HEADERS ZipFile.h
            ZipFileImpl.h
            Archive.h
            Compressor.h
            NewFileInfo.h)

add_library(qminizip ${SRC} ${HEADERS})
target_link_libraries(qminizip minizip Qt5::Core)