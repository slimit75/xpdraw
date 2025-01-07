cmake_minimum_required(VERSION 3.24)
project(xpdraw)

set(CMAKE_C_STANDARD 23)

# CMake Settings
set(CMAKE_C_FLAGS "-O3 -fPIC -pedantic -Wall")
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
	${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/xpdraw.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/windows.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/windows.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/tools.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/tools.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/fonts.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/xpdraw/fonts.h
)

# Include directories for both xpdraw & its dependants
target_include_directories(xpdraw
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src

	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/libs/XPSDK/CHeaders/XPLM
	${CMAKE_CURRENT_SOURCE_DIR}/libs/XPSDK/CHeaders/Widgets
	${CMAKE_CURRENT_SOURCE_DIR}/libs/stb
)

# OS-specific options
if (WIN32)
	# Compiler Definitions
	add_definitions(
		-DIBM
		-D_USE_MATH_DEFINES
	)

	# Libraries to link
	target_link_libraries(xpdraw
		${LINK_LIBRARIES}
		${CMAKE_CURRENT_SOURCE_DIR}/libs/XPSDK/Libraries/Win/XPLM_64.lib
		${CMAKE_CURRENT_SOURCE_DIR}/libs/XPSDK/Libraries/Win/XPWidgets_64.lib
		imagehlp
		Psapi
	)

	# Output Directory
	set_target_properties(xpdraw PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ./build/win
	)
elseif (APPLE)
	# Compiler Definitions
	add_definitions(
		-DAPL
		-DGL_SILENCE_DEPRECATION
	)

	# Libraries to link
	target_link_libraries(xpdraw
		${LINK_LIBRARIES}
		${CMAKE_CURRENT_SOURCE_DIR}/libs/XPSDK/Libraries/Mac/XPLM.framework
		${CMAKE_CURRENT_SOURCE_DIR}/libs/XPSDK/Libraries/Mac/XPWidgets.framework
		"-framework OpenGL"
		"-framework CoreFoundation"
	)

	# Output Directory
	set_target_properties(xpdraw PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ./build/mac
	)
else ()
	# Compiler Definitions
	add_definitions(-DLIN)

	# Output Directory
	set_target_properties(xpdraw PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ./build/lin
	)
endif ()