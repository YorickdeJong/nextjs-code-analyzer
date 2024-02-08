#pragma once

#include <string>


struct TokenInfo {
    std::string value;
    int line;
    int startIndex;
    int endIndex;
};
