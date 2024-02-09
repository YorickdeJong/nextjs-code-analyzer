

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_include_directories(reporter PUBLIC 
    ${NODE_ADDON_API_DIR}
    ${FOLDER_SOURCE_DIR}/include
    ${INCLUDE_DIR} 
    ${PROJECT_SOURCE_DIR}/src/reader 
    ${PROJECT_SOURCE_DIR}/src/reporter 
    ${PROJECT_SOURCE_DIR}/src/analysis
    ${PROJECT_SOURCE_DIR}/src/models
    ${PROJECT_SOURCE_DIR}/external/json/single_include
)

# Add test executable
add_executable(analysis_test analysis_test.cpp)
add_executable(hook_strategy_test hook_strategy_test.cpp)
add_executable(use_client_strategy_test use_client_strategy_test.cpp)
add_executable(hook_chain_builder_test hook_chain_builder_test.cpp)
add_executable(use_client_chain_builder use_client_chain_builder.cpp)
add_executable(html_strategy_test html_strategy_test.cpp)


# Link against Google Test and any other libraries
target_link_libraries(analysis_test gtest gtest_main analysis_report analysis)
target_link_libraries(hook_strategy_test gtest gtest_main analysis_report reporter analysis )
target_link_libraries(use_client_strategy_test gtest gtest_main analysis_report reporter analysis)
target_link_libraries(hook_chain_builder_test gtest gtest_main analysis_report reporter analysis)
target_link_libraries(use_client_chain_builder gtest gtest_main analysis_report reporter analysis)
target_link_libraries(html_strategy_test gtest gtest_main analysis_report reporter analysis)

# Add the test to CTest's test suite
add_test(NAME analysis_test COMMAND analysis_test)
add_test(NAME hook_strategy_test COMMAND hook_strategy_test)
add_test(NAME use_client_strategy_test COMMAND use_client_strategy_test)
add_test(NAME hook_chain_builder_test COMMAND hook_chain_builder_test)
add_test(NAME use_client_chain_builder COMMAND use_client_chain_builder)
add_test(NAME html_strategy_test COMMAND html_strategy_test)

