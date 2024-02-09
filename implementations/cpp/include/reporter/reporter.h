#pragma once

#include <nlohmann/json.hpp>
#include <unordered_set>
#include <regex>
#include <map>
#include <iostream>

#include "models/token_info.h"
#include "models/analysis_report.h"
#include "manager/json_manager.h"
#include "utils/constants.h"
#include "reporter/chain/comment_strategy_chain_builder.h"
#include "reporter/strategy/comment_strategy_interface.h"

/**
 * The Reporter class is responsible for adding optimization comments and suggestions
 * based on the findings in the Analyzer and Optimizer classes.
 */
class Reporter {
    public:
        Reporter(const AnalysisReport &analysisReport, const std::vector<TokenInfo> &tokenInfo);
        
        /**
         * Adds comments to a JSON object based on the analysis report.
         * @param jsonManager Manager responsible for handling the JSON object operations.
         */
        void AddCommentsToJsonObject(JsonManager& jsonManager);

    private: 
        void PopulateTokensToComment(const std::vector<TokenInfo> &tokenInfos, std::unordered_set<std::string> &tokensToComment);
        
        AnalysisReport m_analysisReport; 
        std::vector<TokenInfo> m_tokenInfos;
} ;