

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(reporter
    reporter.cpp
    chain/chain_builder.cpp
    chain/comment_strategy_chain_builder.cpp

    strategy/hook_strategy.cpp
    strategy/html_strategy.cpp
    strategy/use_client_strategy.cpp
)



target_link_libraries(reporter json_manager analysis_report)


target_include_directories(reporter PUBLIC 
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/single_include
    ${NODE_ADDON_API_DIR}
)

if(WIN32)
  target_link_libraries(reporter libnode_api.a)
endif()