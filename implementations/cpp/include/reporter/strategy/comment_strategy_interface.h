#pragma once

#include <string> 

#include "models/analysis_report.h"
#include "models/token_info.h"


/**
 * CommentStrategyInterface is an abstract interface for implementing different comment strategies.
 * It defines the common interface that all comment strategies must implement.
 */

class CommentStrategyInterface{
    public: 
        
    virtual ~CommentStrategyInterface() = default;

    /**
     * Generates a comment text based on the analysis report and a specific JavaScript token.
     * @param analysisReport A reference to the analysis report containing detection flags.
     * @param javascriptTokenValue The value of the JavaScript token being analyzed.
     * @return A string containing the generated comment.
     */
    virtual std::string CommentText(const AnalysisReport &analysisReport, 
                                    const std::string &javascriptTokenValue) const = 0;

    /**
     * Executes the strategy for a specific JavaScript token.
     * @param analysisReport A reference to the analysis report containing detection flags.
     * @param comments Reference to a string where the generated comment will be stored.
     * @param javascriptTokenValue The value of the JavaScript token being analyzed.
     * @return A boolean indicating whether the strategy was executed successfully.
     */
    virtual bool ExecuteStrategy(const AnalysisReport &analysisReport, 
                                 std::string &comments, 
                                 const std::string &javascriptTokenValue) const = 0;

    /**
     * Utility function to construct a return message based on specific conditions.
     * @param text1 The message to return if both 'use client' and 'large file' flags are set.
     * @param text2 The message to return if 'use client' flag is not set.
     * @param specificCondition A boolean condition that affects the return message.
     * @param analysisReport A reference to the analysis report containing detection flags.
     * @return A string containing the appropriate return message based on the conditions.
     */
    std::string ReturnMessage(const std::string &text1, const std::string &text2, 
            bool specificCondition, const AnalysisReport &analysisReport) const {
                std::string returnText = "";
                const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
                const bool isLargeFilePresent = analysisReport.GetDetectionFlag(CLIENT::LARGE_FILE);

                if (isUseClientPresent && isLargeFilePresent 
                    && specificCondition) {
                        returnText += text1 + " \n";
                }
                if (!isUseClientPresent 
                    && specificCondition) {
                        returnText += text2  + " \n";
                }
                

                return returnText;
        }

};



