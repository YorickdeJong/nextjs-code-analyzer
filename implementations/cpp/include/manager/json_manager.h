#pragma once

#include <iostream>
#include <napi.h>
#include <nlohmann/json.hpp>

/**
 * The JsonManager class is responsible for handling the conversion between JSON data and Napi values.
 * It allows for passing JSON data between TypeScript and C++ by converting string data to JSON and 
 * JSON data to Napi values.
 */
class JsonManager {
    public:

        /**
         * Constructs a JsonManager from Napi callback info, which typically includes the arguments passed from TypeScript.
         * @param _info The Napi callback info including arguments passed from the TypeScript context.
         * @param _env The Napi environment, which is used to interact with the value types of N-API.
         */
        JsonManager(const Napi::CallbackInfo &_info, Napi::Env &_env);
         
         /**
         * Constructs a JsonManager directly from a JSON object.
         * @param _json The JSON object to manage.
         * @param _env The Napi environment, which is used to interact with the value types of N-API.
         */
        JsonManager(const nlohmann::json &_json, Napi::Env &_env);
        
        /**
         * Converts the internal JSON object to a Napi value that can be returned to the TypeScript context.
         */
        void JsonToNapiValue();
        
        /**
         * Modifies a JSON object at a specific index by inserting a comment.
         * @param index The index of the JSON object to modify.
         * @param commentText The comment text to insert into the JSON object.
         */
        void ModifyJsonObject(size_t index, const std::string& commentText);

         /**
         * Retrieves the internal JSON object.
         * @return A constant reference to the internal JSON object.
         */
        const nlohmann::json &GetJson() const { return m_json; };

        /**
         * Sets the internal JSON object based on some external criteria (currently unimplemented).
         */
        void SetJson(){ }

        /**
         * Retrieves the Napi value that represents the converted JSON object ready to be returned to TypeScript.
         * @return The Napi value representation of the JSON object.
         */
        Napi::Value GetReturnData() { return m_returnData; };

    private: 
        /**
         * Converts a JSON-formatted string into a JSON object.
         * @param jsonString The JSON string to convert.
         */
        void ConvertStringToJson(const std::string& jsonString);
        
        nlohmann::json m_json;
        Napi::Env m_env;
        Napi::Value m_returnData;
};