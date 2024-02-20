#pragma once

// #include <vector>
#include <array>


#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/use_client_strategy.h"
#include "reporter/strategy/html_strategy.h"
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
        const std::array<std::unique_ptr<CommentStrategyInterface>, 9>& GetStrategies() const;
    private:

        std::array<std::unique_ptr<CommentStrategyInterface>, 9> m_Strategies;

        void BuildChain();

};