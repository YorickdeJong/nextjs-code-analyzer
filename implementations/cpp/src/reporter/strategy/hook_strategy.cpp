#include "reporter/strategy/hook_strategy.h"

/**
 * Constructs the comment for a hook strategy based on the token value and the analysis report.
 * Appends specific guidance for useEffect with async operations when applicable.
 */
std::string HookStrategy::CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const  {
    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";
    
    
    bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
    
    // Additional advice for useEffect with async operations.
    if ( javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && specificCondition) {
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

/**
 * Executes the hook strategy by applying a regular expression to the JavaScript token value to identify hook usage.
 * If a hook is identified, it generates a comment and sets the comments parameter.
 */
bool HookStrategy::ExecuteStrategy(const AnalysisReport &analysisReport, 
    std::string &comments, const std::string &javascriptTokenValue) const  {
        std::regex re("use[A-Z]\\w*");
        std::smatch match;

        // If a hook pattern is identified, generate the comment.
        if ( std::regex_search(javascriptTokenValue, match, re) && 
                javascriptTokenValue != CLIENT_DESCRIPTIONS::USE_CLIENT_DESC
            ) {
                comments = CommentText(analysisReport, javascriptTokenValue);
                return false;
        }

        return true;
}
