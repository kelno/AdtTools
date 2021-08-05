file(GLOB sources_ConsoleTools *.cpp *.h)

set(ConsoleTools_SRCS
  ${sources_ConsoleTools}
)

add_library(ConsoleTools ${ConsoleTools_SRCS})
