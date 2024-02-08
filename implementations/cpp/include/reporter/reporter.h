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
        
        /**
         * Adds comment tokens to the JSON object.
         * @param j The JSON object being modified.
         * @param tokensToComment A set containing the tokens that require comments.
         */
        void AddCommentTokens(nlohmann::json &j, const std::unordered_set<std::string> &tokensToComment); 
        
        /**
         * Creates a comment in the JSON object for a specific token.
         * @param jToken The JSON token to which the comment is added.
         * @param commentText The text of the comment to add.
         */
        void CreateComment(nlohmann::json &jToken, const std::string &commentText);
        
        AnalysisReport m_analysisReport; 
        std::vector<TokenInfo> m_tokenInfos;
} ;