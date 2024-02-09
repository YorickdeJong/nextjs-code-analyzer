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

/**
  * Adds comment to specific json index based on the NextJs code found in the parsed data
  * @param index Refers to the specific index to insert the index into the "tokens" sub object
  *              in the json array
  * 
  * @param commentText Specifc comment to insert into the json object
  */ 

void JsonManager::ModifyJsonObject(size_t index, const std::string& commentText) {
    
    if (commentText == "") {
        return;
    }

    nlohmann::json comment;
    comment["value"] = commentText;
    comment["line"] = m_json["tokens"][index]["loc"]["start"]["line"];
    comment["start"] = m_json["tokens"][index]["loc"]["start"]["index"];
    comment["end"] = m_json["tokens"][index]["loc"]["end"]["index"];
    m_json["tokens"][index]["comment"] = comment;
}

/**
  * function to convert Json to Napi values, such that they can be parsed back into the javascript file
  */ 
void JsonManager::JsonToNapiValue() {

  if (m_json.length == 0) {
    throw std::runtime_error("Error: m_json is empty"); 
  }

  // Helper lambda for recursive handling
  std::function<Napi::Value(const nlohmann::json&)> convertToJson;
  convertToJson = [&](const nlohmann::json& j) -> Napi::Value {
      if (j.is_null()) {
          return m_env.Null();
      } 
      else if (j.is_boolean()) {
          return Napi::Boolean::New(m_env, j.get<bool>());
      } 
      else if (j.is_number()) {
          return Napi::Number::New(m_env, j.get<double>());
      } 
      else if (j.is_string()) {
          return Napi::String::New(m_env, j.get<std::string>());
      } 
      else if (j.is_object()) {
          Napi::Object obj = Napi::Object::New(m_env);

          for (const auto& el : j.items()) {
              obj.Set(el.key(), convertToJson(el.value()));
          }

          return obj;
      } 
      else if (j.is_array()) {
          Napi::Array array = Napi::Array::New(m_env);
          size_t i = 0;

          for (const auto& item : j) {
              array[i++] = convertToJson(item);
          }
          return array;
      } 
      else {
          return m_env.Undefined();
      }
  };

  m_returnData = convertToJson(m_json);
}


void JsonManager::ConvertStringToJson(const std::string &jsonString) {
  {
    Timer timer("Convert String to Json");
    m_json = nlohmann::json::parse(jsonString);
  }
}