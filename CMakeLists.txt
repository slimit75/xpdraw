set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" FORCE)
cmake_minimum_required(VERSION 3.9.1)
project(xpdraw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -fPIC -fvisibility=hidden -Wno-narrowing")

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

add_library(xpdraw 
    src/xpdraw.cpp
)

add_definitions(-DXPLM200)
add_definitions(-DXPLM210)
add_definitions(-DXPLM300)
add_definitions(-DXPLM301)
add_definitions(-DXPLM302)
add_definitions(-DXPLM303)

include_directories("libs/XSDK/CHeaders/XPLM")
include_directories("libs/XSDK/CHeaders/Widgets")
include_directories("libs/stb")

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static -shared -Wl,--version-script=exports.txt")
    add_definitions(-DIBM)
    #add_definitions(-DGLEW_STATIC)
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared -Wl,-exported_symbol -Wl,_XPluginStart -Wl,-exported_symbol -Wl,_XPluginEnable -Wl,-exported_symbol -Wl,_XPluginReceiveMessage -Wl,-exported_symbol -Wl,_XPluginDisable -Wl,-exported_symbol -Wl,_XPluginStop")
    add_definitions(-DAPL)
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -shared -Wl,--version-script=exports.txt")
    add_definitions(-DLIN)
    set_target_properties(xpdraw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ./export/lib/lin
    )

    target_link_libraries(xpdraw 
        stdc++
        freetype
    )
endif ()