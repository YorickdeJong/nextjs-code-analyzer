#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "models/analysis_report.h"
#include "models/token_info.h"
#include <regex>
#include "utils/constants.h"

// Analyzer is responsible for analyzing JSON data and setting a set of values
// based on the report findings. These values indicate what optimizations should
// be made and what report should be sent back to the user. Analyzer also keeps
// track of the code blocks which should be optimized by the optimizer

class Analyzer {


    public:
        Analyzer(): m_analysisResult(), m_tokenInfos() {};
        void AnalyzeJson( const nlohmann::json &j ); 
        void AddTokenInfo( const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
            const std::string &value, const std::string& compareValue, bool &analysisResultValues );

        void AddTokenInfoHooks( const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos,
           const std::string &value, bool &analysisResultValue );

        const AnalysisReport& GetAnalysisResult() const { return m_analysisResult; };
        const std::vector<TokenInfo>& GetTokenInfos() const { return m_tokenInfos; };

    private:    
        void InitAnalyseResult(const nlohmann::json &j);

        AnalysisReport m_analysisResult; 
        std::vector<TokenInfo> m_tokenInfos;


};