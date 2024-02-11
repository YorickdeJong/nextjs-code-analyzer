#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "models/analysis_report.h"
#include "models/token_info.h"
#include "analysis/analysis.h"
#include "utils/constants.h"

// This suite of tests is designed to validate the functionality of the Analyzer class.
// It checks whether the analyzer can correctly parse JSON input and detect various 
// client usage patterns and hooks based on the token information provided.

TEST(AnalysisTest, useClientAndHooks) {

    // Test Scenario: Analysis of JSON data representing code that uses client and hooks.
    // Expected Behavior: Analyzer should correctly identify and store information about the tokens related to client and hooks.
    // Rationale: Ensures the analyzer can detect the combined use of client descriptions and hook functions from JSON tokens.

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

    // Test Scenario: Analysis of JSON data representing code that uses hooks.
    // Expected Behavior: Analyzer should correctly identify and store information about the tokens related to hooks.
    // Rationale: Confirms that the analyzer can isolate and detect hook usage from JSON tokens, independent of other functionalities

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

    // Test Scenario: Analysis of JSON data representing code that uses the client descriptor.
    // Expected Behavior: Analyzer should correctly identify and store information about the tokens related to the client descriptor.
    // Rationale: Validates that the analyzer can detect the use of client descriptor from JSON tokens, ensuring accurate client usage reporting.
    
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

