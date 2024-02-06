#include "analysis/analysis.h"





void Analyzer::Analyze(nlohmann::json &j) {

    std::cout << "Analyzing JSON object" << j["loc"]["end"]["line"] << std::endl;
    
    

    InitAnalyseResult(j);

    for (auto& token : j["tokens"]) {
        


        if (!token.contains("value") || !token["value"].is_string()) {
            continue;
        }

        const std::string &value = token["value"];

        if (value == "use client"){
            
            AddTokenInfo(token, m_tokenInfos);
            m_analysisResult.useClientDetected = true;
            continue;
        }

        if (value.find("use") != std::string::npos) {
            AddTokenInfo(token, m_tokenInfos);
            m_analysisResult.hookDetected = true;
        }

    }
}


void Analyzer::AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos) {
    TokenInfo info;
    info.value = token["value"].get<std::string>();
    info.line = token["loc"]["start"]["line"];
    info.start = token["loc"]["start"]["index"];
    info.end = token["loc"]["end"]["index"];
    tokenInfos.emplace_back(info);
}


void Analyzer::InitAnalyseResult(nlohmann::json &j) {
    m_analysisResult.useClientDetected = false;
    m_analysisResult.hookDetected = false;
    m_analysisResult.largeFileDetected = j["loc"]["end"]["line"] > 99;
    m_analysisResult.manyWordsInFile = false;

    // Determine if file contains to many words, which is bad for SEO
    int count = 0;
    for (auto &token : j["tokens"]) {
        if (token["type"].contains("label") && token["type"]["label"] == "jsxText") {
            count += 1;    
        }
    }

    if (count > 30) {
        m_analysisResult.manyWordsInFile = true;
    }

}
