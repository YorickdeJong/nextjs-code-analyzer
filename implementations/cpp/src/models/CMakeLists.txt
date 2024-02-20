

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(analysis_report
    analysis_report.cpp
)



target_link_libraries(analysis_report json_manager)


target_include_directories(analysis_report PUBLIC 
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/single_include
    ${NODE_ADDON_API_DIR}
)

if(WIN32)
  target_link_libraries(analysis_report libnode_api.a)
endif()