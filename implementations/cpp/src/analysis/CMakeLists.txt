

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(analysis
    analysis.cpp
)


target_include_directories(analysis PUBLIC 
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/single_include
)