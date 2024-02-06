#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/other_strategies.h"
#include "reporter/chain/comment_strategy_chain_builder.h"


class UseEffectStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport;
    UseClientStrategy useClientStrategy;
    ChainBuilder chainBuilder;
    const std::string javascriptTokenValue = "useEffect";
    std::string comments;

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
    ChainBuilder chainBuilder;
    const std::string javascriptTokenValue = "useState";
    std::string comments;
    
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



TEST_F(UseEffectStrategyTest, ExecuteChain_WithStandardInput_ReturnsEmptyComments) {

    auto &strategies = chainBuilder.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptTokenValue)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}


TEST_F(UseEffectStrategyTest, ExecuteChain_WithUseClientAndLargeFileFlags) {
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    
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

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

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
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

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

    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;

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
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

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
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;


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
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;


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
