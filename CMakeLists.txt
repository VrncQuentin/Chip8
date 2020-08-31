# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(Chip8)

# Set Compile Options
#set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(
  -Wall
  -Wextra
  -Wshadow
  -Wnon-virtual-dtor
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wpedantic
  -Wconversion
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wnull-dereference
  -Wuseless-cast
  -Wdouble-promotion
  )

option(USE_DEBUG "Enter debug mode" OFF)
if (USE_DEBUG)
  add_compile_options(-g3)
  add_compile_definitions(_DEBUG_)
endif (USE_DEBUG)

# Source directories
set(BASE_DIR src)
set(INTERP_DIR ${BASE_DIR}/interpreter)
set(GUI_DIR ${BASE_DIR}/gui)

# Includes
set(INC_DIRS ${BASE_DIR} ${INTERP_DIR} ${GUI_DIR})
include_directories(${INC_DIRS})

# Sources
## Base
set(BASE_SRC
  Chip8.cpp
  )
foreach (base_src ${BASE_SRC})
    set(PROJECT_SOURCES ${PROJECT_SOURCES} ${BASE_DIR}/${base_src})
endforeach (base_src)

## Interpreter
set(INTERP_SRC
        Regs.cpp
        Memory.cpp
        Stack.cpp
  )
foreach (interp_src ${INTERP_SRC})
    set(PROJECT_SOURCES ${PROJECT_SOURCES} ${INTERP_DIR}/${interp_src})
endforeach (interp_src)

## GUI
set(GUI_SRC
        Window.cpp
        Screen.cpp
        )
foreach (gui_src ${GUI_SRC})
    set(PROJECT_SOURCES ${PROJECT_SOURCES} ${GUI_DIR}/${gui_src})
endforeach (gui_src)

# Build
add_executable(
  chip8
  main.cpp
  ${PROJECT_SOURCES}
  )

target_link_libraries(chip8 PRIVATE -lsfml-graphics -lsfml-window -lsfml-system)
