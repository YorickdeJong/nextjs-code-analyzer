set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(json_manager SHARED json_manager.cpp)


# Specify include directories for the reader target
target_include_directories(json_manager PUBLIC 
  ${NODE_ADDON_API_DIR}
  ${INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/external/json/single_include
)

if(WIN32)
  target_link_libraries(json_manager libnode_api.a)
endif()