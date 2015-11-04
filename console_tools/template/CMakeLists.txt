file(GLOB sources_ConsoleToolTemplate *.cpp *.h)

set(ConsoleToolTemplate_SRCS
  ${sources_ConsoleToolTemplate}
)

add_library(ConsoleToolTemplate ${sources_ConsoleToolTemplate})

add_dependencies(ConsoleToolTemplate Core)

target_link_libraries( ConsoleToolTemplate
    Core
) 