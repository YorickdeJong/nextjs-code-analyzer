#include <string> 

#include <iostream>
#include "reporter/strategy/comment_strategy_interface.h"
#include "utils/constants.h"



class HtmlStrategy : public CommentStrategyInterface {
    public:
        std::string CommentText(const AnalysisReport &analysisReport, const std::string &javascriptTokenValue) const override {        
            
            
            bool htmlElementDetected = analysisReport.GetDetectionFlag(CLIENT::HTML);
            bool largeFileDetected = analysisReport.GetDetectionFlag(CLIENT::HTML);

            if (htmlElementDetected && largeFileDetected) {
                return "Many Words in File detected in client side file. Consider refactoring <" + 
                        javascriptTokenValue + 
                        "> into a different file for better SEO. ";
            }
            return "";
        }


        bool ExecuteStrategy(const AnalysisReport &analysisReport, 
            std::string &comments, const std::string &javascriptTokenValue) const override {
                bool isUseClientPresent = analysisReport.GetDetectionFlag(CLIENT::USE_CLIENT);

                std::cout << "USE CLIENT IN HTML" << isUseClientPresent << std::endl;

                for (const std::string &htmlElement : HTML_ELEMENTS::HTML_ARRAY) {
                    if (javascriptTokenValue == htmlElement && isUseClientPresent) {
                        comments = CommentText(analysisReport, javascriptTokenValue);
                        return false;
                    }

                }

                return true;
        } 
};