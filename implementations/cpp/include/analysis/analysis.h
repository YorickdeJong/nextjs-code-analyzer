#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <regex>
#include <sstream>

#include "models/token_info.h"
#include "models/analysis_report.h"
#include "utils/constants.h"
#include "utils/timer.h"

// Analyzer is responsible for analyzing JSON data and setting a set of values
// based on the report findings. These values indicate what optimizations should
// be made and what report should be sent back to the user. Analyzer also keeps
// track of the code blocks which should be optimized by the optimizer

class Analyzer {


    public:
        Analyzer(): m_analysisResult(), m_tokenInfos() {};
        /**
         * Analyzes a JSON object representing the code and populates the analysis results and token information.
         * @param j The JSON object to analyze.
         */
        void AnalyzeJson(const nlohmann::json &j);

        /**
         * Retrieves the analysis results.
         * @return A constant reference to the analysis report.
         */
        const AnalysisReport& GetAnalysisResult() const { return m_analysisResult; };

        /**
         * Retrieves the token information gathered during analysis.
         * @return A constant reference to the vector of token information.
         */
        const std::vector<TokenInfo>& GetTokenInfos() const { return m_tokenInfos; };

        /**
         * Retrieves the detection flag for a specific key from the analysis results.
         * @param key The key for the specific detection flag.
         * @return The boolean value of the detection flag.
         */
        bool GetDetectionFlag(const std::string& key) {
            return m_analysisResult.GetDetectionFlag(key);
        }

        /**
         * Retrieves the string value associated with a specific key in the analysis results.
         * @param key The key for the specific string value.
         * @return A constant reference to the string value.
         */
        const std::string &GetStringValue(const std::string& key) const {
            return m_analysisResult.GetStringValue(key);
        }

        /**
         * Sets a detection flag in the analysis report.
         * @param key The key for the specific detection flag.
         * @param value The boolean value to assign to the detection flag.
         */
        void SetDetectionFlag(const std::string& key, bool value) {
            m_analysisResult.SetDetectionFlag(key, value);
        }

    private:
        /**
         * Initializes the analysis result with the JSON object representing the code.
         * @param j The JSON object used for initializing the analysis result.
         */
        void InitAnalyseResult(const nlohmann::json &j);

        /**
         * Adds token information to the token information vector.
         * @param token The JSON object representing a single token in the code.
         * @param tokenInfos The vector where token information is being stored.
         * @param value The value of the token to add information for.
         */
        void AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos, const std::string &value);

        /**
         * Adds token information specifically for hooks to the token information vector.
         * @param token The JSON object representing a single token in the code.
         * @param tokenInfos The vector where token information is being stored.
         * @param value The value of the token to add information for.
         */
        void AddTokenInfoHooks(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos, const std::string &value);

        AnalysisReport m_analysisResult; 
        std::vector<TokenInfo> m_tokenInfos;


};