#pragma once

#include "RayEngine.hpp"

#include <tuple>

class Parser {
public:
    static std::tuple<int,std::string> parse(const char* const str, RayEngine* e);
};
