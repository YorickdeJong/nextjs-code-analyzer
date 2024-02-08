#include "analysis/analysis.h"





void Analyzer::AnalyzeJson(const nlohmann::json &j) {


    if (!j.contains("tokens")) {
        throw std::runtime_error("Invalid token structure: 'tokens' is missing.");
    }
    
    InitAnalyseResult(j);


    for (auto& token : j["tokens"]) {
        
        if (!token.contains("value") || !token["value"].is_string()) {
            continue;
        }

        const std::string &value = token["value"];

        AddTokenInfo(token, m_tokenInfos, value);

    }
}




void Analyzer::AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
    const std::string &value
) {
    if (!token.contains("loc") || !token["loc"]["start"].contains("line")) {
        throw std::runtime_error("Invalid token structure: 'loc' or 'line' missing.");
    }

    auto keyOpt = m_analysisResult.FindKeyByDescription(value);
    
    //return if key is not found
    if (!keyOpt.has_value()) {
        return;
    }
    
    // Use the key value
    const std::string& key = keyOpt.value();
    m_analysisResult.SetDetectionFlag(key, true);


    TokenInfo info;
    info.value = token["value"].get<std::string>();
    info.line = token["loc"]["start"]["line"];
    info.startIndex = token["loc"]["start"]["index"];
    info.endIndex = token["loc"]["end"]["index"];
    tokenInfos.emplace_back(info);

}

// void Analyzer::AddTokenInfoHooks(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
//     const std::string &value
// ) {
//     if (!token.contains("loc") || !token["loc"]["start"].contains("line")) {
//             throw std::runtime_error("Invalid token structure: 'loc' or 'line' missing.");
//     }
    
//     std::regex re("use[A-Z]\\w*");
//     std::smatch match;
        
//     if (std::regex_search(value, match, re) && 
//                      value == "use client") {

//         const std::string key = m_analysisResult.FindKeyByDescription(value);
//         m_analysisResult.SetDetectionFlag(key, true);
    
//         TokenInfo info;
//         info.value = token["value"].get<std::string>();
//         info.line = token["loc"]["start"]["line"];
//         info.start = token["loc"]["start"]["index"];
//         info.end = token["loc"]["end"]["index"];
//         tokenInfos.emplace_back(info);
//     }
// }


void Analyzer::InitAnalyseResult(const nlohmann::json &j) {

    if (!j["loc"]["start"].contains("line")) {
        throw std::runtime_error("Invalid token structure: 'tokens' is missing.");
    }

    // Check for large file
    const bool largeFile = j["loc"]["end"]["line"] > 99;
    m_analysisResult.SetDetectionFlag(CLIENT::LARGE_FILE, largeFile);

    // Determine if file contains to many words, which is bad for SEO
    int count = 0;
    for (auto &token : j["tokens"]) {
        if (token["type"].contains("label") && token["type"]["label"] == "jsxText") {
            count += 1;    
        }
    }

    if (count > 30) {
        m_analysisResult.SetDetectionFlag(CLIENT::MANY_WORDS, false);
    }

}
