#pragma once

#include <string> 
#include <regex>


#include "reporter/strategy/comment_strategy_interface.h"

/**
 * HookStrategy implements the strategy pattern for generating comments based on the analysis of hook usage.
 */
class HookStrategy : public CommentStrategyInterface {
public:
    /**
     * Generates a comment based on the token value and the analysis report.
     * @param analysisReport The analysis report containing detected flags.
     * @param javascriptTokenValue The value of the JavaScript token being analyzed.
     * @return A string containing the generated comment.
     */
    std::string CommentText(const AnalysisReport &analysisReport, 
        const std::string &javascriptTokenValue) const override;

    /**
     * Executes the comment generation strategy.
     * @param analysisReport The analysis report containing detected flags.
     * @param comments Reference to a string where the generated comment will be stored.
     * @param javascriptTokenValue The value of the JavaScript token being analyzed.
     * @return A boolean indicating whether the strategy was executed successfully.
     */
    bool ExecuteStrategy(const AnalysisReport &analysisReport, std::string &comments, 
        const std::string &javascriptTokenValue) const override;
};

