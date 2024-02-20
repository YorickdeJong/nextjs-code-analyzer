#include "reporter/strategy/use_client_strategy.h"

/**
 * Generates a comment based on the presence of 'use client' and related flags within the analysis report.
 */
std::string UseClientStrategy::CommentText(const AnalysisReport &analysisReport, 
    const std::string &javascriptTokenValue) const  {

    const std::string text1 = "Large client-side file detected! Consider splitting the current 'use client' file" 
        "into smaller modules. This can improve performance by reducing load times and optimizing resource usage."
        "Review and refactor variables and instances where feasible.\n";
    const std::string text2 = "";
    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    const bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    std::string returnText = ReturnMessage(text1, text2, isUseClientPresent, analysisReport);

    if (isManyWordsPresent && isUseClientPresent) {
        returnText += "Client-side file with a high word count detected. Large amounts of text"
        "can negatively impact SEO and user experience. Consider breaking down the text into smaller," 
        "more manageable components, or using server-side rendering for large text elements. \n";
    }

    if (isUseClientPresent && AllvaluesFalse(analysisReport)) { 
        returnText += "Unnecessary use of 'use client' detected. No client-side components or dependencies`"
        "are identified in this file. Removing 'use client' can streamline your"
        "code and improve server-side rendering efficiency.\n";

    }

    return returnText;
}

/**
 * Executes the 'use client' strategy, determining whether to generate a comment based on the token value.
 */
bool UseClientStrategy::ExecuteStrategy(const AnalysisReport &analysisReport, 
    std::string &comments, const std::string &javascriptTokenValue) const  {

    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);

    if (isUseClientPresent && javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_CLIENT_DESC) {
        
        // Generate and assign the comment for this token
        comments = CommentText(analysisReport, javascriptTokenValue);
        return false; // Stop further processing as a comment has been assigned.
    }

    // Go to the next strategy in the array
    return true;
}

/**
 * Checks if all client-related flags are false in the analysis report, indicating no client-side components.
 */
bool UseClientStrategy::AllvaluesFalse(const AnalysisReport &analysisReport) const {
    const bool isHookPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const bool isWindowPresent = analysisReport.GetDetectionFlag(CLIENT::WINDOW);
    const bool isDocumentPresent = analysisReport.GetDetectionFlag(CLIENT::DOCUMENT);
    const bool isButtonPresent = analysisReport.GetDetectionFlag(CLIENT::BUTTON);
    const bool isRouterPresent = analysisReport.GetDetectionFlag(CLIENT::ROUTER);
    const bool isLocalPresent = analysisReport.GetDetectionFlag(CLIENT::LOCAL);
    const bool isEventPresent = analysisReport.GetDetectionFlag(CLIENT::EVENT);

    return !(
        isHookPresent || isWindowPresent
        || isDocumentPresent || isButtonPresent 
        || isEventPresent || isRouterPresent 
        || isLocalPresent 
    );
}