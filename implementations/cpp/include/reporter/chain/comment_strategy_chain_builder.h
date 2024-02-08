#pragma once

#include <memory>

#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/chain/chain_builder.h"

class CommentStrategyChain {

    public:

        std::string ExecuteChain(const ChainBuilder& builder, const AnalysisReport& analysisReport, 
            const std::string &javascriptTokenValue) {
            std::string comments;

            for (const auto& strategy : builder.GetStrategies()) {
                if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
                    break; // Break the chain if a strategy indicates to stop further processing
                }
            }
            return comments;
        }

      
    private:

};