#include "reporter/chain/chain_builder.h"


/**
 * Constructs the chain by sequentially adding specific strategies.
 * The order of addition determines the order of strategy execution in the chain.
 */
void ChainBuilder::BuildChain() {
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

void ChainBuilder::AddStrategy(std::unique_ptr<CommentStrategyInterface> strategy) {
    m_Strategies.push_back(std::move(strategy));
}