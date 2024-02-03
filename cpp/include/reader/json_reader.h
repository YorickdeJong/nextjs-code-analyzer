

#include <iostream>
#include <napi.h>
#include <nlohmann/json.hpp>


class JsonReader{

    private: 
        std::string json;
    public:
        Napi::Value NlohmannJsonToNapiValue(nlohmann::json &j, Napi::Env env);
        nlohmann::json ConvertStringToJson(const Napi::CallbackInfo& info);
};