#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "models/analysis_report.h"
#include "models/token_info.h"

// Analyzer is responsible for analyzing JSON data and setting a set of values
// based on the report findings. These values indicate what optimizations should
// be made and what report should be sent back to the user. Analyzer also keeps
// track of the code blocks which should be optimized by the optimizer

class Analyzer {


    public:
        Analyzer(): analysisResult(), tokenInfos() {};
        AnalysisResult Analyze(nlohmann::json &j); 
        void AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos);
        const AnalysisResult& GetAnalysisResult() const { return analysisResult; };
        const std::vector<TokenInfo>& GetTokenInfos() const { return tokenInfos; };

    private:    
        AnalysisResult analysisResult; 
        std::vector<TokenInfo> tokenInfos;


};