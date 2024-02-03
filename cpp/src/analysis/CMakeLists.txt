

set(MY_ANALYSIS_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(analysis
    analyzer.cpp
)

target_include_directories(analysis PUBLIC 
    ${MY_ANALYSIS_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/single_include
)