

#include "reporter/reporter.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include "analysis/analysis.h"
#include <iostream>
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/comment_strategy_interface.h"



class UseEffectStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy;
    
    const std::string javascriptTokenValue = "useEffect";
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
    
    const std::string javascriptTokenValue = "useState";
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

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText1 + " \n");

    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText1 + " \n" + textUseEffect);

}

TEST_F(UseEffectStrategyTest, useEffectWithoutUseClientAndLargeFile) {

    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText2 + " \n");

    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText2 + " \n" + textUseEffect);

}


TEST_F(UseEffectStrategyTest, NoUseEffectAndUseClient) {

    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;

    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, "");

}




TEST_F(UseEffectStrategyTest, useEffectDetectedWithUseClientAndLargeFile) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;
    
    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText1 + " \n");

    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText1 + " \n" + textUseEffect);

}



TEST_F(UseStateStrategyTest, HookWithUseClientAndLargeFile) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText1 + " \n");


    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText1 + " \n");

}


TEST_F(UseStateStrategyTest, HookWithNoUseClientAndLargeFile) {

    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = true;

    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, getExpectedText2 + " \n");


    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, getExpectedText2 + " \n");

}


TEST_F(UseStateStrategyTest, NoHookWithNoUseClientAndLargeFile) {
 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = true;
    analysisReport.hookDetected = false;

    bool isUseClientPresent = analysisReport.hookDetected;
    const std::string getExpectedText1 = GetExpectedText1();
    const std::string getExpectedText2 = GetExpectedText2();

    std::string returnText = useClientStrategy.ReturnMessage(getExpectedText1, getExpectedText2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");


    if (javascriptTokenValue == "useEffect" && analysisReport.hookDetected) {
        textUseEffect = GetExpectedTextUseEffect();
        returnText += textUseEffect;
    }

    EXPECT_EQ(returnText, "");

}
