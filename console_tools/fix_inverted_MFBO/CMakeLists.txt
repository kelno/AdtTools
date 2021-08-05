INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/console_tools/ConsoleTools
)

file(GLOB sources_fix_inverted_mfbo *.cpp *.h)

add_executable(FixInvertedMFBO 
    ${sources_fix_inverted_mfbo}
)
set_target_properties(FixInvertedMFBO PROPERTIES OUTPUT_NAME "fixcamera")

add_dependencies(FixInvertedMFBO Core)

target_link_libraries(FixInvertedMFBO
    Core
    ConsoleTools
)

install(TARGETS FixInvertedMFBO DESTINATION ${CMAKE_INSTALL_PREFIX})
