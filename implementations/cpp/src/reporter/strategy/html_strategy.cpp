#include "reporter/strategy/html_strategy.h"


std::string HtmlStrategy::CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const {        
    // Check if both an HTML element is detected and the file contains many words.
    bool htmlElementDetected = analysisReport.GetDetectionFlag(CLIENT::HTML);
    bool manyWordsDetected = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    if (htmlElementDetected && manyWordsDetected) {
        return "A high word count has been detected in the HTML element <" + 
                javascriptTokenValue + 
                "> within a client-side file. This can impact SEO and page load times. Consider"
                "refactoring this content into smaller, more manageable components. Utilize server-side"
                "rendering for large text blocks or move them to a separate file to enhance performance and SEO effectiveness.";
    }
    return "";
}


bool HtmlStrategy::ExecuteStrategy(const AnalysisReport &analysisReport, 
    std::string &comments, const std::string &javascriptTokenValue) const {
        bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
        
        // Loop through known HTML elements to see if the token matches any.
        for (const std::string &htmlElement : HTML_ELEMENTS::HTML_ARRAY) {
            if (javascriptTokenValue == htmlElement && isUseClientPresent) {

                // Generate and assign the comment for this token
                comments = CommentText(analysisReport, javascriptTokenValue);
                return false; // Stop further processing as a comment has been assigned.
            }

        }

        // Go to the next strategy in the array
        return true;
} 