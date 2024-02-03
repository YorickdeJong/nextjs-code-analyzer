

#include <iostream>
#include <napi.h>

class JSON_READER{

    private: 
        std::string json;
    public:
        Napi::String AnalyzeAST(const Napi::CallbackInfo& info);

};