set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(json_manager SHARED json_manager.cpp)

message("NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR}") 
# Specify include directories for the reader target
target_include_directories(json_manager PUBLIC 
  ${INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/external/json/single_include
  ${NODE_ADDON_API_DIR}
)
