file(GLOB sources_AllWater *.cpp *.h)

set(AllWater_SRCS
  ${sources_AllWater}
)

add_executable(AllWaterMCLQ ${sources_AllWater})
set_target_properties(AllWaterMCLQ PROPERTIES OUTPUT_NAME "AllWaterPreWotLK")

add_dependencies(AllWaterMCLQ ConsoleToolTemplate)

target_link_libraries( AllWaterMCLQ
	ConsoleToolTemplate
) 