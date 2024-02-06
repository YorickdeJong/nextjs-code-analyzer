#pragma once
#include "reporter/strategy/comment_strategy_interface.h"
#include <string> 
#include <regex>


class HookStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {
            const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
            const std::string text2 = "No use client detected, consider refactoring " + 
                javascriptTokenValue + " or add 'use client' to make this file client side";
            

            bool specificCondition = analysisReport.hookDetected;
            

            std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
            
            if ( javascriptTokenValue == "useEffect" && analysisReport.hookDetected ) {
                returnText += "If you are using an async await fetch in your useEffect, "
                  "consider making this component server side and make this component async. Example: "
                  "async function Component() {"
                  "    const var = await fetchFunction();"
                  "    return ("
                  "        <div></div>"
                  "    );"
                  "}  \n";
            }

            return returnText;
        }

        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                std::regex re("use[A-Z]\\w*");
                std::smatch match;
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