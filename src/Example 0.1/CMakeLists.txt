cmake_minimum_required(VERSION 3.15)
project(RandomWalk CXX)

set(CMAKE_CXX_STANDARD 17)

if (EMSCRIPTEN)
    # Ensure static linking flags are set globally for Emscripten
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(BUILD_SHARED_LIBS OFF)

    # Path to raylib compiled for WebAssembly
    set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/raylib_wasm")

    # Import raylib as a STATIC library
    add_library(raylib STATIC IMPORTED)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${RAYLIB_DIR}/lib/libraylib.web.a"
        INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
    )

    # Add executable
    add_executable(RanWalk main.cpp)

    # Link raylib statically
    target_link_libraries(RanWalk PRIVATE raylib)

    # Apply Emscripten static link options
    target_link_options(RanWalk PRIVATE
        "-sUSE_GLFW=3"
        "-sASYNCIFY"
        "-sFORCE_FILESYSTEM=1"
    )

elseif (WIN32)
    set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/raylib_win64")
    add_library(raylib STATIC IMPORTED)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${RAYLIB_DIR}/lib/raylib.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
        INTERFACE_LINK_LIBRARIES "opengl32;gdi32;winmm;shell32"
    )
    add_executable(RanWalk main.cpp)
    target_link_libraries(RanWalk PRIVATE raylib)

elseif (UNIX)
    set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/raylib_5.5_linux")
    add_library(raylib STATIC IMPORTED)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${RAYLIB_DIR}/lib/libraylib.a"
        INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
        INTERFACE_LINK_LIBRARIES "GL;m;pthread;dl;rt;X11"
    )
    add_executable(RanWalk main.cpp)
    target_link_libraries(RanWalk PRIVATE raylib)
endif()