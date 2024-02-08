#pragma once

#include <string> 

#include "models/analysis_report.h"
#include "models/token_info.h"

class CommentStrategyInterface{
    public: 
        
        virtual ~CommentStrategyInterface() = default;
        virtual std::string CommentText(const AnalysisReport &analysisReport, 
            const std::string &javascriptTokenValue) const  = 0;
        virtual bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const = 0; // New method


        std::string ReturnMessage(const std::string &text1, const std::string &text2, 
            bool specificCondition, const AnalysisReport &analysisReport) const {
                std::string returnText = "";
                const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
                const bool isLargeFilePresent = analysisReport.GetDetectionFlag(CLIENT::LARGE_FILE);

                if (isUseClientPresent && isLargeFilePresent 
                    && specificCondition) {
                        returnText += text1 + " \n";
                }
                if (!isUseClientPresent 
                    && specificCondition) {
                        returnText += text2  + " \n";
                }
                

                return returnText;
        }

};



