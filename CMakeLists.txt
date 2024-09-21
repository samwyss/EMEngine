cmake_minimum_required(VERSION 3.27)

# set compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    # Debug
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -g3")

    # Release
    # may also add -fopt-info-vec-all for vectorization report
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -DNDEBUG -Wall -fstrict-aliasing -ftree-vectorize -march=native -mtune=native -mprefer-vector-width=512 -fno-trapping-math -fno-math-errno -flto")

    # RelWithDebInfo
    # may also add -fopt-info-vec-all for vectorization report
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g3 -Wall -fstrict-aliasing -ftree-vectorize -march=native -mtune=native -mprefer-vector-width=512 -fno-trapping-math -fno-math-errno -flto")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    # Debug
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /W4 /Zi")

    # Release
    # may also replace /arch:AVX2 with /arch:AVX512 for newer CPUS
    # may also add /Qvec-report:2 for auto vectorization report
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /W4 /arch:AVX2 /fp:contract /GL")

    # RelWithDebInfo
    # may also replace /arch:AVX2 with /arch:AVX512 for newer CPUS
    # may also add /Qvec-report:2 for auto vectorization report
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Zo /W4 /arch:AVX2 /fp:contract /GL")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

    if (UNIX)

        # Debug
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

        # Release
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fno-fnalias -axcodeCORE-AVX512 -xhost -vecabi=cmdtarget -qopt-zmm-usage=high -ipo")

        # RelWithDebInfo
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g -debug extended -fno-fnalias -axcodeCORE-AVX512 -xhost -vecabi=cmdtarget -qopt-zmm-usage=high -ipo -qopt-report:5")

    elseif (WIN32)

        # Debug
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

        # Release
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O3 /Ow- /QaxcodeCORE-AVX512 /QxHOST /Qvecabi:cmdtarget /Qopt-zmm-usage:high /Qipo")

        # RelWithDebInfo
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O3 /debug:full /Ow- /QaxcodeCORE-AVX512 /QxHOST /Qvecabi:cmdtarget /Qopt-zmm-usage:high /Qipo /Qopt-report=5")

    endif ()

endif ()

# define project
project(EMEngine VERSION 0.0.1 LANGUAGES CXX)

# set cxx standard
set(CMAKE_CXX_STANDARD 20)

# find MPI
find_package(MPI REQUIRED)

# define executable
add_executable(EMEngine src/main.cpp)

# link libraries to executable
target_link_libraries(EMEngine
        PRIVATE MPI::MPI_CXX)