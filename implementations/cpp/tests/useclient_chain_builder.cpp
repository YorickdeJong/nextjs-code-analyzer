#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/other_strategies.h"
#include "reporter/chain/comment_strategy_chain_builder.h"





TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_WithStandardInput_ReturnsEmptyComments) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    const std::string javascript_token = "use client";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}


TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_LargeFileWithUseClient) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    analysisReport.manyWordsInFile = false;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text1 + " \n" + removeUseClient);

}

TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_LargeFileWithUseClientAndMayWords) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    analysisReport.manyWordsInFile = true;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text1 + " \n" + manywords + removeUseClient);

}


TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_LargeFileWithUseClientAndMayWordsAndHook) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = true;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text1 + " \n" + manywords);
}


TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_LargeFileMayWordsAndHook) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = true;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}


TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_LargeFileUseClientHook) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = false;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text1 + " \n");

}

TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_UseClientHook) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = false;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}

TEST(CommentStrategyChainBuilderUseClient, ExecuteChain_UseClient) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.hookDetected = false;
    analysisReport.manyWordsInFile = false;
    const std::string javascript_token = "use client";


    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    const std::string manywords = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    const std::string removeUseClient = "Consider removing use client from this file as no client side components have been detected \n";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, removeUseClient);

}