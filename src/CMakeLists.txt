cmake_minimum_required(VERSION 3.14)
# project(Chip8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

# Compilation Options
###############################################################################
add_compile_options(
  -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual
  -Wpedantic -Wconversion -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference
  -Wuseless-cast -Wdouble-promotion
) # Generic options

# Debug options
option(USE_DEBUG "Enter debug mode" OFF)

if (USE_DEBUG)
  add_compile_options(-g3)
  add_compile_definitions(_DEBUG_)
endif (USE_DEBUG)

# Prod/Release options
option(USE_PROD "Enter prod mode" OFF)

if (USE_PROD)
  add_compile_options(-O2 -march=native)
endif (USE_PROD)
###############################################################################

# c8vm
###############################################################################
set(C8VM_DIR c8vm)

set(C8VM_SRC main.cpp)

foreach (src ${C8VM_SRC})
  set(C8VM_SOURCES ${C8VM_SOURCES} ${C8VM_DIR}/${src})
endforeach (src)

include_directories(${C8VM_DIR} .)

# target_link_libraries(
#   c8vm PRIVATE
# )

add_executable(c8vm ${C8VM_SOURCES})
###############################################################################

# c8c
###############################################################################
set(C8C_DIR c8c)
set(C8C_SRC main.cpp)

foreach (src ${C8C_SRC})
  set(C8C_SOURCES ${C8C_SOURCES} ${C8C_DIR}/${src})
endforeach (src)

include_directories(${C8C_DIR} .)

# target_link_libraries(
#   c8vm PRIVATE
# )

add_executable(c8c ${C8C_SOURCES})
###############################################################################
