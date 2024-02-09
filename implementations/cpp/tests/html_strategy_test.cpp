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



class HtmlStrategyTest : public ::testing::Test {
protected:
    CommentStrategyChain commentStrategy;
    ChainBuilder chainBuilder;
    AnalysisReport analysisReport;
    const std::string javascriptToken = CLIENT_DESCRIPTIONS::USE_CLIENT_DESC;
    std::string comments;
    const std::string javascriptTokenValue = "p";
    
    void SetUp() override {

    }

    std::string ManyWordsDetected() {
        return "Many Words in File detected in client side file. Consider refactoring <" + 
           javascriptTokenValue + 
           "> into a different file for better SEO. ";
    }

    std::string EmptyText() {
        return "";
    }


};



TEST_F(HtmlStrategyTest, ManyWords_HTML) {

    analysisReport.SetDetectionFlag(CLIENT::HTML, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

    const std::string manyWordsDetected = ManyWordsDetected();
    const std::string emptyText = EmptyText();

    bool isHtmlPresent = analysisReport.GetDetectionFlag(CLIENT::HTML);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);
    
    std::string returnValue = "";
    if (isHtmlPresent && isManyWordsPresent) {
        returnValue += manyWordsDetected;
    }

    EXPECT_EQ(returnValue, manyWordsDetected);

}

TEST_F(HtmlStrategyTest, ManyWords) {

    analysisReport.SetDetectionFlag(CLIENT::HTML, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, true);

    const std::string manyWordsDetected = ManyWordsDetected();
    const std::string emptyText = EmptyText();

    bool isHtmlPresent = analysisReport.GetDetectionFlag(CLIENT::HTML);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);
    
    std::string returnValue = "";
    if (isHtmlPresent && isManyWordsPresent) {
        returnValue += manyWordsDetected;
    }

    EXPECT_EQ(returnValue, "");
}


TEST_F(HtmlStrategyTest, HTML) {

    analysisReport.SetDetectionFlag(CLIENT::HTML, true);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);

    const std::string manyWordsDetected = ManyWordsDetected();
    const std::string emptyText = EmptyText();

    bool isHtmlPresent = analysisReport.GetDetectionFlag(CLIENT::HTML);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);
    
    std::string returnValue = "";
    if (isHtmlPresent && isManyWordsPresent) {
        returnValue += manyWordsDetected;
    }

    EXPECT_EQ(returnValue, "");

}


TEST_F(HtmlStrategyTest, None) {

    analysisReport.SetDetectionFlag(CLIENT::HTML, false);
    analysisReport.SetDetectionFlag(CLIENT::MANY_WORDS, false);

    const std::string manyWordsDetected = ManyWordsDetected();
    const std::string emptyText = EmptyText();

    bool isHtmlPresent = analysisReport.GetDetectionFlag(CLIENT::HTML);
    bool isManyWordsPresent = analysisReport.GetDetectionFlag(CLIENT::MANY_WORDS);
    
    std::string returnValue = "";
    if (isHtmlPresent && isManyWordsPresent) {
        returnValue += manyWordsDetected;
    }

    EXPECT_EQ(returnValue, "");

}