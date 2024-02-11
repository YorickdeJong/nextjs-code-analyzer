#include "reporter/strategy/hook_strategy.h"

/**
 * Constructs the comment for a hook strategy based on the token value and the analysis report.
 * Appends specific guidance for useEffect with async operations when applicable.
 */
std::string HookStrategy::CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const  {
    const std::string text1 = "Large file detected in '" + javascriptTokenValue + "'. Consider breaking down" 
                                "this file into smaller, more manageable components or using"
                                "dynamic imports to optimize performance and code maintainability.";

const std::string text2 = "No 'use client' detected in '" + 
    javascriptTokenValue + "'. If this file contains client-side specific code," 
    "consider adding 'use client' for clearer separation of client and server-side" 
    "code, enhancing code organization and performance.";
    

    bool specificCondition = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    std::string returnText = ReturnMessage(text1, text2, specificCondition, analysisReport);
    
    // Additional advice for useEffect with async operations.
    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && specificCondition) {
        returnText += "Detected 'useEffect' with async operations. For optimal performance and better handling of asynchronous" 
        "data fetching, consider moving this logic to a server-side function or using Next.js's async function <ComponentName>."
        "This can improve data loading efficiency and reduce client-side rendering delays.\n\nExample of server-side async function:\n  "
            "async function Component() {\n"
            "    const data = await fetchFunction();\n"
            "    return (\n"
            "        <div>{data}</div>\n"
            "    );\n"
            "}\n";
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

                // Generate and assign the comment for this token
                comments = CommentText(analysisReport, javascriptTokenValue);
                return false; // Stop further processing as a comment has been assigned.
        }

        // Go to the next strategy in the array
        return true;
}
