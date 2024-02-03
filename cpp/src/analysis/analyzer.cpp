#include "analysis/analysis.h"


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
            TokenInfo info;
            info.value = token["value"].get<std::string>();
            info.line = token["loc"]["start"]["line"];
            info.start = token["loc"]["start"]["index"];
            info.end = token["loc"]["end"]["index"];
            tokenInfos.emplace_back(info);
            
            useClient = true;
            continue;
        }

        if (useClient) {
            if (value.find("use") != std::string::npos) {
                TokenInfo info;
                
                info.value = token["value"].get<std::string>();
                info.line = token["loc"]["start"]["line"];
                info.start = token["loc"]["start"]["index"];
                info.end = token["loc"]["end"]["index"];
                tokenInfos.emplace_back(info);

                hook = true;
            }
        }
    }

    std::unordered_set<std::string> tokensToComment;

    if (useClient && hook && length) {
        for (const auto& tokenInfo : tokenInfos) {
            tokensToComment.insert(tokenInfo.value);
        }

        for (const auto& comment : tokensToComment) {
            std::cout << "Token to comment: " << comment << std::endl;
        }

        for (auto& jToken : j["tokens"]) {
            //  check if jToken contains "value" and it is a string
            if (jToken.contains("value") && jToken["value"].is_string()) {
                const std::string& value = jToken["value"];
                
                // Comapre
                if (tokensToComment.find(value) != tokensToComment.end() && value == "use client") {
                    // The value exists in our set, so we add the comment.
                    nlohmann::json comment;
                    comment["value"] = "Large file detected with 'use client', Consider refactoring 'use client' into smaller files for better SEO score";
                    comment["line"] = jToken["loc"]["start"]["line"];
                    comment["start"] = jToken["loc"]["start"]["index"];
                    comment["end"] = jToken["loc"]["end"]["index"];
                    // Assuming you want to add the comment as a string, not as an array of objects
                    jToken["comment"] = comment;
                }

                if (tokensToComment.find(value) != tokensToComment.end() && 
                    value.find("use") != std::string::npos && value != "use client"
                ) {
                    // The value exists in our set, so we add the comment.
                    nlohmann::json comment;
                    comment["value"] = "Consider refactoring " + value + " into a smaller file fo better SEO score";
                    comment["line"] = jToken["loc"]["start"]["line"];
                    comment["start"] = jToken["loc"]["start"]["index"];
                    comment["end"] = jToken["loc"]["end"]["index"];
                    // Assuming you want to add the comment as a string, not as an array of objects
                    jToken["comment"] = comment;
                }
            }

        }
        std::cout << "Hook detected with 'use client'" << std::endl;

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
