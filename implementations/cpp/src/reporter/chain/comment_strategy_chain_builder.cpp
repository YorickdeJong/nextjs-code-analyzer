#include "reporter/chain/comment_strategy_chain_builder.h"


/**
 * Iterates through the strategies provided by the ChainBuilder and executes them.
 * If a strategy returns false, it stops the chain and returns the comments gathered so far.
 */
std::string CommentStrategyChain::ExecuteChain(const ChainBuilder& builder, const AnalysisReport& analysisReport, 
                                                const std::string &javascriptTokenValue) {
    
    std::string comments = "";

    try {
        // Process each strategy to generate comments.
        for (const auto& strategy : builder.GetStrategies()) {
            if (strategy == nullptr) {
                throw std::invalid_argument("Encountered null strategy in chain.");
            } 
            if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
                break; // Stop processing if a strategy indicates completion.
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return comments;
}
