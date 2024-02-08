#pragma once

#include <vector>

#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/use_client_strategy.h"
#include "reporter/strategy/other_strategies.h"


/**
 * ChainBuilder is responsible for assembling a sequence of comment strategies.
 * It initializes the chain with the required strategies on construction.
 */
class ChainBuilder {
    public: 

        /**
         * Constructor for ChainBuilder that initializes the chain of strategies.
         */
        ChainBuilder() {
            BuildChain();
        }

        /**
         * Retrieves the collection of strategies that have been built.
         * @return A constant reference to a vector of unique pointers to CommentStrategyInterface.
         */
        const std::vector<std::unique_ptr<CommentStrategyInterface>>& GetStrategies() const { 
            return m_Strategies; 
        }

    private:
        std::vector<std::unique_ptr<CommentStrategyInterface>> m_Strategies;

        void BuildChain();
        void AddStrategy(std::unique_ptr<CommentStrategyInterface> strategy);
};