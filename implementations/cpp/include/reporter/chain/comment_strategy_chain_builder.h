#pragma once

#include <memory>

#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/chain/chain_builder.h"

/**
 * CommentStrategyChain orchestrates the execution of a chain of comment strategies.
 * It applies each strategy in sequence until one indicates no further processing is needed.
 */
class CommentStrategyChain {

    public:
        /**
         * Executes a sequence of comment strategies until one strategy returns false.
         * @param builder A reference to a ChainBuilder that holds the sequence of strategies.
         * @param analysisReport A reference to the analysis report with the details needed for commenting.
         * @param javascriptTokenValue The JavaScript token value that is subject to commenting.
         * @return A string with the accumulated comments from the executed strategies.
         */
        std::string ExecuteChain(const ChainBuilder& builder, const AnalysisReport& analysisReport, 
            const std::string &javascriptTokenValue);

};