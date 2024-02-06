#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/other_strategies.h"
#include "reporter/chain/comment_strategy_chain_builder.h"



class UseClientStrategyTest : public ::testing::Test {
protected:
    CommentStrategyChain commentStrategy;
    ChainBuilder chainBuilder;
    AnalysisReport analysisReport;
    const std::string javascriptToken = "use client";
    std::string comments;

    void SetUp() override {

    }

    std::string LargeFileDetected() {
        return "Large file detected! Consider refactoring 'use client' into a smaller file";
    }

    std::string EmptyText() {
        return "";
    }

    std::string GetManyWords() {
        return "Client side file detected with many words. Consider refactoring for better SEO score \n";
    }

    std::string RemoveClient() {
        return "Consider removing use client from this file as no client side components have been detected \n";
    }


};




TEST_F(UseClientStrategyTest, ExecuteChain_WithStandardInput_ReturnsEmptyComments) {

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");
}


TEST_F(UseClientStrategyTest, ExecuteChain_LargeFileWithUseClient) {
    
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    analysisReport.manyWordsInFile = false;
    

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, largeFileDetected + " \n" + removeClient);

}

TEST_F(UseClientStrategyTest, ExecuteChain_LargeFileWithUseClientAndMayWords) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    analysisReport.manyWordsInFile = true;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }


    EXPECT_EQ(comments, largeFileDetected + " \n" + getManyWords + removeClient);

}


TEST_F(UseClientStrategyTest, ExecuteChain_LargeFileWithUseClientAndMayWordsAndHook) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = true;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }
    EXPECT_EQ(comments, largeFileDetected + " \n" + getManyWords);
}


TEST_F(UseClientStrategyTest, ExecuteChain_LargeFileMayWordsAndHook) {

    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = true;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}


TEST_F(UseClientStrategyTest, ExecuteChain_LargeFileUseClientHook) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = false;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, largeFileDetected + " \n");

}

TEST_F(UseClientStrategyTest, ExecuteChain_UseClientHook) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.hookDetected = true;
    analysisReport.manyWordsInFile = false;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}

TEST_F(UseClientStrategyTest, ExecuteChain_UseClient) {
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.hookDetected = false;
    analysisReport.manyWordsInFile = false;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, removeClient);

}