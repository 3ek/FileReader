cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
project(FileReader)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES
    src/main.cpp
    src/FileReaderApp.cpp
    src/FileReaderC.cpp
    src/FileReaderCpp.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES} )