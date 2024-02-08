#include "reporter/chain/comment_strategy_chain_builder.h"


/**
 * Iterates through the strategies provided by the ChainBuilder and executes them.
 * If a strategy returns false, it stops the chain and returns the comments gathered so far.
 */
std::string CommentStrategyChain::ExecuteChain(const ChainBuilder& builder, const AnalysisReport& analysisReport, 
                                                const std::string &javascriptTokenValue) {
    
    std::string comments;
    // Process each strategy to generate comments.
    for (const auto& strategy : builder.GetStrategies()) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Stop processing if a strategy indicates completion.
        }
    }
    return comments;
}
