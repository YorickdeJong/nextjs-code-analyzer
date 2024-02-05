#include <gtest/gtest.h>
#include "analysis/analysis.h"
#include "models/token_info.h"
#include "models/analysis_report.h"
#include <nlohmann/json.hpp>




TEST(AnalysisTest, AddTokenInfo) {
    Analyzer analyze;
    std::vector<TokenInfo> tokenInfo;
    nlohmann::json token = {
            {"value", "testValue"},
            {"loc", {
                {"start", {{"line", 1}, {"index", 0}}},
                {"end", {{"index", 10}}}
            }}
        };

    analyze.AddTokenInfo(token, tokenInfo);

    EXPECT_EQ(tokenInfo.size(), 1u);
    EXPECT_EQ(tokenInfo[0].value, "testValue");
    EXPECT_EQ(tokenInfo[0].line, 1);
    EXPECT_EQ(tokenInfo[0].start, 0);
    EXPECT_EQ(tokenInfo[0].end, 10);

}


TEST(AnalysisTest, useClientAndHooks) {
    Analyzer analyzer;
    nlohmann::json inputJson = {
        {"tokens", {
            {
                {"end", 10},
                {"loc", {{"start", {{"line", 1}, {"index", 0}}}, {"end", {{"line", 1}, {"index", 10}}}}},
                {"start", 0},
                {"type", "CommentLine"},
                {"value", "test.js"}
            },
            {
                {"end", 23},
                {"loc", {{"start", {{"line", 1}, {"index", 11}}}, {"end", {{"line", 1}, {"index", 23}}}}},
                {"start", 11},
                {"type", "Keyword"},
                {"value", "use client"}
            },
            {
                {"end", 23},
                {"loc", {{"start", {{"line", 1}, {"index", 11}}}, {"end", {{"line", 1}, {"index", 23}}}}},
                {"start", 11},
                {"type", "Keyword"},
                {"value", "useState"}
            },
        }}
    };

    analyzer.Analyze(inputJson);


    EXPECT_EQ(analyzer.GetAnalysisResult().useClientDetected, true);
    EXPECT_EQ(analyzer.GetAnalysisResult().hookDetected, true);
}

TEST(AnalysisTest, Hooks) {
    Analyzer analyzer;
    nlohmann::json inputJson = {
        {"tokens", {
            {
                {"end", 10},
                {"loc", {{"start", {{"line", 1}, {"index", 0}}}, {"end", {{"line", 1}, {"index", 10}}}}},
                {"start", 0},
                {"type", "CommentLine"},
                {"value", "test.js"}
            },
            {
                {"end", 23},
                {"loc", {{"start", {{"line", 1}, {"index", 11}}}, {"end", {{"line", 1}, {"index", 23}}}}},
                {"start", 11},
                {"type", "Keyword"},
                {"value", "useState"}
            },
            // Add other tokens as needed
        }}
    };

    analyzer.Analyze(inputJson);


    EXPECT_EQ(analyzer.GetAnalysisResult().hookDetected, true);
}

TEST(AnalysisTest, useClient) {
    Analyzer analyzer;
    nlohmann::json inputJson = {
        {"tokens", {
            {
                {"end", 10},
                {"loc", {{"start", {{"line", 1}, {"index", 0}}}, {"end", {{"line", 1}, {"index", 10}}}}},
                {"start", 0},
                {"type", "CommentLine"},
                {"value", "test.js"}
            },
            {
                {"end", 23},
                {"loc", {{"start", {{"line", 1}, {"index", 11}}}, {"end", {{"line", 1}, {"index", 23}}}}},
                {"start", 11},
                {"type", "Keyword"},
                {"value", "use client"}
            },
            // Add other tokens as needed
        }}
    };

    analyzer.Analyze(inputJson);

    EXPECT_EQ(analyzer.GetAnalysisResult().useClientDetected, true);
}