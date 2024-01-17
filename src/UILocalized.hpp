#pragma once

#include "UILocalized.hpp"
#define _S(_LITERAL)    (const char*)u8##_LITERAL
#define _L(_TEXT) UILocalized::get_localized_text(_TEXT)
#include <string>
#include <vector>

class UILocalized {
public:
    static void add_localized_font(float m_font_size);
    static void init_loc();
    static const char* get_localized_text(const char* text);

    static const inline std::vector<std::string> s_ui_language {
        "English", 
        _S("简体中文"), 
        _S("繁體中文")
    };

    static void set_language();

    enum UILanguage : int8_t {
        ENG,
        ZH_CN,
        CHT
    };

    static UILanguage get_ui_language_value();
};