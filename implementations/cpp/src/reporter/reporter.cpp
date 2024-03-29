
#include "reporter/reporter.h"


Reporter::Reporter(const AnalysisReport &analysisReport, 
const std::vector<TokenInfo> &tokenInfo) 
: m_analysisReport{analysisReport}, m_tokenInfos{tokenInfo}
{
}

void Reporter::AddCommentsToJsonObject(JsonManager& jsonManager){
    std::unordered_set<std::string> tokensToComment;
    ChainBuilder chainBuilder; 
    CommentStrategyChain commentStrategyChain;

    // Populate the set with tokens extracted from the analysis report.
    PopulateTokensToComment(m_tokenInfos, tokensToComment);

    const nlohmann::json &jsonObject = jsonManager.GetJson();
    for (size_t i = 0; i < jsonObject["tokens"].size(); ++i) {
        const auto& jToken = jsonObject["tokens"][i];

        if (!jToken.contains("value") || !jToken["value"].is_string()) {
            continue;
        }

        std::string javascriptTokenValue = jToken["value"];

        // If the current token's value is not in the set of tokens to comment, skip to the next one.
        if (tokensToComment.find(javascriptTokenValue) == tokensToComment.end()) {
            continue;
        }

        try {
            std::string comments = commentStrategyChain.ExecuteChain(chainBuilder, m_analysisReport, javascriptTokenValue);

            // Modify the JSON object with the generated comments for the current token.
            jsonManager.ModifyJsonObject(i, comments);
        }
        catch(const std::exception &e) {
            std::cerr << "Error processing token at" << i << ": " << e.what() << std::endl;
            continue;
        }
    }
}



void Reporter::PopulateTokensToComment(const std::vector<TokenInfo> &m_tokenInfos, 
                                       std::unordered_set<std::string> &tokensToComment) {

    for (const auto& tokenInfo : m_tokenInfos) {
        tokensToComment.insert(tokenInfo.value);
    }
}
