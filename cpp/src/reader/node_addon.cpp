#include "reader/json_reader.h"
#include "analysis/analysis.h"

Napi::Value Analyzer(const Napi::CallbackInfo& info) {
  class JsonReader reader;
  class Analyzer analyzer;

  Napi::Env env = info.Env();
  
  // Check the number of arguments passed.
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }

  // Check the argument types.
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }

  //Convert the string to a JSON object
  nlohmann::json jsonObject = reader.ConvertStringToJson(info);

  // Analyze code and add comments to sections
  nlohmann::json analyzedJson = analyzer.Analyze(jsonObject);


  // Convert the JSON object to a NAPI value.
  Napi::Value returnValue = reader.NlohmannJsonToNapiValue(jsonObject, env);



  // Return value
  return Napi::Value(env, returnValue);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "Analyzer"),
        Napi::Function::New(env, Analyzer)
    );
  
    std::cout << "JSON Object: " << std::endl;
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)