## Qt stuff ##

#"Automatically link Qt executables to qtmain target on Windows."
cmake_policy(SET CMP0020 NEW)
# set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_path(QT_ROOT_DIR bin/qmake.exe bin/qmake)
IF(NOT QT_ROOT_DIR)
     message(FATAL_ERROR "Please set QT_ROOT_DIR to a directory like D:/Qt/5.4/msvc2013")
ENDIF()

message("Using QT_ROOT_DIR = ${QT_ROOT_DIR}")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${QT_ROOT_DIR}")
set(Qt5Widgets_DIR "${QT_ROOT_DIR}/lib/cmake/Qt5Widgets")
set(Qt5Core_DIR "${QT_ROOT_DIR}/lib/cmake/Qt5Core")
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

## End Qt stuff ##

#add all subproject sources to solution
file(GLOB sources_AdtTools *.cpp *.h)
file(GLOB sources_AdtTools_ui ui/*.cpp ui/*.h ui/*.ui)

set(AdtTools_SRCS
  ${sources_AdtTools}
  ${sources_AdtTools_ui}
)

add_executable(AdtTools ${sources_AdtTools})

#install(FILES D:/a.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) 
#install(FILES ${QT_ROOT_DIR}/bin/QtCore5.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) 

add_dependencies(AdtTools Core)

target_link_libraries( AdtTools
    Core
)

qt5_use_modules(AdtTools Widgets Core)