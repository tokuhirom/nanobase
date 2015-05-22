cmake_minimum_required (VERSION 2.6)
project(nanobase)

enable_testing()

add_executable(01_encode t/01_encode.c)
set_target_properties(01_encode PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/t/")

add_executable(02_synopsis t/02_synopsis.c)
set_target_properties(02_synopsis PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/t/")

add_test(NAME prove COMMAND prove t)

include_directories(extlib/)
