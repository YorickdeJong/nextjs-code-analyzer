#pragma once

#include <string> 

#include "reporter/strategy/comment_strategy_interface.h"

// UseClientStrategy return comments based on findings in the NextJS javascript code
class UseClientStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {
            const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
            const std::string text2 = "";
            const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
            const bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);
            
            std::string returnText = ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
            
            if (isManyWordsPresent && isUseClientPresent) {
                    returnText += "Client side file detected with many words. Consider refactoring for better SEO score \n";
            }

            if (isUseClientPresent
                    && AllvaluesFalse(analysisReport)) { 
                    returnText += "Consider removing use client from this file as no client side components have been detected \n";

            }
            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {

                const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
                if (isUseClientPresent && javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_CLIENT_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                        return false;
                }
                return true;
        }

        bool AllvaluesFalse(const AnalysisReport &analysisReport) const {
            const bool isHookPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
            const bool isWindowPresent = analysisReport.GetDetectionFlag(CLIENT::WINDOW);
            const bool isDocumentPresent = analysisReport.GetDetectionFlag(CLIENT::DOCUMENT);
            const bool isButtonPresent = analysisReport.GetDetectionFlag(CLIENT::BUTTON);
            const bool isRouterPresent = analysisReport.GetDetectionFlag(CLIENT::ROUTER);
            const bool isLocalPresent = analysisReport.GetDetectionFlag(CLIENT::LOCAL);
            const bool isDynamicPresent = analysisReport.GetDetectionFlag(CLIENT::DYNAMIC);
            const bool isEventPresent = analysisReport.GetDetectionFlag(CLIENT::EVENT);

            return !(isHookPresent || isWindowPresent
                || isDocumentPresent || isButtonPresent 
                || isEventPresent || isRouterPresent 
                || isLocalPresent || isDynamicPresent );
        }
};
