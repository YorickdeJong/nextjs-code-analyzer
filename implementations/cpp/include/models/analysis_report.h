#pragma once

#include <string>
#include <vector>
#include <optional>

// Use optional for fields that may or may not have a value
struct AnalysisReport {
    bool useClientDetected = false;
    bool hookDetected = false;
    bool largeFileDetected = false;
    bool manyWordsInFile = false;
    bool windowDetected = false;
    bool documentDetected = false;
    bool buttontDetected = false;
    bool onClickDetected = false;
    bool eventDetected = false;
    bool routerDetected = false;
    bool localDetected = false;
    bool dynamicDetected = false;
};
