set(READER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(json_reader SHARED node_addon.cpp json_reader.cpp)

# Specify include directories for the reader target
target_include_directories(json_reader PRIVATE 
  ${READER_INCLUDE_DIR}
  ${NODE_ADDON_API_DIR}
)
