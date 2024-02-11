#include <string> 

#include <iostream>
#include "reporter/strategy/comment_strategy_interface.h"
#include "utils/constants.h"



class HtmlStrategy : public CommentStrategyInterface {
    public:

         /**
         * Generates a comment based on the analysis report and the value of the JavaScript token.
         * 
         * @param analysisReport The analysis report containing detection flags.
         * @param javascriptTokenValue The value of the JavaScript token being analyzed.
         * @return A string containing the comment for the token. Returns an empty string if no comment is needed.
         */
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override;

        /**
         * Executes the HTML comment strategy on a given JavaScript token.
         * 
         * This method checks if the token is an HTML element and if 'use client' is present in the analysis.
         * If both conditions are met, it assigns a comment to the token.
         * 
         * @param analysisReport The analysis report containing detection flags.
         * @param comments A reference to a string where the generated comment will be stored.
         * @param javascriptTokenValue The value of the JavaScript token being analyzed.
         * @return False if a comment is generated (stopping further strategy processing), true otherwise.
         */
        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override;
};