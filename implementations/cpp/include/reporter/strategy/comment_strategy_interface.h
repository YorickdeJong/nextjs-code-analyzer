#pragma once

#include "models/analysis_report.h"
#include "models/token_info.h"
#include <string> 

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
                
                if (analysisReport.useClientDetected && analysisReport.largeFileDetected 
                    && specificCondition) {
                        returnText += text1 + " \n";
                }
                if (!analysisReport.useClientDetected 
                    && specificCondition) {
                        returnText += text2  + " \n";
                }
                

                return returnText;
        }

};



