cmake_minimum_required(VERSION 3.0)

#-----------------------------------------------------------------------------#
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
#-----------------------------------------------------------------------------#

set(TARGET testbench)

add_executable(${TARGET} test.cpp ../src/videostream.cpp)
target_link_libraries(${TARGET} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${TARGET} PUBLIC ../include ${OpenCV_INCLUDE_DIRS})

#-----------------------------------------------------------------------------#
target_compile_options(${TARGET} PUBLIC -std=gnu++11
										-Wall
										-Werror
										-O2
)
#-----------------------------------------------------------------------------#
install(TARGETS ${TARGET} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)