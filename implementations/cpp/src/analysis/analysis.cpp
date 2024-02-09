#include "analysis/analysis.h"




/**
 * Analyzes the given JSON object for token information and populates the analysis results.
 * Throws a runtime_error if the expected 'tokens' structure is missing.
 * 
 * @param j The JSON object containing code token information to be analyzed.
 */ 
void Analyzer::AnalyzeJson(const nlohmann::json &j) {

    if (!j.contains("tokens")) {
        throw std::runtime_error("Invalid token structure: 'tokens' is missing.");
    }
    
    InitAnalyseResult(j);


    for (auto& token : j["tokens"]) {
        
        if (!token.contains("value") || !token["value"].is_string()) {
            continue;
        }

        // Add information about the token to the analysis results.
        const std::string &value = token["value"];
        AddTokenInfo(token, m_tokenInfos, value);

    }
    
}


/**
 * Adds information about a single token to the analysis results.
 * Throws a runtime_error if the token structure is invalid.
 * 
 * @param token The JSON object representing a single token.
 * @param tokenInfos The container that holds token information.
 * @param value The string value of the token.
 */
void Analyzer::AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
                            const std::string &value) 
{
    if (!token.contains("loc") || !token["loc"]["start"].contains("line")) {
        throw std::runtime_error("Invalid token structure: 'loc' or 'line' missing.");
    }

    // retrieve key value from value
    auto keyOpt = m_analysisResult.FindKeyByDescription(value);
    
    if (!keyOpt.has_value()) {
        return;
    }
    
    // Check if detected html element has type jsxName.
    if (keyOpt == CLIENT::HTML){
        if (token["type"]["label"] != "jsxName") {
            return;
        }
    }

    const std::string& key = keyOpt.value();
    m_analysisResult.SetDetectionFlag(key, true);

    // Create and populate a TokenInfo object, then add it to the tokenInfos vector.
    TokenInfo info;
    info.value = token["value"].get<std::string>();
    info.line = token["loc"]["start"]["line"];
    info.startIndex = token["loc"]["start"]["index"];
    info.endIndex = token["loc"]["end"]["index"];
    tokenInfos.emplace_back(info);

}


/**
 * Initializes the analysis result with flags based on the JSON content.
 * Throws a runtime_error if the JSON structure is missing required 'loc' or 'line' information.
 * 
 * @param j The JSON object containing the initial data for analysis.
 */
void Analyzer::InitAnalyseResult(const nlohmann::json &j) {

    if (!j["loc"]["start"].contains("line")) {
        throw std::runtime_error("Invalid token structure: 'tokens' is missing.");
    }

    // Check for large file
    const bool largeFile = j["loc"]["end"]["line"] > FILE_SPECS::WORD_COUNT;
    m_analysisResult.SetDetectionFlag(CLIENT::LARGE_FILE, largeFile);

    // Determine if file contains to many words, which should result in a refactor
    int count = 0;
    for (auto &token : j["tokens"]) {
        if (token["type"].contains("label") && token["type"]["label"] == "jsxText") {
            std::string value = token["value"];
            std::istringstream iss(value);
            std::string word;
            while (iss >> word) {
                ++count;
            }  
        }
    }

    const bool manyWords = count > FILE_SPECS::WORD_COUNT;
    m_analysisResult.SetDetectionFlag(CLIENT::MANY_WORDS, manyWords);

}
