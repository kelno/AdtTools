project (AdtLib)
#cmake_policy (SET CMP0015 OLD)
set(ADTLIB_VERSION 0.0.1)
cmake_minimum_required (VERSION 2.6)

# Additional search paths for find_package.
# Set this to more paths you windows guys need.
if (WIN32)
  set ( CMAKE_INCLUDE_PATH
        "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include/"
        "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/include/"
  )
  set ( CMAKE_LIBRARY_PATH
        "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/lib/"
        "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/lib/"
  )
endif( WIN32 )

# Our own FindModule.cmake scripts.
#set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_BUILD_TYPE "Release")

find_package (Qt4 4.8 COMPONENTS QtCore QtGui REQUIRED)

# Qt setup
include (${QT_USE_FILE})

#sans effet
set ( adtlib_misc
	resource/untitled.ui
)

option (ALL_WARNINGS "Enable all warnings?" OFF)

if (ALL_WARNINGS)
  message (STATUS "Spilling out mass warnings.")
  if (WIN32)
    add_definitions (/W4 /Wall /Wp64)
  else (WIN32)
    add_definitions (-W -Wall -Wshadow)
  endif (WIN32)
endif (ALL_WARNINGS)

# MSVC++ specific defines.
#if (WIN32)
 #   add_definitions (/D NOMINMAX)
#endif (WIN32)
#see http://msdn.microsoft.com/en-us/library/hhzbb5c8.aspx

file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.ui)

source_group("sources"            REGULAR_EXPRESSION src/.*cpp)
source_group("headers"            REGULAR_EXPRESSION src/.*h)
source_group("resources"              REGULAR_EXPRESSION resource)

add_executable ( 
	AdtLib
		${SRCS}
)

target_link_libraries ( 
	AdtLib
		${QT_LIBRARIES}
)