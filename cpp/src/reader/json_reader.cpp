#include "reader/json_reader.h"


Napi::Value JsonReader::NlohmannJsonToNapiValue(nlohmann::json &j, Napi::Env env) {


  if (j.is_null()) {
    return env.Null();
  } 
  else if (j.is_boolean()) {
    return Napi::Boolean::New(env, j.get<bool>());
  } 
  else if (j.is_number()) {
    return Napi::Number::New(env, j.get<double>());
  } 
  else if (j.is_string()) {
    return Napi::String::New(env, j.get<std::string>());
  } 
  else if (j.is_object()) {
    Napi::Object obj = Napi::Object::New(env);
    for (auto& el : j.items()) {
      obj.Set(el.key(), NlohmannJsonToNapiValue(el.value(), env));
    }
    return obj;
  } 
  else if (j.is_array()) {
    Napi::Array array = Napi::Array::New(env);
    for (size_t i = 0; i < j.size(); i++) {
      array[i] = NlohmannJsonToNapiValue(j[i], env);
    }
    return array;
  }
  return env.Undefined(); // Fallback for other types
}


nlohmann::json JsonReader::ConvertStringToJson(const Napi::CallbackInfo& info) {
  // Extract the JSON string from the JavaScript arguments.
  std::string jsonString = info[0].As<Napi::String>().Utf8Value();
  nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
  return jsonObject;
}
