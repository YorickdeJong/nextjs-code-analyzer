#pragma once

#include <nlohmann/json.hpp>
#include <unordered_set>
#include <regex>
#include <map>
#include <iostream>
#include "models/token_info.h"
#include "models/analysis_report.h"


// Reporter class is responsible for adding optimization comments and suggestions
// Based on the findings in the analyzer and optimzer classes
class Reporter {
    public:
        Reporter(const AnalysisResult &_analysisResult, const std::vector<TokenInfo> &_tokenInfo);
        void AddCommentsToJsonObject(nlohmann::json &j);

    private: 
        void PopulateTokensToComment(const std::vector<TokenInfo> &tokenInfos, std::unordered_set<std::string> &tokensToComment);
        void AddCommentTokens(nlohmann::json &j, const std::unordered_set<std::string> &tokensToComment); 
        void CreateComment(nlohmann::json &jToken, const std::string &commentText);
        
        
        AnalysisResult analysisResult; 
        std::vector<TokenInfo> tokenInfos;
} ;