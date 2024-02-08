#pragma once

#include <string>
#include <vector>
#include <optional>
#include <regex>
#include <map>
#include "utils/constants.h"

class AnalysisReport {
    
    public: 
        AnalysisReport() {
           InitializeDetectionFlags();
           InitializeReverseLookupTable();
        }

        /**
         * Sets a detection flag in the analysis report.
         * @param key The key representing the specific detection flag.
         * @param value The boolean value to set for the detection flag.
         * @throws std::out_of_range if the key is not found in the detection flags.
         */
        void SetDetectionFlag(const std::string& key, bool value);
        
        /**
         * Retrieves the map of all detection flags.
         * @return A constant reference to the map of detection flags.
         */
        const std::map<std::string, std::pair<bool, std::string>> &GetDetectionFlags() const;

        /**
         * Gets the value of a specific detection flag.
         * @param key The key representing the specific detection flag.
         * @return The boolean value of the detection flag.
         * @throws std::out_of_range if the key is not found in the detection flags.
         */
        const bool GetDetectionFlag(const std::string& key) const;
        
        /**
         * Retrieves the string value associated with a specific key in the detection flags.
         * @param key The key for which to retrieve the string value.
         * @return A constant reference to the string value associated with the key.
         * @throws std::out_of_range if the key is not found in the detection flags.
         */
        const std::string &GetStringValue(const std::string& key) const;

        /**
         * Initializes a reverse lookup table for efficient searching by description.
         */
        void InitializeReverseLookupTable();

        /**
         * Finds the key corresponding to a given description.
         * @param description The description to search for.
         * @return An optional containing the key if found, std::nullopt otherwise.
         */
        std::optional<std::string> FindKeyByDescription(const std::string& description) const;

    private: 

    /**
 * Initializes the detection flags with default values and descriptions.
 */
        void InitializeDetectionFlags();


        std::map<std::string, std::pair<bool, std::string>> m_DetectionFlags;
        std::map<std::string, std::string> m_reverseLookupTable;
};