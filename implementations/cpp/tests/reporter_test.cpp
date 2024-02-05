#include "reporter/reporter.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include "analysis/analysis.h"
#include <iostream>
 
TEST(ReporterTest, AddCommentTokens) {
    nlohmann::json j = {
            {"value", "testValue"},
            {"loc", {
                {"start", {{"line", 1}, {"index", 0}}},
                {"end", {{"index", 10}}}
            }}
    };
    const int size_j = j.size();
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
    std::cout << "useclient " << analyzer.GetAnalysisResult().useClientDetected << std::endl;
    std::cout << "hook " << analyzer.GetAnalysisResult().hookDetected << std::endl;
    std::cout << "analyzer " << analyzer.GetTokenInfos()[0].value << std::endl;

    Reporter reporter(analyzer.GetAnalysisResult(), analyzer.GetTokenInfos()); 
    reporter.AddCommentsToJsonObject(j);

    std::cout << j.dump(4) << std::endl;

    EXPECT_EQ(j.size(), size_j + 1);


}

