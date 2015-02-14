project (AdtLib)
cmake_minimum_required (VERSION 3.0)

message("* AdtLib *")

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

IF(UNIX)
    add_definitions(-std=c++11)
ENDIF ()
IF (WIN32)
    add_definitions(/MP)
ENDIF ()

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/Core
	${PROJECT_SOURCE_DIR}/Core/Chunks
)

add_subdirectory(AdtTools)
add_subdirectory(AllWater)
add_subdirectory(Core)
add_subdirectory(CopyMCLQ)