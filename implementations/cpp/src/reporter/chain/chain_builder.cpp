#include "reporter/chain/chain_builder.h"


/**
 * Constructs the chain by sequentially adding specific strategies.
 * The order of addition determines the order of strategy execution in the chain.
 */
void ChainBuilder::BuildChain() {
    // Directly initializing each strategy in the array
    m_Strategies[0] = std::make_unique<UseClientStrategy>();
    m_Strategies[1] = std::make_unique<HookStrategy>();
    m_Strategies[2] = std::make_unique<WindowStrategy>();
    m_Strategies[3] = std::make_unique<DocumentStrategy>();
    // m_Strategies[4] = std::make_unique<DynamicStrategy>();
    m_Strategies[4] = std::make_unique<LocalStorageStrategy>();
    m_Strategies[5] = std::make_unique<RouterStrategy>();
    m_Strategies[6] = std::make_unique<EventStrategy>();
    m_Strategies[7] = std::make_unique<ButtonStrategy>();
    m_Strategies[8] = std::make_unique<HtmlStrategy>();
}

const std::array<std::unique_ptr<CommentStrategyInterface>, 9>& ChainBuilder::GetStrategies() const { 
    return m_Strategies; 
}