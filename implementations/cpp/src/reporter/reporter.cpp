
#include "reporter/reporter.h"


Reporter::Reporter(const AnalysisResult &_analysisResult, 
const std::vector<TokenInfo> &_tokenInfo) 
: analysisResult{_analysisResult}, tokenInfos{_tokenInfo}
{
}


void Reporter::AddCommentsToJsonObject(nlohmann::json &j){
    std::unordered_set<std::string> tokensToComment;

    if (analysisResult.useClientDetected && analysisResult.hookDetected && analysisResult.largeFileDetected) {
        PopulateTokensToComment(tokenInfos, tokensToComment);
        AddCommentTokens(j, tokensToComment);
    }
    else if (analysisResult.useClientDetected  && ! analysisResult.hookDetected) {
        std::cout << "No hook detected, consider removing use client" << std::endl;
    }
    else if (!analysisResult.useClientDetected &&  analysisResult.hookDetected) {
        std::cout << "No use client detected, but detected hooks, consider adding useClient" << std::endl;
    }
    else {
        std::cout << "No use client detected" << std::endl;
    }
}



void Reporter::PopulateTokensToComment(const std::vector<TokenInfo> &tokenInfos, 
    std::unordered_set<std::string> &tokensToComment) {
    
    for (const auto& tokenInfo : tokenInfos) {
        tokensToComment.insert(tokenInfo.value);
    }
}

void Reporter::AddCommentTokens(nlohmann::json &j, 
    const std::unordered_set<std::string> &tokensToComment) {
    
    for (auto& jToken : j["tokens"]) {
        if (jToken.contains("value") && jToken["value"].is_string()) {
            const std::string& value = jToken["value"];

            // Add instructions for incorrect use of 'use client'
            if (tokensToComment.find(value) != tokensToComment.end() && 
                value == "use client"
            ) {
                CreateComment(jToken, "Large file detected with 'use client', Consider refactoring 'use client' into smaller files for better SEO score");
            }
            // Add instructions for incorrect use of 'use' hook instances 
            else if (tokensToComment.find(value) != tokensToComment.end()) {
                std::regex re("use[A-Z]\\w*");
                if (value.find(std::regex_search(value, re) && value != "use client")) {
                    CreateComment(jToken, "Consider refactoring " + value + " into a smaller file for better SEO score");
                }
            }  
        }
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
