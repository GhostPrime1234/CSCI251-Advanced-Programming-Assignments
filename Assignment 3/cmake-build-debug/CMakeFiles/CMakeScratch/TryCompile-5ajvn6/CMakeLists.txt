cmake_minimum_required(VERSION 3.29.6.0)
project(CMAKE_TRY_COMPILE C)
set_property(DIRECTORY PROPERTY INCLUDE_DIRECTORIES "")
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILE_DEFINITIONS}")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_LINKER_FLAGS}")
include_directories(${INCLUDE_DIRECTORIES})
set(CMAKE_SUPPRESS_REGENERATION 1)
link_directories(${LINK_DIRECTORIES})
add_definitions([==[-v]==])
cmake_policy(SET CMP0065 NEW)
cmake_policy(SET CMP0083 NEW)
cmake_policy(SET CMP0155 NEW)
cmake_policy(SET CMP0157 OLD)
include("${CMAKE_ROOT}/Modules/Internal/HeaderpadWorkaround.cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/Michael/OneDrive - University of Wollongong/UOW/Bachelor of Computer Science/Year2/Spring/CSCI251 - Advanced Programming/Assessments/Assignment3/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-5ajvn6")
add_executable(cmTC_9010f)
target_sources(cmTC_9010f PRIVATE
  "C:/Users/Michael/AppData/Local/Programs/CLion/bin/cmake/win/x64/share/cmake-3.29/Modules/CMakeCCompilerABI.c"
)
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/cmTC_9010f_loc"
     CONTENT $<TARGET_FILE:cmTC_9010f>)
target_link_libraries(cmTC_9010f ${LINK_LIBRARIES})
