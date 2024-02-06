#pragma once
#include "reporter/patterns/comment_strategy_interface.h"
#include <string> 
#include <regex>



class UseClientStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {
            const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
            const std::string text2 = "";
            bool isUseClientPresent = analysisReport.useClientDetected;

            std::string returnText = ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
            
            if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
                    returnText += "\n Client side file detected with many words. Consider refactoring for better SEO score";
            }

            if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
                    && AllvaluesFalse(analysisReport)) { 
                    returnText += "Consider removing use client from this file as no client side components have been detected";

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
            return !(analysisReport.hookDetected || analysisReport.manyWordsInFile || analysisReport.windowDetected 
                || analysisReport.documentDetected
                || analysisReport.buttontDetected || analysisReport.eventDetected || analysisReport.routerDetected 
                || analysisReport.localDetected || analysisReport.dynamicDetected);
        }
};



class HookStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            

            bool specificCondition = analysisReport.hookDetected;
            

            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            
            if (javascriptTokenValue == "useEffect") {
                returnText += "If you are using an async await fetch in your useEffect, "
                  "consider making this component server side and make this component async. Example: "
                  "async function Component() {"
                  "    const var = await fetchFunction();"
                  "    return ("
                  "        <div></div>"
                  "    );"
                  "}";
            }

            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                std::regex re("use[A-Z]\\w*");
                std::smatch match;
                std::cout << "TOKEN" << javascriptTokenValue << std::endl;
                if ( std::regex_search(javascriptTokenValue, match, re) && 
                     javascriptTokenValue != "use client"
                    ) {
                        comments = CommentText(analysisReport, javascriptTokenValue);
                        return false;
                }

                // Continue to next strategy
                return false;
        }

};


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

                // Continue to next strategy
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

                // Continue to next strategy
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

                // Continue to next strategy
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

                // Continue to next strategy
                return true;
        }
};
