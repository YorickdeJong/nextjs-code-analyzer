#include "html_strategy.h"


std::string HtmlStrategy::CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const {        
    bool htmlElementDetected = analysisReport.GetDetectionFlag(CLIENT::HTML);
    bool manyWordsDetected = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    if (htmlElementDetected && manyWordsDetected) {
        return "Many Words in File detected in client side file. Consider refactoring <" + 
                javascriptTokenValue + 
                "> into a different file for better SEO. ";
    }
    return "";
}


bool HtmlStrategy::ExecuteStrategy(const AnalysisReport &analysisReport, 
    std::string &comments, const std::string &javascriptTokenValue) const {
        bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
        
        for (const std::string &htmlElement : HTML_ELEMENTS::HTML_ARRAY) {
            if (javascriptTokenValue == htmlElement && isUseClientPresent) {
                comments = CommentText(analysisReport, javascriptTokenValue);
                return false;
            }

        }

        return true;
} 