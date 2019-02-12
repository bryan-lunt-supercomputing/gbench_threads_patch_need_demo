cmake_minimum_required (VERSION 3.5)
project(mp1 VERSION 1.0.0 LANGUAGES CXX)

# Location of additional cmake modules
#
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake
    )

(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DATA_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/data)

#we need an openmp compiler
find_package(OpenMP)
if(NOT OPENMP_FOUND)
	message(FATAL_ERROR "ERROR: OpenMP not found.")
else(NOT OPENMP_FOUND)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif(NOT OPENMP_FOUND)

#Benchmarking
find_package(GBench)
if(NOT GBENCH_FOUND)
	message(FATAL_ERROR "DANGER: Could not find GoogleBenchmark")
endif(NOT GBENCH_FOUND)



#BENCHMARKING
add_executable(run_benchmarks "tests/allbench.cpp")
target_link_libraries(run_benchmarks OpenMP::OpenMP_CXX)
include_directories(run_benchmarks pthread ${GBENCH_INCLUDE_DIRS})
target_link_libraries(run_benchmarks ${GBENCH_BOTH_LIBRARIES})
