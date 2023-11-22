cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

## Space invaders
file(GLOB_RECURSE SOURCES Space_invaders/*.cpp Space_invaders/*.h)
add_executable(2_INVADERS ${SOURCES} )
target_include_directories(2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(2_INVADERS sfml-graphics)

## Tile_engine
file(GLOB_RECURSE SOURCES Tile_Engine/*.cpp Space_invaders/*.h)
add_executable(3_Tile_Engine ${SOURCES} )
target_include_directories(3_Tile_Engine SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(3_Tile_Engine sfml-graphics)

# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

# Add this line to link against lib_maths
target_link_libraries(3_Tile_Engine lib_maths)

## Pac_Man
file(GLOB_RECURSE SOURCES Pac_Man/*.cpp Space_invaders/*.h)
add_executable(Pac_Man ${SOURCES} )
target_include_directories(Pac_Man SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Pac_Man sfml-graphics)

## CW_practice
file(GLOB_RECURSE SOURCES CW_practice/*.cpp Space_invaders/*.h)
add_executable(CW_practice ${SOURCES} )
target_include_directories(CW_practice SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(CW_practice sfml-graphics)

#### Link Dependencies ####
foreach (exe ${EXECUTABLES})
  #Set working directory to build dir in visual studio
  set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
  )

  #Add all SFML libs.
  target_link_libraries(${exe}
    #lib_maths # We'll make this later.
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-audio debug sfml-audio-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-main
  )

  add_dependencies(${exe} sfml-graphics sfml-audio copy_resources)
endforeach ()