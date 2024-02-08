

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_include_directories(reporter PUBLIC 
    ${NODE_ADDON_API_DIR}
    ${FOLDER_SOURCE_DIR}/include
    ${INCLUDE_DIR} 
    ${PROJECT_SOURCE_DIR}/src/reader 
    ${PROJECT_SOURCE_DIR}/src/reporter 
    ${PROJECT_SOURCE_DIR}/src/analysis
    ${PROJECT_SOURCE_DIR}/external/json/single_include
)

# Add test executable
add_executable(analysis_test analysis_test.cpp)
add_executable(reporter_test reporter_test.cpp)
add_executable(useclient_strategy_test useclient_strategy_test.cpp)
add_executable(hook_strategy_test hook_strategy_test.cpp)
add_executable(hook_chain_builder_test hook_chain_builder_test.cpp)
add_executable(useclient_chain_builder useclient_chain_builder.cpp)


# Link against Google Test and any other libraries
target_link_libraries(analysis_test gtest gtest_main analysis)
target_link_libraries(reporter_test gtest gtest_main reporter analysis)
target_link_libraries(useclient_strategy_test gtest gtest_main reporter analysis)
target_link_libraries(hook_strategy_test gtest gtest_main reporter analysis)
target_link_libraries(hook_chain_builder_test gtest gtest_main reporter analysis)
target_link_libraries(useclient_chain_builder gtest gtest_main reporter analysis)

# Add the test to CTest's test suite
add_test(NAME analysis_test COMMAND analysis_test)
add_test(NAME reporter_test COMMAND reporter_test)
add_test(NAME useclient_strategy_test COMMAND useclient_strategy_test)
add_test(NAME hook_strategy_test COMMAND hook_strategy_test)
add_test(NAME hook_chain_builder_test COMMAND hook_chain_builder_test)
add_test(NAME useclient_chain_builder COMMAND useclient_chain_builder)

