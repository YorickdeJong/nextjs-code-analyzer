#pragma once
#include "reporter/strategy/comment_strategy_interface.h"
#include <string> 


class WindowStrategy : public CommentStrategyInterface {
    public:   
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            
            bool specificCondition = analysisReport.windowDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }

       bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "window") {
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
            
            bool specificCondition = analysisReport.documentDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "document") {
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
            
            bool specificCondition = analysisReport.dynamicDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "dynamic") {
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
            
            bool specificCondition = analysisReport.localDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "local") {
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
            
            bool specificCondition = analysisReport.routerDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "router") {
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
            
            bool specificCondition = analysisReport.eventDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "event") {
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
            
            bool specificCondition = analysisReport.buttontDetected;
            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            return returnText;
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                if (javascriptTokenValue == "button") {
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false;
                }

                return true;
        }
};
