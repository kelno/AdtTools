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
file(GLOB sources_GUI *.cpp *.h)
file(GLOB sources_GUI_ui ui/*.cpp ui/*.h ui/*.ui)

set(GUI_SRCS
  ${sources_GUI}
  ${sources_GUI_ui}
)

add_executable(GUI ${sources_GUI})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

#release dll's
install(FILES ${QT_ROOT_DIR}/bin/Qt5Core.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Release) 
install(FILES ${QT_ROOT_DIR}/bin/Qt5Widgets.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Release) 
install(FILES ${QT_ROOT_DIR}/bin/libEGL.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Release) 
install(FILES ${QT_ROOT_DIR}/bin/libGLESv2.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Release)
install(FILES ${QT_ROOT_DIR}/plugins/platforms/qwindows.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/platforms/ CONFIGURATIONS Release) 
	#this one is only needed to start the program in visual studio
	install(FILES ${QT_ROOT_DIR}/plugins/platforms/qwindows.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/platforms/ CONFIGURATIONS Release) 

#debug dll's
install(FILES ${QT_ROOT_DIR}/bin/Qt5Cored.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Debug) 
install(FILES ${QT_ROOT_DIR}/bin/Qt5Widgetsd.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Debug) 
install(FILES ${QT_ROOT_DIR}/bin/libEGLd.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Debug) 
install(FILES ${QT_ROOT_DIR}/bin/libGLESv2d.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH} CONFIGURATIONS Debug) 
install(FILES ${QT_ROOT_DIR}/plugins/platforms/qwindowsd.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/platforms/ CONFIGURATIONS Debug) 
	#this one is only needed to start the program in visual studio
	install(FILES ${QT_ROOT_DIR}/plugins/platforms/qwindowsd.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/platforms/ CONFIGURATIONS Debug) 

#both config dll's
install(FILES ${QT_ROOT_DIR}/bin/Qt5Guid.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
install(FILES ${QT_ROOT_DIR}/bin/icuin53.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
install(FILES ${QT_ROOT_DIR}/bin/icuuc53.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
install(FILES ${QT_ROOT_DIR}/bin/icudt53.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_dependencies(GUI Core)

target_link_libraries( GUI
    Core
)

qt5_use_modules(GUI Widgets Core)