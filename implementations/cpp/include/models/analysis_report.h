#pragma once

#include <string>
#include <vector>
#include <optional>
#include <regex>

#include "utils/constants.h"

class AnalysisReport {
    
    
    public: 
        AnalysisReport() {
           InitializeDetectionFlags();
           InitializeReverseLookupTable();
        }



        void SetDetectionFlag(const std::string& key, bool value) {
            auto it = m_DetectionFlags.find(key);
            if (it != m_DetectionFlags.end()) {
                it->second.first = value;
            } else {
                throw std::out_of_range("Error while setting detection flag: Key not found in detection flags");
            }
        }
        
        const std::map<std::string, std::pair<bool, std::string>> &GetDetectionFlags() const {
            return m_DetectionFlags;
        }

        const bool GetDetectionFlag(const std::string& key) const {
            auto it = m_DetectionFlags.find(key);
            if (it != m_DetectionFlags.end()) {
                return it->second.first;
            } else {
                throw std::out_of_range("Error while getting detection flag: Key not found in detection flags");
            }
        }

        const std::string &GetStringValue(const std::string& key) const{
            auto it = m_DetectionFlags.find(key);
            if (it != m_DetectionFlags.end()) {
                return it->second.second;
            } else {
                throw std::out_of_range("Error while getting string value: Key not found in string value");
            }
        }
        void InitializeReverseLookupTable() {
            for (const auto& pair : m_DetectionFlags) {
                m_reverseLookupTable[pair.second.second] = pair.first;
            }
        }

        std::optional<std::string> FindKeyByDescription(const std::string& description) const {
            std::string newDescription = description;
            std::regex re("use[A-Z]\\w*");
            std::smatch match;
                
            if (std::regex_search(description, match, re)) {
                newDescription = "hook";
            }

            auto it = m_reverseLookupTable.find(newDescription);
            if (it != m_reverseLookupTable.end()) {
                return it->second;
            } else {
                return std::nullopt;
            }
        }

    private: 
        void InitializeDetectionFlags() {
            m_DetectionFlags[CLIENT::USE_CLIENT] = std::make_pair(false, CLIENT_DESCRIPTIONS::USE_CLIENT_DESC);
            m_DetectionFlags[CLIENT::HOOK] = std::make_pair(false, CLIENT_DESCRIPTIONS::HOOK_DESC);
            m_DetectionFlags[CLIENT::LARGE_FILE] = std::make_pair(false, CLIENT_DESCRIPTIONS::LARGE_FILE_DESC);
            m_DetectionFlags[CLIENT::MANY_WORDS] = std::make_pair(false, CLIENT_DESCRIPTIONS::MANY_WORDS_DESC);
            m_DetectionFlags[CLIENT::WINDOW] = std::make_pair(false, CLIENT_DESCRIPTIONS::WINDOW_DESC);
            m_DetectionFlags[CLIENT::DOCUMENT] = std::make_pair(false, CLIENT_DESCRIPTIONS::DOCUMENT_DESC);
            m_DetectionFlags[CLIENT::BUTTON] = std::make_pair(false, CLIENT_DESCRIPTIONS::BUTTON_DESC);
            m_DetectionFlags[CLIENT::ONCLICK] = std::make_pair(false, CLIENT_DESCRIPTIONS::ONCLICK_DESC);
            m_DetectionFlags[CLIENT::EVENT] = std::make_pair(false, CLIENT_DESCRIPTIONS::EVENT_DESC);
            m_DetectionFlags[CLIENT::ROUTER] = std::make_pair(false, CLIENT_DESCRIPTIONS::ROUTER_DESC);
            m_DetectionFlags[CLIENT::LOCAL] = std::make_pair(false, CLIENT_DESCRIPTIONS::LOCAL_DESC);
            m_DetectionFlags[CLIENT::DYNAMIC] = std::make_pair(false, CLIENT_DESCRIPTIONS::DYNAMIC_DESC);
        }


        std::map<std::string, std::pair<bool, std::string>> m_DetectionFlags;
        std::map<std::string, std::string> m_reverseLookupTable;
};