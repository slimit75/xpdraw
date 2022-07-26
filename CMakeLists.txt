cmake_minimum_required(VERSION 3.25)
project(xpdraw)

# CMake Settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O2 -fPIC -pedantic")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

# Definitions for the X-Plane SDK
add_definitions(
    -DXPLM200
    -DXPLM210
    -DXPLM300
    -DXPLM301
    -DXPLM302
    -DXPLM303
)

# Include dependencies
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
add_library(xpdraw 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/xpdraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/windows.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/windows.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/tools.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fonts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/fonts.h
)
target_link_libraries(xpdraw
    stdc++
)

# Include directories for both xpdraw & its dependants
target_include_directories(xpdraw
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/CHeaders/XPLM
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/CHeaders/Widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb
)

# OS-specific options
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Compiler Definitions
    add_definitions(
        -DIBM
        -D_USE_MATH_DEFINES
    )
    
    # Libraries to link
    target_link_libraries(xpdraw
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Win/XPLM_64.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Win/XPWidgets_64.lib
        opengl32
        imagehlp
        Psapi
    )

    # Output Directory
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./build/win
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    # Compiler Definitions
    add_definitions(
        -DAPL
        -DGL_SILENCE_DEPRECATION
    )

    # Libraries to link
    target_link_libraries(xpdraw
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Mac/XPLM.framework
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Mac/XPWidgets.framework
        -framework OpenGL
        -framework CoreFoundation
    )

    # Output Directory
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./build/mac
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Compiler Definitions
    add_definitions(-DLIN)

    # Output Directory
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./build/lin
    )
endif ()