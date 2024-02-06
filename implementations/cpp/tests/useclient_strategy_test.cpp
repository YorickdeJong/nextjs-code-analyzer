#include "reporter/reporter.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include "analysis/analysis.h"
#include <iostream>
#include "reporter/strategy/useclient_strategy.h"
#include "reporter/strategy/comment_strategy_interface.h"


class UseClientStrategyTest : public ::testing::Test {
protected:
    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
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


TEST_F(UseClientStrategyTest, largefileWithManyWordsAndUseClient) {


    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.manyWordsInFile = true;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, largeFileDetected + " \n");

    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, largeFileDetected + " \n" + getManyWords);

    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }

    EXPECT_EQ(returnText, largeFileDetected + " \n" + getManyWords);

}


TEST_F(UseClientStrategyTest, manyWordsAndUseClient) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.manyWordsInFile = true;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, getManyWords);

    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, getManyWords + removeClient);

}


TEST_F(UseClientStrategyTest, returnEmpty) {

    AnalysisReport analysisReport; 
    UseClientStrategy useClientStrategy; 
    analysisReport.useClientDetected = false;
    analysisReport.largeFileDetected = false;
    analysisReport.manyWordsInFile = true;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, "");

    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, "");

}


TEST_F(UseClientStrategyTest, removeClient) {
 
    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = false;
    analysisReport.manyWordsInFile = false;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, "");

    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, "");


    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, removeClient);

}


TEST_F(UseClientStrategyTest, largeFile) {

    analysisReport.useClientDetected = true;
    analysisReport.largeFileDetected = true;
    analysisReport.manyWordsInFile = false;

    const std::string largeFileDetected = LargeFileDetected();
    const std::string emptyText = EmptyText();
    const std::string getManyWords = GetManyWords();
    const std::string removeClient = RemoveClient();

    bool isUseClientPresent = analysisReport.useClientDetected;

    std::string returnText = useClientStrategy.ReturnMessage(largeFileDetected, emptyText, isUseClientPresent, analysisReport);
    
    EXPECT_EQ(returnText, largeFileDetected + " \n");

    
    if (analysisReport.manyWordsInFile && analysisReport.useClientDetected ) {
            returnText += getManyWords;
    }

    EXPECT_EQ(returnText, largeFileDetected + " \n");

    if (analysisReport.useClientDetected && !analysisReport.largeFileDetected 
            && useClientStrategy.AllvaluesFalse(analysisReport)) { 
            returnText += removeClient;

    }


    EXPECT_EQ(returnText, largeFileDetected + " \n");

}