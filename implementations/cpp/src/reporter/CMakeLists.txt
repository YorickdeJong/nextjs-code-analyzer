

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(reporter
    reporter.cpp
)


target_include_directories(reporter PUBLIC 
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/single_include
)