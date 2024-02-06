#include <gtest/gtest.h>
#include "analysis/analysis.h"
#include "models/token_info.h"
#include "models/analysis_report.h"
#include <nlohmann/json.hpp>
#include "utils/client_side_constants.h"



TEST(AnalysisTest, addTokenInfoUseClient) {
    Analyzer analyze;
    std::vector<TokenInfo> tokenInfo;
    nlohmann::json token = {
            {"value", CLIENT::USE_CLIENT},
            {"loc", {
                {"start", {{"line", 1}, {"index", 0}}},
                {"end", {{"index", 10}}}
            }}
        };

    const std::string &value = token["value"]; 

    bool mock_useClientDetected = false;
    analyze.AddTokenInfo(token, tokenInfo, value, CLIENT::USE_CLIENT, mock_useClientDetected );

    EXPECT_EQ(tokenInfo.size(), 1u);
    EXPECT_EQ(tokenInfo[0].value, CLIENT::USE_CLIENT);
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
                {"value", CLIENT::USE_CLIENT}
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

    analyzer.AnalyzeJson(inputJson);


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

    analyzer.AnalyzeJson(inputJson);


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
                {"value", CLIENT::USE_CLIENT}
            },
            // Add other tokens as needed
        }}
    };

    analyzer.AnalyzeJson(inputJson);

    EXPECT_EQ(analyzer.GetAnalysisResult().useClientDetected, true);
}

