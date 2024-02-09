#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>

#include "models/analysis_report.h"
#include "analysis/analysis.h"

#include "reporter/strategy/use_client_strategy.h"
#include "reporter/strategy/comment_strategy_interface.h"



class UseEffectStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy;
    
    const std::string javascriptTokenValue = CLIENT_DESCRIPTIONS::USE_EFFECT_DESC;
    std::string comments;
    std::string textUseEffect;

    void SetUp() override {
    }

    std::string GetExpectedText1() {
        return "Consider refactoring " + javascriptTokenValue + " Large file detected";
    }

    std::string GetExpectedText2() {
        return "No use client detected, consider refactoring " + 
               javascriptTokenValue + " or add 'use client' to make this file client side";
    }

    std::string GetExpectedTextUseEffect() {
        return "If you are using an async await fetch in your useEffect, "
               "consider making this component server side and make this component async. Example: "
               "async function Component() {"
               "    const var = await fetchFunction();"
               "    return ("
               "        <div></div>"
               "    );"
               "}  \n";
    }
};

class UseStateStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy;
    
    const std::string javascriptTokenValue = CLIENT_DESCRIPTIONS::USE_STATE_DESC;
    std::string comments;
    std::string textUseEffect;


    void SetUp() override {
    }

    std::string GetExpectedText1() {
        return "Consider refactoring " + javascriptTokenValue + " Large file detected";
    }

    std::string GetExpectedText2() {
        return "No use client detected, consider refactoring " + 
               javascriptTokenValue + " or add 'use client' to make this file client side";
    }

    std::string GetExpectedTextUseEffect() {
        return "If you are using an async await fetch in your useEffect, "
               "consider making this component server side and make this component async. Example: "
               "async function Component() {"
               "    const var = await fetchFunction();"
               "    return ("
               "        <div></div>"
               "    );"
               "}  \n";
    }
};



TEST_F(UseEffectStrategyTest, useEffectWithUseClientAndLargeFile) {

    // Test Scenario: All flags set to true in an analysis report involving useEffect.
    // Expected Behavior: The return text should match the expected text for useClient and large file scenarios.
    // Rationale: Ensures that useClientStrategy correctly processes and returns messages when all relevant flags are active.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);

    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText1 + " \n");

    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && isUseClientPresent) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText1 + " \n" + textUseEffect);

}

TEST_F(UseEffectStrategyTest, useEffectWithoutUseClientAndLargeFile) {

    // Test Scenario: Large file and hook detected, but no useClient detected for useEffect.
    // Expected Behavior: Return text should include advice for large file handling without useClient specific message.
    // Rationale: Validates that useClientStrategy omits client-specific advice in the absence of the useClient flag.



    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);

    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText2 + " \n");

    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && isUseClientPresent) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText2 + " \n" + textUseEffect);

}


TEST_F(UseEffectStrategyTest, NoUseEffectAndUseClient) {

    // Test Scenario: Hook not detected for useEffect with large file detected and no use client.
    // Expected Behavior: Return text should be empty as no conditions are met for generating advice.
    // Rationale: Confirms that the absence of hook detection results in no advice being generated.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);

    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && isUseClientPresent) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, "");

}




TEST_F(UseStateStrategyTest, HookWithUseClientAndLargeFile) {

    // Test Scenario: useState hook detected with useClient and large file flags set.
    // Expected Behavior: Return text should include the expected message for a large file with use client.
    // Rationale: Verifies that useState scenarios correctly handle the combination of useClient and large file flags.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);

    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText1 + " \n");


    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && isUseClientPresent) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText1 + " \n");

}


TEST_F(UseStateStrategyTest, HookWithNoUseClientAndLargeFile) {

    // Test Scenario: useState hook and large file detected, but no useClient present.
    // Expected Behavior: Return text should only reflect the large file scenario without useClient-specific advice.
    // Rationale: Ensures that the absence of the useClient flag leads to omission of client-specific advice.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);


    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText2 + " \n");


    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && isUseClientPresent) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText2 + " \n");

}


TEST_F(UseStateStrategyTest, NoHookWithNoUseClientAndLargeFile) {
 
    // Test Scenario: Large file detected without useState hook and no useClient.
    // Expected Behavior: Return text should be empty as the primary condition (hook detection) is not met.
    // Rationale: Confirms that no advice is generated when the hook detection condition is not satisfied.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);

    const bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::HOOK);
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");


    if (javascriptTokenValue == CLIENT_DESCRIPTIONS::USE_EFFECT_DESC && isUseClientPresent) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, "");

}
