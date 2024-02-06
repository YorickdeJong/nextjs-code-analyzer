#pragma once
#include "reporter/strategy/comment_strategy_interface.h"
#include <string> 



class UseClientStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {
            const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
            const std::string text2 = "";
            bool isUseClientPresent = analysisReport.useClientDetected;

            std::string returnText = ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
            
            if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
                    returnText += "Client side file detected with many words. Consider refactoring for better SEO score \n";
            }

            if (analysisReport.useClientDetected
                    && AllvaluesFalse(analysisReport)) { 
                    returnText += "Consider removing use client from this file as no client side components have been detected \n";

            }
            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (analysisReport.useClientDetected && javascriptTokenValue == "use client") {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                        return false;
                }
                return true;
        }

        bool AllvaluesFalse(const AnalysisReport &analysisReport) const {
            return !(analysisReport.hookDetected || analysisReport.windowDetected 
                || analysisReport.documentDetected || analysisReport.buttontDetected || 
                    analysisReport.eventDetected || analysisReport.routerDetected 
                || analysisReport.localDetected || analysisReport.dynamicDetected);
        }
};
