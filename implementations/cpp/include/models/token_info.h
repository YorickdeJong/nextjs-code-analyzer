#pragma once

#include <string>


struct TokenInfo {
    std::string value;
    int line;
    int start;
    int end;
};
