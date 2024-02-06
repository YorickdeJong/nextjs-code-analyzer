
#include "reporter/reporter.h"


Reporter::Reporter(const AnalysisReport &analysisReport, 
const std::vector<TokenInfo> &tokenInfo) 
: m_analysisReport{analysisReport}, m_tokenInfos{tokenInfo}
{
}


void Reporter::AddCommentsToJsonObject(nlohmann::json &j){
    std::unordered_set<std::string> tokensToComment;
    
    CommentStrategyChain commentStrategyChain;
    commentStrategyChain.ChainBuilder();
    PopulateTokensToComment(m_tokenInfos, tokensToComment);

    for (auto& jToken : j["tokens"]) {
        if (!jToken.contains("value") || !jToken["value"].is_string()) {
            continue; // Skip to the next iteration if conditions are not met
        }

        std::string javascriptTokenValue = jToken["value"];
        if (tokensToComment.find(javascriptTokenValue) == tokensToComment.end()) {
            continue; // Skip to the next iteration if value is not in tokensToComment
        }

        std::string comments = commentStrategyChain.ExecuteChain(m_analysisReport, javascriptTokenValue);
        std::cout << "main" << comments << std::endl;
        CreateComment(jToken, comments);
    }
    
}



void Reporter::PopulateTokensToComment(const std::vector<TokenInfo> &m_tokenInfos, 
    std::unordered_set<std::string> &tokensToComment) {
    
    for (const auto& tokenInfo : m_tokenInfos) {
        tokensToComment.insert(tokenInfo.value);
    }
}

void Reporter::CreateComment(nlohmann::json &jToken, 
    const std::string &commentText) {
    
    nlohmann::json comment;
    comment["value"] = commentText;
    comment["line"] = jToken["loc"]["start"]["line"];
    comment["start"] = jToken["loc"]["start"]["index"];
    comment["end"] = jToken["loc"]["end"]["index"];
    jToken["comment"] = comment;
}
