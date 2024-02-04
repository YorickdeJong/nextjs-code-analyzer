#pragma once

#include <iostream>
#include <napi.h>
#include <nlohmann/json.hpp>

// JsonReader is responsible for transforming string data to JSON and
// JSON data Napi data, such that it can be parsed between typescript 
// and C++
class JsonReader {
    public:
        JsonReader(const Napi::CallbackInfo &_info, Napi::Env &_env);
        JsonReader(const nlohmann::json& _json, Napi::Env &_env);
        void NlohmannJsonToNapiValue();
        nlohmann::json &getJson() { return json; };
        Napi::Value getReturnData() { return returnData; };

    private: 
        void ConvertStringToJson(const std::string& jsonString);
        nlohmann::json json;
        Napi::Env env;
        Napi::Value returnData;
};