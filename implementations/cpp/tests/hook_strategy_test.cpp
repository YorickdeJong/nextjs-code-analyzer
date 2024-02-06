

#include "reporter/reporter.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include "analysis/analysis.h"
#include <iostream>
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/comment_strategy_interface.h"





TEST(UseEffectStrategyTest, useEffectWithUseClientAndLargeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    const std::string javascriptTokenValue = "useEffect"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text1 + " \n");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, text1 + " \n" + textUseEffect);

}

TEST(UseEffectStrategyTest, useEffectWithoutUseClientAndLargeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    const std::string javascriptTokenValue = "useEffect"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text2 + " \n");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, text2 + " \n" + textUseEffect);

}


TEST(UseEffectStrategyTest, NoUseEffectAndUseClient) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;

    const std::string javascriptTokenValue = "useEffect"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected ) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, "");

}




TEST(UseEffectStrategyTest, useEffectDetectedWithUseClientAndLargeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    const std::string javascriptTokenValue = "useEffect"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text1 + " \n");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, text1 + " \n" + textUseEffect);

}



TEST(HookStrategyTest, HookWithUseClientAndLargeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    const std::string javascriptTokenValue = "useState"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text1 + " \n");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, text1 + " \n");

}


TEST(HookStrategyTest, HookWithNoUseClientAndLargeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    const std::string javascriptTokenValue = "useState"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text2 + " \n");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, text2 + " \n");

}


TEST(HookStrategyTest, NoHookWithNoUseClientAndLargeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;

    const std::string javascriptTokenValue = "useState"; 

    const std::string text1 = "Consider refactoring " + javascriptTokenValue + " Large file detected";
    const std::string text2 = "No use client detected, consider refactoring " + 
        javascriptTokenValue + " or add 'use client' to make this file client side";

    bool isUseClientPresent = analysisReport.hookDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    std::string textUseEffect = ""; 
    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = "If you are using an async await fetch in your useEffect, "
            "consider making this component server side and make this component async. Example: "
            "async function Component() {"
            "    const var = await fetchFunction();"
            "    return ("
            "        <div></div>"
            "    );"
            "}  \n";
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, "");

}
