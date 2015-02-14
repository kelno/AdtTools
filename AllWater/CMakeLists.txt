#add all subproject sources to solution
file(GLOB sources_AllWater *.cpp *.h)

set(AllWater_SRCS
  ${sources_AllWater}
)

add_executable(AllWater ${sources_AllWater})
set_target_properties(AllWater PROPERTIES OUTPUT_NAME "AllWaterPreWotLK")

add_dependencies(AllWater Core)

target_link_libraries( AllWater
    Core
)