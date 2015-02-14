file(GLOB sources_Core *.cpp *.h)
file(GLOB sources_Core_chunks Chunks/*.cpp Chunks/*.h)

set(Core_SRCS
  ${sources_Core}
  ${sources_Core_chunks}
)

add_library(Core ${Core_SRCS})