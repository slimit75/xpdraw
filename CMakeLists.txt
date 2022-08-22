set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" FORCE)
cmake_minimum_required(VERSION 3.9.1)
project(xpdraw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -fPIC -pedantic")

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

add_library(xpdraw 
    src/xpdraw.cpp
    src/xpdraw/xpdraw.h
    src/windows.cpp
    src/xpdraw/windows.h
    src/tools.cpp
    src/xpdraw/tools.h
    src/fonts.cpp
    src/xpdraw/fonts.h
)

add_definitions(
    -DXPLM200
    -DXPLM210
    -DXPLM300
    -DXPLM301
    -DXPLM302
    -DXPLM303
)

include_directories("libs/XSDK/CHeaders/XPLM")
include_directories("libs/XSDK/CHeaders/Widgets")
include_directories("libs/stb")

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DIBM)
    add_definitions(-D_USE_MATH_DEFINES)
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./export/lib/win
    )
    target_link_libraries(xpdraw
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Win/XPLM_64.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Win/XPWidgets_64.lib"
        opengl32
        imagehlp
        Psapi
		stdc++
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions(-DAPL)
    add_definitions(-DGL_SILENCE_DEPRECATION)
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./export/lib/mac
    )
    target_link_libraries(xpdraw
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Mac/XPLM.framework"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Mac/XPWidgets.framework"
        "-framework OpenGL"
        "-framework CoreFoundation"
        stdc++
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DLIN)
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./export/lib/lin
    )
    target_link_libraries(xpdraw 
        stdc++
        freetype
    )
endif ()