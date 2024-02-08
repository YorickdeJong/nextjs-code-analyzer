

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(reporter
    analysis_report.cpp
)



target_link_libraries(reporter json_manager)


target_include_directories(reporter PUBLIC 
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/single_include
    ${NODE_ADDON_API_DIR}

)