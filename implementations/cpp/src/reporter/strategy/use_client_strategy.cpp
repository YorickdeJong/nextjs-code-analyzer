#include "reporter/strategy/use_client_strategy.h"

/**
 * Generates a comment based on the presence of 'use client' and related flags within the analysis report.
 */
std::string UseClientStrategy::CommentText(const AnalysisReport &analysisReport, 
    const std::string &javascriptTokenValue) const  {

    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    const bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    std::string returnText = ReturnMessage(text1, text2, isUseClientPresent, analysisReport);

    if (isManyWordsPresent && isUseClientPresent) {
        returnText += "Client side file detected with many words. Consider refactoring for better SEO score \n";
    }

    if (isUseClientPresent && AllvaluesFalse(analysisReport)) { 
        returnText += "Consider removing use client from this file as no client side components have been detected \n";

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
        comments = CommentText(analysisReport, javascriptTokenValue);
        return false;
    }
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
    const bool isDynamicPresent = analysisReport.GetDetectionFlag(CLIENT::DYNAMIC);
    const bool isEventPresent = analysisReport.GetDetectionFlag(CLIENT::EVENT);

    return !(
        isHookPresent || isWindowPresent
        || isDocumentPresent || isButtonPresent 
        || isEventPresent || isRouterPresent 
        || isLocalPresent || isDynamicPresent 
    );
}