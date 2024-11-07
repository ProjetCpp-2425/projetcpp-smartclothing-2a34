# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\transactionCRUD_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\transactionCRUD_autogen.dir\\ParseCache.txt"
  "transactionCRUD_autogen"
  )
endif()
