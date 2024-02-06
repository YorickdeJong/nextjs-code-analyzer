#pragma once

#include <string>
#include <vector>
#include <optional>

// Use optional for fields that may or may not have a value
struct AnalysisReport {
    bool useClientDetected;
    bool hookDetected;
    bool largeFileDetected;
    bool manyWordsInFile;
    bool windowDetected;
    bool documentDetected;
    bool buttontDetected;
    bool eventDetected;
    bool routerDetected;
    bool localDetected;
    bool dynamicDetected;
};
