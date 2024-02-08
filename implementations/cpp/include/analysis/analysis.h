#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <regex>

#include "models/token_info.h"
#include "models/analysis_report.h"
#include "utils/constants.h"

// Analyzer is responsible for analyzing JSON data and setting a set of values
// based on the report findings. These values indicate what optimizations should
// be made and what report should be sent back to the user. Analyzer also keeps
// track of the code blocks which should be optimized by the optimizer

class Analyzer {


    public:
        Analyzer(): m_analysisResult(), m_tokenInfos() {};
        void AnalyzeJson( const nlohmann::json &j ); 
       

        const AnalysisReport& GetAnalysisResult() const { return m_analysisResult; };
        const std::vector<TokenInfo>& GetTokenInfos() const { return m_tokenInfos; };

        bool GetDetectionFlag(const std::string& key) {
            return m_analysisResult.GetDetectionFlag(key);
        }
        const std::string &GetStringValue(const std::string& key) const {
            return m_analysisResult.GetStringValue(key);
        }
        
        void SetDetectionFlag(const std::string& key, bool value) {
            m_analysisResult.SetDetectionFlag(key, value);
        }
    private:    
        void InitAnalyseResult(const nlohmann::json &j);
        
        void AddTokenInfo( const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
            const std::string &value);
        
        void AddTokenInfoHooks( const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
           const std::string &value);



        AnalysisReport m_analysisResult; 
        std::vector<TokenInfo> m_tokenInfos;


};