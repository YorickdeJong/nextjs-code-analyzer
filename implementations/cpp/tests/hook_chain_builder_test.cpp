#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>

#include "utils/constants.h"
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/use_client_strategy.h"
#include "reporter/strategy/other_strategies.h"
#include "reporter/chain/comment_strategy_chain_builder.h"


// UseEffectStrategyTest is responsible for testing the behavior of useEffect hooks
// within the analyzed JavaScript code. It verifies that appropriate comments are generated
// based on the detected use of useEffect, considering various flags like useClientDetected
// and largeFileDetected that simulate different code analysis scenarios. The function being
// tested is CommentStrategyChain::ExecuteChain.

class UseEffectStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport;
    UseClientStrategy useClientStrategy;
    ChainBuilder chainBuilder;
    const std::string javascriptTokenValue = CLIENT_DESCRIPTIONS::USE_EFFECT_DESC;
    std::string comments;

    void SetUp() override {
    }

    std::string GetExpectedText1() {
        return "Large file detected in '" + javascriptTokenValue + "'. Consider breaking down" 
                "this file into smaller, more manageable components or using"
                "dynamic imports to optimize performance and code maintainability.";
    }

    std::string GetExpectedText2() {
        return "No 'use client' detected in '" + 
            javascriptTokenValue + "'. If this file contains client-side specific code," 
            "consider adding 'use client' for clearer separation of client and server-side" 
            "code, enhancing code organization and performance.";
    }

    std::string GetExpectedTextUseEffect() {
        return "Detected 'useEffect' with async operations. For optimal performance and better handling of asynchronous" 
                "data fetching, consider moving this logic to a server-side function or using Next.js's async function <ComponentName>."
                "This can improve data loading efficiency and reduce client-side rendering delays.\n\nExample of server-side async function:\n  "
                    "async function Component() {\n"
                    "    const data = await fetchFunction();\n"
                    "    return (\n"
                    "        <div>{data}</div>\n"
                    "    );\n"
                    "}\n";
    }
};

class UseStateStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport;
    UseClientStrategy useClientStrategy;
    ChainBuilder chainBuilder;
    const std::string javascriptTokenValue = CLIENT_DESCRIPTIONS::USE_STATE_DESC;
    std::string comments;
    
    void SetUp() override {
    }

    std::string GetExpectedText1() {
        return "Large file detected in '" + javascriptTokenValue + "'. Consider breaking down" 
                "this file into smaller, more manageable components or using"
                "dynamic imports to optimize performance and code maintainability.";
    }

    std::string GetExpectedText2() {
        return "No 'use client' detected in '" + 
            javascriptTokenValue + "'. If this file contains client-side specific code," 
            "consider adding 'use client' for clearer separation of client and server-side" 
            "code, enhancing code organization and performance.";
    }

    std::string GetExpectedTextUseEffect() {
        return "Detected 'useEffect' with async operations. For optimal performance and better handling of asynchronous" 
                "data fetching, consider moving this logic to a server-side function or using Next.js's async function <ComponentName>."
                "This can improve data loading efficiency and reduce client-side rendering delays.\n\nExample of server-side async function:\n  "
                    "async function Component() {\n"
                    "    const data = await fetchFunction();\n"
                    "    return (\n"
                    "        <div>{data}</div>\n"
                    "    );\n"
                    "}\n";
    }
};



TEST_F(UseEffectStrategyTest, ExecuteChain_WithStandardInput_ReturnsEmptyComments) {
    
    // Test Scenario: Standard input without any flags triggered.
    // Expected Behavior: The comment chain should execute without generating any comments
    // because no conditions to add comments are met.
    // Rationale: This ensures that the analysis report doesn't generate false positives.

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}


TEST_F(UseEffectStrategyTest, ExecuteChain_WithUseClientAndLargeFileFlags) {

    // Test Scenario: Input with useClient and largeFile flags set to true.
    // Expected Behavior: Comments should remain empty as the useClient strategy does not
    // append any comments in this test setup.
    // Rationale: We expect no comments since the conditions for adding comments are not satisfied
    // even though flags are set, demonstrating conditional comment generation

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, false);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);

    
    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}

TEST_F(UseEffectStrategyTest, ExecuteChain_WithUseClientLargeFileAndUseEffectFlags) {
    
    // Test Scenario: All flags (useClientDetected, largeFileDetected, and hookDetected) are set to true.
    // Expected Behavior: The comments should include suggestions for both large file handling and using useEffect hook.
    // Rationale: This test ensures that when all relevant conditions are met, appropriate advice is generated for optimizing useEffect usage.
    
    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);

    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }
    EXPECT_EQ(comments, expectedText1 + " \n" + expectedTextUseEffect);

}


TEST_F(UseEffectStrategyTest, ExecuteChain_WithoutUseClientLargeFileAndUseEffectFlags) {
    
    // Test Scenario: Only largeFileDetected and hookDetected flags are set, excluding useClientDetected.
    // Expected Behavior: Comments should include advice related to large file and hook usage, but not for useClient.
    // Rationale: Validates that the absence of the useClient flag correctly omits client-specific advice.
    
        
    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);

    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, expectedText2 + " \n" + expectedTextUseEffect);

}

TEST_F(UseEffectStrategyTest, ExecuteChain_WithoutUseClientLargeFileAndWithoutUseEffectFlags) {

    // Test Scenario: Only largeFileDetected is set with useClientDetected and hookDetected being false.
    // Expected Behavior: No comments should be generated since hookDetected flag, crucial for this strategy, is false.
    // Rationale: Ensures that the strategy chain correctly halts when a necessary condition (hookDetected) is not met.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);


    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments,  "");

}


TEST_F(UseStateStrategyTest, ExecuteChain_WithUseClientLargeFileAndHookFlags) {

    // Test Scenario: All flags are set for useState strategy.
    // Expected Behavior: Comments should reflect advice for handling large files in the context of useState hook.
    // Rationale: Ensures that when useState is used in a large file with a client detected, relevant advice is given.

    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, true);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);

    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, expectedText1 + " \n");
}


TEST_F(UseStateStrategyTest, ExecuteChain_WithoutUseClientLargeFileAndHookFlags) {

    // Test Scenario: The largeFileDetected and hookDetected flags are set, but useClientDetected is false.
    // Expected Behavior: Comments should advise on handling large files, without client-specific advice.
    // Rationale: Validates that useState strategies provide correct advice when no client usage is detected.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, true);


    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, expectedText2 + " \n");
}


TEST_F(UseStateStrategyTest, ExecuteChain_WithoutUseClientLargeFileAndWithoutHookFlags) {

    // Test Scenario: Only largeFileDetected is true, and both useClientDetected and hookDetected are false.
    // Expected Behavior: No comments should be generated as the crucial hookDetected condition is not met.
    // Rationale: Confirms that the absence of hook detection correctly leads to no comments being generated.


    analysisReport.SetDetectionFlag(CLIENT::USE_CLIENT, false);
    analysisReport.SetDetectionFlag(CLIENT::LARGE_FILE, true);
    analysisReport.SetDetectionFlag(CLIENT::HOOK, false);

    std::string expectedText1 = GetExpectedText1();
    std::string expectedText2 = GetExpectedText2();
    std::string expectedTextUseEffect = GetExpectedTextUseEffect();


    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");
}
