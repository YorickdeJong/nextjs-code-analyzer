#include "analysis/analysis.h"
#include <regex>


nlohmann::json Analyzer::Analyze(nlohmann::json &j) {
    nlohmann::json result;
    std::vector<TokenInfo> tokenInfos;
    std::cout << "Analyzing JSON object" << j["loc"]["end"]["line"] << std::endl;
    
    
    bool useClient = false;
    bool hook = false;
    bool length = j["loc"]["end"]["line"] > 99;

    for (auto& token : j["tokens"]) {
        
        if (!token.contains("value") || !token["value"].is_string()) {
            continue;
        }

        const std::string &value = token["value"];

        if (value == "use client"){
            
            AddTokenInfo(token, tokenInfos);
            useClient = true;
            continue;
        }

        if (useClient) {
            if (value.find("use") != std::string::npos) {
                AddTokenInfo(token, tokenInfos);
                hook = true;
            }
        }
    }

    std::unordered_set<std::string> tokensToComment;

    if (useClient && hook && length) {
        PopulateTokensToComment(tokenInfos, tokensToComment);
        AddCommentTokens(j, tokensToComment);
    }
    else if (useClient && !hook) {
        std::cout << "No hook detected, consider removing use client" << std::endl;
    }
    else if (!useClient && hook) {
        std::cout << "No use client detected, but detected hooks, consider adding useClient" << std::endl;
    }
    else {
        std::cout << "No use client detected" << std::endl;
    }
    return result;
}


void Analyzer::AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos) {
    TokenInfo info;
    info.value = token["value"].get<std::string>();
    info.line = token["loc"]["start"]["line"];
    info.start = token["loc"]["start"]["index"];
    info.end = token["loc"]["end"]["index"];
    tokenInfos.emplace_back(info);
}



void Analyzer::AddComment(nlohmann::json &jToken, const std::string &commentText) {
    nlohmann::json comment;
    comment["value"] = commentText;
    comment["line"] = jToken["loc"]["start"]["line"];
    comment["start"] = jToken["loc"]["start"]["index"];
    comment["end"] = jToken["loc"]["end"]["index"];
    jToken["comment"] = comment;
}


void Analyzer::PopulateTokensToComment(const std::vector<TokenInfo> &tokenInfos, std::unordered_set<std::string> &tokensToComment) {
    for (const auto& tokenInfo : tokenInfos) {
        tokensToComment.insert(tokenInfo.value);
    }
}

void Analyzer::AddCommentTokens(nlohmann::json &j, const std::unordered_set<std::string> &tokensToComment) {
    for (auto& jToken : j["tokens"]) {
        if (jToken.contains("value") && jToken["value"].is_string()) {
            const std::string& value = jToken["value"];

            // Add instructions for incorrect use of 'use client'
            if (tokensToComment.find(value) != tokensToComment.end() && 
                value == "use client"
            ) {
                AddComment(jToken, "Large file detected with 'use client', Consider refactoring 'use client' into smaller files for better SEO score");
            }
            // Add instructions for incorrect use of 'use' hook instances 
            else if (tokensToComment.find(value) != tokensToComment.end()) {
                std::regex re("use[A-Z]\\w*");
                if (value.find(std::regex_search(value, re) && value != "use client")) {
                    AddComment(jToken, "Consider refactoring " + value + " into a smaller file for better SEO score");
                }
            }  
        }
    }
}
