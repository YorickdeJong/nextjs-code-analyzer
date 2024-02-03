#include "reader/json_reader.h"


Napi::String JsonReader(const Napi::CallbackInfo& info) {
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

  std::string json = info[0].As<Napi::String>().Utf8Value();
  
  // Your C++ code to deserialize and analyze the JSON would go here
  std::cout << "Received JSON: " << json << std::endl;

  // For demonstration purposes, let's just return the same JSON string
  return Napi::String::New(env, json);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "JsonReader"),
        Napi::Function::New(env, JsonReader)
    );

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)