cmake_minimum_required(VERSION 3.15)

project(fltk_experiments)

set(FLTK_DIR "/usr/lib/fltk"
    CACHE FILEPATH "FLTK Installation or build directory")

find_package(FLTK REQUIRED CONFIG)

add_executable(window1 WIN32 MACOSX_BUNDLE window1.cpp)
add_executable(window2 WIN32 MACOSX_BUNDLE window2.cpp)

if (APPLE)
    target_link_libraries(window1 PRIVATE "-framework cocoa")
    target_link_libraries(window2 PRIVATE "-framework cocoa")
endif (APPLE)

target_include_directories(window1 PRIVATE ${FLTK_INCLUDE_DIRS})
target_include_directories(window2 PRIVATE ${FLTK_INCLUDE_DIRS})

target_link_libraries(window1 PRIVATE fltk)
target_link_libraries(window2 PRIVATE fltk)
