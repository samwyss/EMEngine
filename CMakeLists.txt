cmake_minimum_required(VERSION 3.27)

if (UNIX)
    set(CMAKE_C_COMPILER "mpicc")
    set(CMAKE_CXX_COMPILER "mpicxx")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
elseif (WIN32)
    include_directories("C:/Program Files (x86)/Microsoft SDKs/MPI/Include" "C:/Program Files (x86)/Microsoft SDKs/MPI/Include/x64")
    set(CMAKE_C_COMPILER "cl.exe")
    set(CMAKE_CXX_COMPILER "cl.exe")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2") #/arch:AVX512 /Qvec-report:2
endif ()

project(EMEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI REQUIRED)

add_executable(OpenPore src/main.cpp)

target_link_libraries(OpenPore
        PRIVATE MPI::MPI_CXX)