set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if (UNIX)
    add_definitions(-std=c++11)
endif ()

if (WIN32 AND MSVC)
	#enable multi processor compiling
    add_definitions(/MP)
endif ()