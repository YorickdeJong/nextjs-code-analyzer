
#include "reporter/reporter.h"


Reporter::Reporter(const AnalysisReport &analysisReport, 
const std::vector<TokenInfo> &tokenInfo) 
: m_analysisReport{analysisReport}, m_tokenInfos{tokenInfo}
{
}


void Reporter::AddCommentsToJsonObject(JsonManager& jsonManager){
    std::unordered_set<std::string> tokensToComment;
    ChainBuilder chainBuilder; 
    CommentStrategyChain commentStrategyChain;


    PopulateTokensToComment(m_tokenInfos, tokensToComment);

    for (auto& jToken : jsonManager.GetJson()["tokens"]) {
        if (!jToken.contains("value") || !jToken["value"].is_string()) {
            continue; // Skip to the next iteration if conditions are not met
        }

        std::string javascriptTokenValue = jToken["value"];
        if (tokensToComment.find(javascriptTokenValue) == tokensToComment.end()) {
            continue; // Skip to the next iteration if value is not in tokensToComment
        }

        std::string comments = commentStrategyChain.ExecuteChain( chainBuilder, m_analysisReport, 
            javascriptTokenValue);
        
        jsonManager.Modify(comments);
    }
    
}



void Reporter::PopulateTokensToComment(const std::vector<TokenInfo> &m_tokenInfos, 
    std::unordered_set<std::string> &tokensToComment) {
    
    for (const auto& tokenInfo : m_tokenInfos) {
        tokensToComment.insert(tokenInfo.value);
    }
}

