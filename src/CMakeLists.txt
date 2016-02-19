include_directories(minizip)
add_subdirectory(minizip)

set(SRC ZipFile.cpp
        ZipFileImpl.cpp
        Archive.cpp
        Compressor.cpp
        FileInfo.cpp
        NewFileInfo.cpp
        ZipReadIterator.cpp)
        
set(HEADERS ZipFile.h
            ZipFileImpl.h
            Archive.h
            Compressor.h
            FileInfo.h
            NewFileInfo.h
            ZipReadIterator.h)

add_library(qminizip ${SRC} ${HEADERS})
target_link_libraries(qminizip minizip Qt5::Core)