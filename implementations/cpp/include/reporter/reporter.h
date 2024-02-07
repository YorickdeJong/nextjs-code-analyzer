#pragma once

#include <nlohmann/json.hpp>
#include <unordered_set>
#include <regex>
#include <map>
#include <iostream>
#include "models/token_info.h"
#include "models/analysis_report.h"
#include "manager/json_manager.h"
#include "reporter/chain/comment_strategy_chain_builder.h"
#include "reporter/strategy/comment_strategy_interface.h"

// Reporter class is responsible for adding optimization comments and suggestions
// Based on the findings in the analyzer and optimzer classes
class Reporter {
    public:
        Reporter(const AnalysisReport &analysisReport, const std::vector<TokenInfo> &tokenInfo);
        void AddCommentsToJsonObject(JsonManager& jsonManager);

    private: 
        void PopulateTokensToComment(const std::vector<TokenInfo> &tokenInfos, std::unordered_set<std::string> &tokensToComment);
        void AddCommentTokens(nlohmann::json &j, const std::unordered_set<std::string> &tokensToComment); 
        void CreateComment(nlohmann::json &jToken, const std::string &commentText);
        
        
        AnalysisReport m_analysisReport; 
        std::vector<TokenInfo> m_tokenInfos;
} ;