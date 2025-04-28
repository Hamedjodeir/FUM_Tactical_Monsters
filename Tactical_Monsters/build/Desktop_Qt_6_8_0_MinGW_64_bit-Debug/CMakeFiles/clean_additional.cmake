# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tactical_Monsters_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tactical_Monsters_autogen.dir\\ParseCache.txt"
  "Tactical_Monsters_autogen"
  )
endif()
