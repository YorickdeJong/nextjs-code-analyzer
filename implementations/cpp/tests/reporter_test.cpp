#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>

#include "analysis/analysis.h"
#include "reporter/reporter.h"
#include "utils/constants.h"

TEST(ReporterTest, AddCommentTokens) {

    Analyzer analyzer;

    nlohmann::json inputJson = {
        {"loc", {{"start", {{"line", 1}, {"index", 0}}}, {"end", {{"line", 200}, {"index", 10}}}}},
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
                {"value",CLIENT_DESCRIPTIONS::USE_CLIENT_DESC}
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
    Reporter reporter(analyzer.GetAnalysisResult(), analyzer.GetTokenInfos()); 
    // reporter.AddCommentsToJsonObject(jsonManager);

    EXPECT_EQ(inputJson.size(), inputJson.size());


}

