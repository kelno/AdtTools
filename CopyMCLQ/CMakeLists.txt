#add all subproject sources to solution
file(GLOB sources_CopyMCLQ *.cpp *.h)

set(CopyMCLQ_SRCS
  ${sources_CopyMCLQ}
)

add_executable(CopyMCLQ ${sources_CopyMCLQ})
set_target_properties(CopyMCLQ PROPERTIES OUTPUT_NAME "CopyPreWotLKWater")

add_dependencies(CopyMCLQ Core)

target_link_libraries( CopyMCLQ
    Core
)