#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "models/analysis_report.h"
#include "models/token_info.h"
#include "analysis/analysis.h"
#include "utils/constants.h"


TEST(AnalysisTest, useClientAndHooks) {
    Analyzer analyzer;
    nlohmann::json inputJson = {
        {"loc", {{"start", {{"line", 0}, {"index", 0}}}, {"end", {{"line", 1}, {"index", 10}}}}},
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
                {"value", CLIENT_DESCRIPTIONS::USE_CLIENT_DESC}
            },
            {
                {"end", 23},
                {"loc", {{"start", {{"line", 1}, {"index", 11}}}, {"end", {{"line", 1}, {"index", 23}}}}},
                {"start", 11},
                {"type", "Keyword"},
                {"value", CLIENT_DESCRIPTIONS::USE_STATE_DESC}
            },
        }}
    };

    analyzer.AnalyzeJson(inputJson);

    // check AddTokenInfo
    EXPECT_EQ(analyzer.GetTokenInfos().size(), 2u);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].value, CLIENT_DESCRIPTIONS::USE_CLIENT_DESC);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].line, 1);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].startIndex, 11);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].endIndex, 23);

    // check analysis Report
    EXPECT_EQ(analyzer.GetDetectionFlag(CLIENT::USE_CLIENT), true);
    EXPECT_EQ(analyzer.GetDetectionFlag(CLIENT::HOOK), true);
}

TEST(AnalysisTest, Hooks) {
    Analyzer analyzer;
    nlohmann::json inputJson = {
        {"loc", {{"start", {{"line", 0}, {"index", 0}}}, {"end", {{"line", 1}, {"index", 10}}}}},
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
                {"value", CLIENT_DESCRIPTIONS::USE_STATE_DESC}
            },
            // Add other tokens as needed
        }}
    };  

    analyzer.AnalyzeJson(inputJson);


    // check AddTokenInfo
    EXPECT_EQ(analyzer.GetTokenInfos().size(), 1u);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].value, CLIENT_DESCRIPTIONS::USE_STATE_DESC);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].line, 1);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].startIndex, 11);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].endIndex, 23);

    // check analysis report
    EXPECT_EQ(analyzer.GetDetectionFlag(CLIENT::HOOK), true);
}

TEST(AnalysisTest, useClient) {
    Analyzer analyzer;
    nlohmann::json inputJson = {
        {"loc", {{"start", {{"line", 0}, {"index", 0}}}, {"end", {{"line", 1}, {"index", 10}}}}},
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
                {"value", CLIENT_DESCRIPTIONS::USE_CLIENT_DESC}
            },
        }}
    };

    analyzer.AnalyzeJson(inputJson);

    // check AddTokenInfo
    EXPECT_EQ(analyzer.GetTokenInfos().size(), 1u);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].value, CLIENT_DESCRIPTIONS::USE_CLIENT_DESC);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].line, 1);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].startIndex, 11);
    EXPECT_EQ(analyzer.GetTokenInfos()[0].endIndex, 23);

    // check analysis report
    EXPECT_EQ(analyzer.GetDetectionFlag(CLIENT::USE_CLIENT), true);
}

