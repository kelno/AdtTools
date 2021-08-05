INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/console_tools/ConsoleTools
)

file(GLOB sources_copy_MCLQ *.cpp *.h)

add_executable(CopyWater 
    ${sources_copy_MCLQ}
)
set_target_properties(CopyWater PROPERTIES OUTPUT_NAME "copywater")

add_dependencies(CopyWater Core)

target_link_libraries(CopyWater
    Core
    ConsoleTools
)

install(TARGETS CopyWater DESTINATION ${CMAKE_INSTALL_PREFIX})
