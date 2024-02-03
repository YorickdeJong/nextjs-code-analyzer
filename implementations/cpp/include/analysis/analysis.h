#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>

struct TokenInfo {
    std::string value;
    int line;
    int start;
    int end;
};


class Analyzer {
    public:
        nlohmann::json Analyze(nlohmann::json &j); 
        void AddComment(nlohmann::json &jToken, const std::string &commentText);
        void AddCommentTokens(nlohmann::json &j, const std::unordered_set<std::string> &tokensToComment);
        void PopulateTokensToComment(const std::vector<TokenInfo> &tokenInfos, std::unordered_set<std::string> &tokensToComment);
        void AddTokenInfo(const nlohmann::json &token, std::vector<TokenInfo> &tokenInfos);

};