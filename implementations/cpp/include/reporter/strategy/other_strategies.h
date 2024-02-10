#pragma once

#include <string> 

#include "reporter/strategy/comment_strategy_interface.h"

/**
 * RouterStrategy provides commentary based on the analysis of 'router' usage
 * in NextJS JavaScript code.
 */
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};

/**
 * DocumentStrategy provides commentary based on the analysis of 'document' usage
 * in NextJS JavaScript code.
 */
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};


/**
 * DynamicStrategy provides commentary based on the analysis of 'dynamic' usage
 * in NextJS JavaScript code.
 */
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};

/**
 * LocalStorageStrategy provides commentary based on the analysis of 'local' usage
 * in NextJS JavaScript code.
 */
class LocalStorageStrategy : public CommentStrategyInterface {
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};


/**
 * RouterStrategy provides commentary based on the analysis of 'router' usage
 * in NextJS JavaScript code.
 */
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};

/**
 * EventStrategy provides commentary based on the analysis of 'event' usage
 * in NextJS JavaScript code.
 */
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};


/**
 * ButtonStrategy provides commentary based on the analysis of 'button' usage
 * in NextJS JavaScript code.
 */
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

                    // Generate and assign the comment for this token
                    comments = CommentText(analysisReport, javascriptTokenValue);
                    return false; // Stop further processing as a comment has been assigned.
                }

                // Continue to next strategy
                return true;
        }
};
