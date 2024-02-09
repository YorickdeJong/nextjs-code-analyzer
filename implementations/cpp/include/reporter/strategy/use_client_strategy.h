#pragma once

#include <string> 

#include "reporter/strategy/comment_strategy_interface.h"
/**
 * UseClientStrategy provides commentary based on the analysis of 'use client' usage
 * in NextJS JavaScript code.
 */
class UseClientStrategy : public CommentStrategyInterface {
    public:
        /**
         * Generates a comment based on the analysis report and a specific JavaScript token value.
         * This method overrides the pure virtual method from CommentStrategyInterface.
         * @param analysisReport The analysis report containing the detection flags.
         * @param javascriptTokenValue The JavaScript token value being analyzed.
         * @return A string containing the generated comment.
         */
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override;


        /**
         * Executes the 'use client' comment strategy for a specific JavaScript token.
         * This method overrides the pure virtual method from CommentStrategyInterface.
         * @param analysisReport The analysis report containing the detection flags.
         * @param comments Reference to a string where the generated comment will be stored.
         * @param javascriptTokenValue The JavaScript token value being analyzed.
         * @return A boolean indicating whether the strategy execution was successful.
         */
        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override;

         /**
         * Checks if all relevant values in the analysis report are false, indicating
         * that no relevant 'use client' patterns were detected.
         * @param analysisReport The analysis report containing the detection flags.
         * @return A boolean indicating whether all relevant values are false.
         */
        bool AllvaluesFalse(const AnalysisReport &analysisReport) const;
};
