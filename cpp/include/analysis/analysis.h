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
};