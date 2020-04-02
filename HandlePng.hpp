#pragma once

#include <string>
#include <tuple>

class RayEngine;

class HandlePng {
public:
    static std::tuple<unsigned,std::string> save(const std::string& path, RayEngine* e);
};
