#include "manager/json_manager.h"


JsonManager::JsonManager(const Napi::CallbackInfo &_info, Napi::Env &_env) 
: m_env{_env} {
  std::string jsonString = _info[0].As<Napi::String>().Utf8Value();
  ConvertStringToJson(jsonString);
}

JsonManager::JsonManager(const nlohmann::json &_json, Napi::Env &_env)
: m_json{_json}, m_env{_env} {
    // The m_json object is passed by reference, so no std::move is used here.
}

void JsonManager::Modify(std::string commentText) {
    nlohmann::json comment;
    comment["value"] = commentText;
    comment["line"] = m_json["loc"]["start"]["line"];
    comment["start"] = m_json["loc"]["start"]["index"];
    comment["end"] = m_json["loc"]["end"]["index"];
    m_json["comment"] = comment;
}


void JsonManager::JsonToNapiValue() {

  if (m_json.is_null()) {
    m_returnData = m_env.Null();
  } 
  else if (m_json.is_boolean()) {
    m_returnData = Napi::Boolean::New(m_env, m_json.get<bool>());
  } 
  else if (m_json.is_number()) {
    m_returnData = Napi::Number::New(m_env, m_json.get<double>());
  } 
  else if (m_json.is_string()) {
    m_returnData = Napi::String::New(m_env, m_json.get<std::string>());
  } 
  else if (m_json.is_object()) {
    Napi::Object obj = Napi::Object::New(m_env);
    for (auto& el : m_json.items()) {
      // Convert each element in the object
      nlohmann::json subJson = el.value();
      JsonManager subReader(subJson, m_env); // Create a sub-reader for the nested m_json
      subReader.JsonToNapiValue(); // Convert the nested m_json
      obj.Set(el.key(), subReader.m_returnData); // Set the converted value in the object
    }
    m_returnData = obj;
  } 
  else if (m_json.is_array()) {
    Napi::Array array = Napi::Array::New(m_env);
    for (size_t i = 0; i < m_json.size(); i++) {
      // Convert each element in the array
      nlohmann::json subJson = m_json[i];
      JsonManager subReader(subJson, m_env); // Create a sub-reader for the nested m_json
      subReader.JsonToNapiValue(); // Convert the nested m_json
      array[i] = subReader.m_returnData; // Set the converted value in the array
    }
    m_returnData = array;
  }
  else {
    m_returnData = m_env.Undefined(); // Fallback for other types
  }
}


void JsonManager::ConvertStringToJson(const std::string &jsonString) {
  m_json = nlohmann::json::parse(jsonString);
}