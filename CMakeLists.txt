project(AdtTools)
cmake_minimum_required (VERSION 3.0)

message("* AdtTools *")

# set default buildoptions and print them
include(cmake/options.cmake)

include(cmake/settings.cmake)

#global includes
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/core
	${PROJECT_SOURCE_DIR}/core/chunks
)

#add subdirectories according to selected cmake options
add_subdirectory(core)
if (CONSOLE_TOOLS)
	add_subdirectory(console_tools)
endif ()

if (GUI)
	add_subdirectory(gui)
endif ()