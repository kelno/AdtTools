INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/template
)

file(GLOB sources_consoleTools *.cpp *.h)
file(GLOB sources_Template template/*.cpp template/*.h)

file(GLOB sources_all_water_MCLQ all_water_MCLQ/*.cpp all_water_MCLQ/*.h)
file(GLOB sources_copy_MCLQ copy_MCLQ/*.cpp copy_MCLQ/*.h)
file(GLOB sources_fix_inverted_MFBO fix_inverted_MFBO/*.cpp fix_inverted_MFBO/*.h)

add_executable(ConsoleTools 
	${sources_consoleTools}
	${sources_Template}
	${sources_all_water_MCLQ}
	${sources_copy_MCLQ}
	${sources_fix_inverted_MFBO}
)
set_target_properties(ConsoleTools PROPERTIES OUTPUT_NAME "adttools")

add_dependencies(ConsoleTools Core)

target_link_libraries(ConsoleTools
	Core
) 