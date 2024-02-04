#include "reader/json_reader.h"


JsonReader::JsonReader(const Napi::CallbackInfo &_info, Napi::Env &_env) 
: env{_env} {
  std::string jsonString = _info[0].As<Napi::String>().Utf8Value();
  ConvertStringToJson(jsonString);
}

JsonReader::JsonReader(const nlohmann::json& _json, Napi::Env &_env)
: json(_json), env(_env) {
    // The JSON object is passed by reference, so no std::move is used here.
}

void JsonReader::NlohmannJsonToNapiValue() {

  if (json.is_null()) {
    returnData = env.Null();
  } 
  else if (json.is_boolean()) {
    returnData = Napi::Boolean::New(env, json.get<bool>());
  } 
  else if (json.is_number()) {
    returnData = Napi::Number::New(env, json.get<double>());
  } 
  else if (json.is_string()) {
    returnData = Napi::String::New(env, json.get<std::string>());
  } 
  else if (json.is_object()) {
    Napi::Object obj = Napi::Object::New(env);
    for (auto& el : json.items()) {
      // Convert each element in the object
      nlohmann::json subJson = el.value();
      JsonReader subReader(subJson, env); // Create a sub-reader for the nested JSON
      subReader.NlohmannJsonToNapiValue(); // Convert the nested JSON
      obj.Set(el.key(), subReader.returnData); // Set the converted value in the object
    }
    returnData = obj;
  } 
  else if (json.is_array()) {
    Napi::Array array = Napi::Array::New(env);
    for (size_t i = 0; i < json.size(); i++) {
      // Convert each element in the array
      nlohmann::json subJson = json[i];
      JsonReader subReader(subJson, env); // Create a sub-reader for the nested JSON
      subReader.NlohmannJsonToNapiValue(); // Convert the nested JSON
      array[i] = subReader.returnData; // Set the converted value in the array
    }
    returnData = array;
  }
  else {
    returnData = env.Undefined(); // Fallback for other types
  }
}


void JsonReader::ConvertStringToJson(const std::string& jsonString) {
  json = nlohmann::json::parse(jsonString);
}