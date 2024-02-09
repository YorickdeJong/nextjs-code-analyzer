#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>

#include "utils/constants.h"
#include "models/analysis_report.h"
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/use_client_strategy.h"
#include "reporter/strategy/other_strategies.h"
#include "reporter/chain/comment_strategy_chain_builder.h"



class UseClientStrategyTest : public ::testing::Test {
protected:
    CommentStrategyChain commentStrategy;
    ChainBuilder chainBuilder;
    AnalysisReport analysisReport;
    const std::string javascriptToken = CLIENT_DESCRIPTIONS::USE_CLIENT_DESC;
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

    // Test Scenario: Standard input with no specific flags set.
    // Expected Behavior: No comments should be generated as no conditions to trigger comment generation are met.
    // Rationale: Validates that the default state of the analysis report does not lead to unnecessary comments.

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");
}


TEST_F(UseClientStrategyTest, ExecuteChain_LargeFileWithUseClient) {
    
    // Test Scenario: Analysis report with useClient and largeFile flags set.
    // Expected Behavior: Comments should indicate large file detection and suggest refactoring 'use client'.
    // Rationale: Ensures the strategy correctly processes scenarios with both useClient and largeFile conditions met.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);

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

    // Test Scenario: Analysis report with useClient, largeFile flags, and manyWordsInFile set.
    // Expected Behavior: Comments should include suggestions for both large file and many words detection.
    // Rationale: Checks the strategy's ability to handle multiple flag conditions and provide combined advice.
    
    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);


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

    // Test Scenario: All flags set including useClient, largeFile, manyWordsInFile, and hookDetected.
    // Expected Behavior: Comments should reflect large file and many words detection, ignoring hook detection.
    // Rationale: Verifies strategy's response to multiple active flags, prioritizing large file and word count advice.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

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

    // Test Scenario: Analysis report with largeFile, manyWordsInFile, and hookDetected flags set, but no useClient.
    // Expected Behavior: No comments should be generated as the useClient flag, crucial for this strategy, is not set.
    // Rationale: Confirms that the strategy does not generate comments when the primary useClient condition is not met.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

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

    // Test Scenario: useClient, largeFile, and hookDetected flags set, but not manyWordsInFile.
    // Expected Behavior: Comments should only reflect the large file detection and not consider the hook.
    // Rationale: Validates that the strategy provides relevant advice for large files while ignoring irrelevant flags.
    

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);

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

    // Test Scenario: Analysis report with useClient and hookDetected set, but no largeFile or manyWordsInFile.
    // Expected Behavior: No comments should be generated as neither large file nor many words conditions are met.
    // Rationale: Ensures that the strategy remains silent in the absence of specific conditions despite useClient being set.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, false);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);


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

    // Test Scenario: Only useClient flag is set in the analysis report.
    // Expected Behavior: Comments should suggest removing 'use client' as no client-side components are detected.
    // Rationale: Verifies that the strategy provides advice to remove 'use client' when it's unnecessary.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, false);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);


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