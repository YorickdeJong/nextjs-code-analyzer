#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>

#include "models/analysis_report.h"
#include "analysis/analysis.h"
#include "utils/constants.h"
#include "reporter/reporter.h"
#include "reporter/strategy/use_client_strategy.h"
#include "reporter/strategy/comment_strategy_interface.h"

// UseClientStrategyTest is designed to test the behavior of UseClientStrategy::CommentText under various conditions.
// It checks how the strategy reacts to different states of an AnalysisReport, specifically focusing on
// scenarios with combinations of 'useClient', 'largeFile', and 'manyWordsInFile' flags.
// Each test case simulates a different combination of these flags and verifies the expected output from the strategy.

class UseClientStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
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


TEST_F(UseClientStrategyTest, largefileWithManyWordsAndUseClient) {

    // Test Scenario: Analysis report with useClient, largeFile, and manyWordsInFile flags set.
    // Expected Behavior: Return text should include advice for large file and many words.
    // Rationale: Validates that the strategy combines messages for both large file and many words scenarios.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);
    
    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, largeFileDetected + " \n");

    if (isManyWordsPresent && isUseClientPresent ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, largeFileDetected + " \n" + getManyWords);

    if (isUseClientPresent 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }

    EXPECT_EQ(returnText, largeFileDetected + " \n" + getManyWords + removeClient);

}


TEST_F(UseClientStrategyTest, manyWordsAndUseClient) {

    // Test Scenario: Analysis report with useClient and manyWordsInFile flags set, but no largeFile flag.
    // Expected Behavior: Return text should include advice for many words and a message to consider removing 'use client'.
    // Rationale: Checks the strategy's handling of a scenario where many words are detected in a client-used file.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (isManyWordsPresent && isUseClientPresent ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, getManyWords);

    if (isUseClientPresent
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, getManyWords + removeClient);

}


TEST_F(UseClientStrategyTest, returnEmpty) {

    // Test Scenario: Analysis report with manyWordsInFile flag set but without useClient and largeFile.
    // Expected Behavior: Return text should be empty as the crucial useClient condition is not met.
    // Rationale: Confirms that the strategy does not generate comments when the primary useClient condition is absent.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (isManyWordsPresent && isUseClientPresent ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, "");

    if (isUseClientPresent 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, "");

}


TEST_F(UseClientStrategyTest, removeClient) {
 
    // Test Scenario: Analysis report with only the useClient flag set.
    // Expected Behavior: Return text should suggest removing 'use client' as no other conditions are met.
    // Rationale: Ensures that the strategy advises removal of 'use client' when it is unnecessary.
    

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (isManyWordsPresent && isUseClientPresent ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, "");


    if (isUseClientPresent 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, removeClient);

}


TEST_F(UseClientStrategyTest, largeFile) {

    // Test Scenario: Analysis report with useClient and largeFile flags set, but no manyWordsInFile.
    // Expected Behavior: Return text should include advice for large file scenario.
    // Rationale: Verifies the strategy's ability to provide correct advice for large files in the presence of useClient.
    
    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, largeFileDetected + " \n");

    
    if (isManyWordsPresent && isUseClientPresent ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, largeFileDetected + " \n");

    if (isUseClientPresent 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, largeFileDetected + " \n" + removeClient);

}