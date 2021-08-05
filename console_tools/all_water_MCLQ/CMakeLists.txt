INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/console_tools/ConsoleTools
)

file(GLOB sources_all_water_MCLQ *.cpp *.h)

add_executable(AllWater 
    ${sources_all_water_MCLQ}
)
set_target_properties(AllWater PROPERTIES OUTPUT_NAME "allwater")

add_dependencies(AllWater Core)

target_link_libraries(AllWater
    Core
    ConsoleTools
)

install(TARGETS AllWater DESTINATION ${CMAKE_INSTALL_PREFIX})
