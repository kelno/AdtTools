file(GLOB sources_FixInvertedMFBO *.cpp *.h)

set(FixInvertedMFBO_SRCS
  ${sources_FixInvertedMFBO}
)

add_executable(FixInvertedMFBO ${sources_FixInvertedMFBO})
set_target_properties(FixInvertedMFBO PROPERTIES OUTPUT_NAME "FixCamera")

add_dependencies(FixInvertedMFBO Core)

target_link_libraries( FixInvertedMFBO
    Core
)