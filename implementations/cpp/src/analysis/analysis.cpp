#include "analysis/analysis.h"


void Analyzer::Analyze(nlohmann::json &j) {

    std::cout << "Analyzing JSON object" << j["loc"]["end"]["line"] << std::endl;
    
    
    m_analysisResult.useClientDetected = false;
    m_analysisResult.hookDetected = false;
    m_analysisResult.largeFileDetected = j["loc"]["end"]["line"] > 99;

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