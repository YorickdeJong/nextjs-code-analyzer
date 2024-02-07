#pragma once

#include <iostream>
#include <napi.h>
#include <nlohmann/json.hpp>

// JsonReader is responsible for transforming string data to JSON and
// JSON data Napi data, such that it can be parsed between typescript 
// and C++
class JsonManager {
    public:
        JsonManager(const Napi::CallbackInfo &_info, Napi::Env &_env);
        JsonManager(const nlohmann::json &_json, Napi::Env &_env);
        void JsonToNapiValue();
        void Modify(std::string commentText);
        const nlohmann::json &GetJson() const { return m_json; };
        Napi::Value GetReturnData() { return m_returnData; };

    private: 
        void ConvertStringToJson(const std::string& jsonString);
        nlohmann::json m_json;
        Napi::Env m_env;
        Napi::Value m_returnData;
};