#pragma once
#include "export.h"
#include <string_view>

class utility_config_parser {
public:
    template <char S = '='>
    struct key_value {
        key_value(ngx_str_t s) {
            std::string_view sv {reinterpret_cast<char*>(s.data), s.len};
            if (auto p = sv.find_first_of(S); p == sv.npos) key_ = sv;
            else { key_ = sv.substr(0, p); val_ = sv.substr(p + 1); }
        }
        std::string_view key() const { return key_; } 
        std::string_view val() const { return val_; }
    private:
        std::string_view key_;
        std::string_view val_;
    };
};