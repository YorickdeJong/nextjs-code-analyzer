#pragma once

#include <string> 

#include "reporter/strategy/comment_strategy_interface.h"

class WindowStrategy : public CommentStrategyInterface {
    public:   
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::WINDOW);
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }

       bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::WINDOW_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }

                // Continue to next strategy
                return true;
        }
};

class DocumentStrategy : public CommentStrategyInterface {
    public:   
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::DOCUMENT);
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::DOCUMENT_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }

                // Continue to next strategy
                return true;
        }
};


class DynamicStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {   
     
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::DYNAMIC); 
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::DYNAMIC_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }

                // Continue to next strategy
                return true;
        }
};

class LocalStorageStragy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::LOCAL); 
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::LOCAL_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }
                return true;
        }
};

class RouterStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::ROUTER); 
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::ROUTER_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }
                return true;
        }
};

class EventStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::EVENT);
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::EVENT_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }

                return true;
        }
};


class ButtonStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::BUTTON);
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == CLIENT_DESCRIPTIONS::BUTTON_DESC) {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }

                return true;
        }
};
