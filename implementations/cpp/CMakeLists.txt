

cmake_minimum_required(VERSION 3.10)
project(NextJS_Analyser VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_JS_INC})


# FINDING NODE
file(GLOB_RECURSE SOURCE_FILES 
    "${PROJECT_SOURCE_DIR}/src/**/*.cpp" 
    "${PROJECT_SOURCE_DIR}/include/**/*.h"
    "${PROJECT_SOURCE_DIR}/node_addon.cpp"
)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")


# Use `execute_process` to get the path to the Node.js N-API includes
execute_process(COMMAND node -p "require('node-addon-api').include"
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../typescript
                OUTPUT_VARIABLE NODE_ADDON_API_DIR)

# /Users/yorickdejong/nextjs_code_analyzer/implementations/typescript/node_modules/node-addon-api/napi-inl.h
message("projec dir ${PROJECT_SOURCE_DIR}")

if(NOT NODE_ADDON_API_DIR)
    message(FATAL_ERROR "NODE_ADDON_API_DIR is not set")
endif()

# Very important to remove trailing newline character from the output
# Otherwise napi.h cannot be found
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${NODE_ADDON_API_DIR}
)



# INCLUDING SUBDIRECTORIES
if (CMAKE_JS_VERSION)
    add_subdirectory(src/reader)
    add_subdirectory(src/analysis)
    add_subdirectory(src/reporter)
else()
    message(FATAL_ERROR "CMAKE_JS_VERSION is not defined")
endif()


#LINKING LIBRARIES
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} json_reader analysis reporter)

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()





