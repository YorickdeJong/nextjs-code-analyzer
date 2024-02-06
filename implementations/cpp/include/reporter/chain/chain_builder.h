#pragma once

#include <vector>
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/other_strategies.h"



class ChainBuilder {
    public: 

        ChainBuilder() {
            BuildChain();
        }

        const std::vector<std::unique_ptr<CommentStrategyInterface>>& GetStrategies() const { 
            return m_Strategies; 
        }
    private:
        std::vector<std::unique_ptr<CommentStrategyInterface>> m_Strategies;

        void BuildChain() {
            AddStrategy(std::make_unique<UseClientStrategy>());
            AddStrategy(std::make_unique<HookStrategy>());
            AddStrategy(std::make_unique<WindowStrategy>());
            AddStrategy(std::make_unique<DocumentStrategy>());
            AddStrategy(std::make_unique<DynamicStrategy>());
            AddStrategy(std::make_unique<LocalStorageStragy>());
            AddStrategy(std::make_unique<RouterStrategy>());
            AddStrategy(std::make_unique<EventStrategy>());
            AddStrategy(std::make_unique<ButtonStrategy>());
        }

        void AddStrategy(std::unique_ptr<CommentStrategyInterface> strategy) {
            m_Strategies.push_back(std::move(strategy));
        }
};