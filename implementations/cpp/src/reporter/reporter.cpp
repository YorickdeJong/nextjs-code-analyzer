
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

    const nlohmann::json &jsonObject = jsonManager.GetJson();
    for (size_t i = 0; i < jsonObject["tokens"].size(); ++i) {
        const auto& jToken = jsonObject["tokens"][i];
        if (!jToken.contains("value") || !jToken["value"].is_string()) {
            continue;
        }

        std::string javascriptTokenValue = jToken["value"];
        if (tokensToComment.find(javascriptTokenValue) == tokensToComment.end()) {
            continue;
        }

        std::string comments = commentStrategyChain.ExecuteChain(chainBuilder, m_analysisReport, javascriptTokenValue);
        
        jsonManager.ModifyJsonObject(i, comments);
    }
    
}



void Reporter::PopulateTokensToComment(const std::vector<TokenInfo> &m_tokenInfos, 
    std::unordered_set<std::string> &tokensToComment) {
    
    for (const auto& tokenInfo : m_tokenInfos) {
        tokensToComment.insert(tokenInfo.value);
    }
}

