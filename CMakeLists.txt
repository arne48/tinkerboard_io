cmake_minimum_required (VERSION 2.8.11)
project (tinkerboard_io)


add_library(tinkerboard_io SHARED tinkerboard_io.c)

add_executable(example example.c)
target_link_libraries(example tinkerboard_io)
