#include "analysis/analysis.h"





void Analyzer::AnalyzeJson(const nlohmann::json &j) {


    
    InitAnalyseResult(j);

    for (auto& token : j["tokens"]) {
        
        if (!token.contains("value") || !token["value"].is_string()) {
            continue;
        }

        const std::string &value = token["value"];

        AddTokenInfo(token, m_tokenInfos, value, CLIENT::USE_CLIENT, m_analysisResult.useClientDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::WINDOW, m_analysisResult.windowDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::DOCUMENT, m_analysisResult.documentDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::BUTTON, m_analysisResult.buttontDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::ONCLICK, m_analysisResult.onClickDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::EVENT, m_analysisResult.eventDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::ROUTER, m_analysisResult.routerDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::LOCAL, m_analysisResult.localDetected);
        AddTokenInfo(token, m_tokenInfos, value, CLIENT::DYNAMIC, m_analysisResult.dynamicDetected);
        AddTokenInfoHooks(token, m_tokenInfos, value, m_analysisResult.hookDetected);

    }
}




void Analyzer::AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
    const std::string &value, const std::string& compareValue, bool &analysisResultValue
) {
    if (value == compareValue){
        analysisResultValue = true;

        TokenInfo info;
        info.value = token["value"].get<std::string>();
        info.line = token["loc"]["start"]["line"];
        info.start = token["loc"]["start"]["index"];
        info.end = token["loc"]["end"]["index"];
        tokenInfos.emplace_back(info);
    }
}

void Analyzer::AddTokenInfoHooks(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
    const std::string &value, bool &analysisResultValue
) {
    std::regex re("use[A-Z]\\w*");
    std::smatch match;
        
    if (std::regex_search(value, match, re) && 
                     value != "use client") {

        analysisResultValue = true;

        TokenInfo info;
        info.value = token["value"].get<std::string>();
        info.line = token["loc"]["start"]["line"];
        info.start = token["loc"]["start"]["index"];
        info.end = token["loc"]["end"]["index"];
        tokenInfos.emplace_back(info);
    }
}


void Analyzer::InitAnalyseResult(const nlohmann::json &j) {
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
