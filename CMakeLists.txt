project (AdtLib)
#cmake_policy (SET CMP0015 OLD)
set(ADTLIB_VERSION 0.0.1)
cmake_minimum_required (VERSION 2.6)

# Additional search paths for find_package.
# Set this to more paths you windows guys need.
if (WIN32)
  set ( CMAKE_INCLUDE_PATH
        "D:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include/"
        "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/include/"
  )
  set ( CMAKE_LIBRARY_PATH
        "D:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/lib/"
        "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/lib/"
  )
endif( WIN32 )

# Our own FindModule.cmake scripts.
#set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_BUILD_TYPE "Release")

find_package (Qt4 4.8 COMPONENTS QtCore QtGui QtXml REQUIRED)

# Qt setup
include (${QT_USE_FILE})

# Gather source files.
set ( adtlib_sources
    src/adt.cpp
	src/charArrayChunk.cpp
	src/chunkHeader.cpp
	src/debuglog.cpp
	src/main.cpp
	src/MCNK.cpp
	src/mfbo.cpp
	src/Window.cpp
)

set ( adtlib_headers
    src/adt.h
	src/charArrayChunk.h
	src/charArrayChunk1.h
	src/chunkHeader.h
	src/debuglog.h
	src/IntArrayChunk.h
	src/MCAL.h
	src/MCCV.h
	src/MCIN.h
	src/MCLQ.h
	src/MCLY.h
	src/MCNK.h
	src/MCNR.h
	src/MCRF.h
	src/MCSE.h
	src/MCSH.h
	src/MCVT.h
	src/MDDF.h
	src/MFBO.h
	src/MH2O.h
	src/MHDR.h
	src/MMDX.h
	src/MMID.h
	src/MODF.h
	src/MTEX.h
	src/MTXF.h
	src/MVER.h
	src/MWID.h
	src/MWMO.h
	src/tools.h
	src/ui_untitled.h
	src/Window.h
)
	
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
if (WIN32)
    add_definitions (/vmg /D NOMINMAX /wd"4503" /wd"4996")
endif (WIN32)

add_executable ( 
	AdtLib
		${adtlib_sources}
		${adtlib_headers}
		${adblib_misc}
)

target_link_libraries ( 
	AdtLib
		${QT_LIBRARIES}
)