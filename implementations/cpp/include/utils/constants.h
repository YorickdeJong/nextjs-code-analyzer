#pragma once

#include <unordered_set>
#include <string>

namespace CLIENT {

    const std::string USE_CLIENT = "USE_CLIENT"; 
    const std::string HOOK = "HOOK";
    const std::string LARGE_FILE = "LARGE_FILE";
    const std::string MANY_WORDS = "MANY_WORDS"; 
    const std::string WINDOW = "WINDOW"; 
    const std::string DOCUMENT = "DOCUMENT"; 
    const std::string BUTTON = "BUTTON"; 
    const std::string ONCLICK = "ONCLICK"; 
    const std::string EVENT = "EVENT"; 
    const std::string ROUTER = "ROUTER"; 
    const std::string LOCAL = "LOCAL"; 
    const std::string DYNAMIC = "DYNAMIC"; 
    const std::string HTML = "HTML"; 
}


namespace CLIENT_DESCRIPTIONS {
    const std::string USE_CLIENT_DESC = "use client";
    const std::string USE_STATE_DESC = "useState";
    const std::string USE_EFFECT_DESC = "useEffect";
    const std::string HOOK_DESC = "hook";
    const std::string LARGE_FILE_DESC = "large file";
    const std::string MANY_WORDS_DESC = "many words";
    const std::string WINDOW_DESC = "window";
    const std::string DOCUMENT_DESC = "document";
    const std::string BUTTON_DESC = "button";
    const std::string ONCLICK_DESC = "onClick";
    const std::string EVENT_DESC = "event";
    const std::string ROUTER_DESC = "router";
    const std::string LOCAL_DESC = "local";
    const std::string DYNAMIC_DESC = "dynamic";
    const std::string HTML_DESC = "html"; 
 }

namespace FILE_SPECS {
    const int WORD_COUNT = 30;
    const int FILE_LENGTH = 99;
}

namespace HTML_ELEMENTS {

    const std::array<std::string, 15> HTML_ARRAY = {
        "p", 
        "u", 
        "h1", 
        "h2",
        "h3",
        "h4",
        "h5",
        "li",
        "td",
        "a",
        "label",
        "span",
        "textarea",
        "i",
        "title"
    };
}