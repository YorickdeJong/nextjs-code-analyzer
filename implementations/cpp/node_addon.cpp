#include "manager/json_manager.h"
#include "analysis/analysis.h"
#include "reporter/reporter.h"

Napi::Value CreateReport(const Napi::CallbackInfo& info) {

  std::cout << info.Env() << std::endl;

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

  class JsonManager jsonManager(info, env);
  class Analyzer analyzer;



  // Analyze code and add comments to sections
  analyzer.AnalyzeJson(jsonManager.GetJson());

  // Add the report to the json object
  Reporter reporter(analyzer.GetAnalysisResult(), analyzer.GetTokenInfos());
  reporter.AddCommentsToJsonObject(jsonManager);

  // Convert the JSON object to a NAPI value.
  jsonManager.JsonToNapiValue();

  // Return value
  return Napi::Value(env, jsonManager.GetReturnData());
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "CreateReport"),
        Napi::Function::New(env, CreateReport)
    );

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)