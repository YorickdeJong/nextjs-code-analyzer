#include "reporter/reporter.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include "analysis/analysis.h"
#include <iostream>
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/comment_strategy_interface.h"





TEST(UseClientStrategyTest, largefileWithManyWordsAndUseClient) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.manyWordsInFile = true;

    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text1 + " \n");

    
    const std::string manyWordsString = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += manyWordsString;
    }

    EXPECT_EQ(returnText, text1 + " \n" + manyWordsString);


    const std::string removeClientSide =  "Consider removing use client from this file as no client side components have been detected \n";
    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClientSide;

    }

    EXPECT_EQ(returnText, text1 + " \n" + manyWordsString);

}


TEST(UseClientStrategyTest, manyWordsAndUseClient) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.manyWordsInFile = true;

    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    
    const std::string manyWordsString = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += manyWordsString;
    }

    EXPECT_EQ(returnText, manyWordsString);


    const std::string removeClientSide =  "Consider removing use client from this file as no client side components have been detected \n";
    std::cout << "TRUES" << useClientStrategy.AllvaluesFalse(analysisReport) << std::endl;
    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClientSide;

    }


    EXPECT_EQ(returnText, manyWordsString + removeClientSide);

}


TEST(UseClientStrategyTest, returnEmpty) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = false;
    analysisReport.manyWordsInFile = true;

    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    
    const std::string manyWordsString = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += manyWordsString;
    }

    EXPECT_EQ(returnText, "");


    const std::string removeClientSide =  "Consider removing use client from this file as no client side components have been detected \n";
    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClientSide;

    }


    EXPECT_EQ(returnText, "");

}


TEST(UseClientStrategyTest, removeClientSide) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.manyWordsInFile = false;

    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    
    const std::string manyWordsString = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += manyWordsString;
    }

    EXPECT_EQ(returnText, "");


    const std::string removeClientSide =  "Consider removing use client from this file as no client side components have been detected \n";
    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClientSide;

    }


    EXPECT_EQ(returnText, removeClientSide);

}


TEST(UseClientStrategyTest, largeFile) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.manyWordsInFile = false;

    const std::string text1 = "Large file detected! Consider refactoring 'use client' into a smaller file";
    const std::string text2 = "";
    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(text1, text2, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, text1 + " \n");

    
    const std::string manyWordsString = "Client side file detected with many words. Consider refactoring for better SEO score \n";
    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += manyWordsString;
    }

    EXPECT_EQ(returnText, text1 + " \n");


    const std::string removeClientSide =  "Consider removing use client from this file as no client side components have been detected \n";
    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClientSide;

    }


    EXPECT_EQ(returnText, text1 + " \n");

}