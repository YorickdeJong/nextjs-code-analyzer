#pragma once

#include <string>
#include <vector>
#include <optional>

// Use optional for fields that may or may not have a value
struct AnalysisReport {
    bool useClientDetected;
    bool hookDetected;
    bool largeFileDetected;

    // Add more fields as needed
    // ...

    // Consider using nested structs or classes for more complex data
    struct DetailedResult {
        // Detailed fields
    };

    std::vector<DetailedResult> detailedResults;
};
