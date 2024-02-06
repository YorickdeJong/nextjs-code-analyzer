#include <gtest/gtest.h>
#include <unordered_set>
#include <iostream>
#include "reporter/strategy/comment_strategy_interface.h"
#include "reporter/strategy/hook_strategy.h"
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/other_strategies.h"
#include "reporter/chain/comment_strategy_chain_builder.h"





TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithStandardInput_ReturnsEmptyComments) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    const std::string javascript_token = "useEffect";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascript_token)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}


TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithUseClientAndLargeFileFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    const std::string javascriptToken = "useEffect";

    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");

}

TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithUseClientLargeFileAndUseEffectFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    const std::string javascriptToken = "useEffect";


    const std::string text1 = "Consider refactoring " + javascriptToken + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptToken + " or add 'use client' to make this file client side";
    const std::string textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";


    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text1 + " \n" + textUseEffect);

}


TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithoutUseClientLargeFileAndUseEffectFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    const std::string javascriptToken = "useEffect";


    const std::string text1 = "Consider refactoring " + javascriptToken + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptToken + " or add 'use client' to make this file client side";

    const std::string textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";


    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text2 + " \n" + textUseEffect);

}

TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithoutUseClientLargeFileAndWithoutUseEffectFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    const std::string javascriptToken = "useEffect";


    const std::string text1 = "Consider refactoring " + javascriptToken + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptToken + " or add 'use client' to make this file client side";
    const std::string textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";


    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments,  "");

}


TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithUseClientLargeFileAndHookFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    const std::string javascriptToken = "useState";


    const std::string text1 = "Consider refactoring " + javascriptToken + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptToken + " or add 'use client' to make this file client side";
    const std::string textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";


    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text1 + " \n");
}


TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithoutUseClientLargeFileAndHookFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    const std::string javascriptToken = "useState";


    const std::string text1 = "Consider refactoring " + javascriptToken + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptToken + " or add 'use client' to make this file client side";
    const std::string textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";


    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, text2 + " \n");
}


TEST(CommentStrategyChainBuilderHook, ExecuteChain_WithoutUseClientLargeFileAndWithoutHookFlags) {
    CommentStrategyChain commentStrategy;
    commentStrategy.ChainBuilder();

    AnalysisReport analysisReport;
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;
    const std::string javascriptToken = "useState";


    const std::string text1 = "Consider refactoring " + javascriptToken + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptToken + " or add 'use client' to make this file client side";
    const std::string textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";


    std::string comments;
    auto &strategies = commentStrategy.GetStrategies();
    for (const auto &strategy : strategies) {
        if (!strategy->ExecuteStrategy(analysisReport, comments, javascriptToken)) {
            break; // Break the chain if a strategy indicates to stop further processing
        }
    }

    EXPECT_EQ(comments, "");
}

