#include "reporter/reporter.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include "analysis/analysis.h"
#include <iostream>
 
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


    analyzer.AnalyzeJson(inputJson);
    Reporter reporter(analyzer.GetAnalysisResult(), analyzer.GetTokenInfos()); 
    reporter.AddCommentsToJsonObject(inputJson);

    EXPECT_EQ(inputJson.size(), inputJson.size());


}

