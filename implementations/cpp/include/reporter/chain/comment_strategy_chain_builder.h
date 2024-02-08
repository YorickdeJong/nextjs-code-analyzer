#pragma once

#include <memory>

#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/chain/chain_builder.h"

class CommentStrategyChain {

    public:
        std::string ExecuteChain(const ChainBuilder& builder, const AnalysisReport& analysisReport, 
            const std::string &javascriptTokenValue);

};