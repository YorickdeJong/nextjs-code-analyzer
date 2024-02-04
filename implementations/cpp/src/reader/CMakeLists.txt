set(READER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(json_reader SHARED json_reader.cpp)


# Specify include directories for the reader target
target_include_directories(json_reader PUBLIC 
  ${READER_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/external/json/single_include
  ${NODE_ADDON_API_DIR}
)
