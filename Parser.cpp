#include "Parser.hpp"
#include "RayApi.hpp"
#include "Macros.hpp"


#include <string>
#include <iostream>

using namespace std;

static bool valid_array(const nlohmann::json& obj, const std::string& key) {
    return obj.contains(key) && obj[key].is_array();
}

static bool valid_vec3(const nlohmann::json& obj, const std::string& key) {
    return valid_array(obj, key) && obj[key].size() == 3 && obj[key][0].is_number() && obj[key][1].is_number() && obj[key][2].is_number();
}

static bool valid_number(const nlohmann::json& obj, const std::string& key) {
    return obj.contains(key) && obj[key].is_number();
}

static bool valid_object(const nlohmann::json& obj, const std::string& key) {
    return obj.contains(key) && obj[key].is_object();
}


// 0 is ok
// 1 is bad json
// 2 is missing required keys

std::tuple<unsigned,std::string> Parser::parse(const char* const str, RayEngine* e, const unsigned restrictParse) {

    cout << "Parsed called with:\n\n" << str << "\n\n";

    nlohmann::json obj;

    try {
        obj = nlohmann::json::parse(str);
    } catch(nlohmann::json::parse_error &er) {
        // cout << er.what() << "\n";
        return std::make_tuple(1,er.what());
    }

    setRayApiTarget(e);

    unsigned subCode = 0;
    std::string subMessage;

    if( !restrictParse || restrictParse == 1 ) {
        std::tie(subCode, subMessage) = parseCamera(obj, e);

        if( subCode ) {
            return std::make_tuple(subCode, subMessage);
        }
    }


    // auto 

    if( false ) {
        cout << obj["global"]["ambient_color"][0] << "\n";
        cout << obj["global"]["ambient_color"][1] << "\n";
    }

    return std::make_tuple(0,"");

}

std::tuple<unsigned,std::string> Parser::parseCamera(const nlohmann::json& obj, RayEngine* e) {
    if( obj.contains("camera") && obj["camera"].is_object() ) {

        cout << "Have Camera\n";
        const auto camera = obj["camera"];

        if( 
            valid_vec3(camera, "loc") && 
            valid_vec3(camera, "dir") && 
            valid_vec3(camera, "rot") && 
            valid_number(camera, "depth")
            ) {
            cout << "Valid Camera Block\n";
            // cout << "loc size " << camera["loc"].size() << "\n";

            // cout << "Grab Camera Rot: " << camera["rot"][2] << "\n";

            setCamera(VEC3_SPREAD(camera["loc"]), VEC3_SPREAD(camera["dir"]), VEC3_SPREAD(camera["rot"]));
            setDepth(camera["depth"]);

        } else {
            return std::make_tuple(2,"Camera tree missing required keys");
        }

    } else {
        return std::make_tuple(2,"Camera tree missing");
    }


    return std::make_tuple(0,"");
}


std::tuple<unsigned,std::string> Parser::parseGlobal(const nlohmann::json& obj, RayEngine* e) {

    return std::make_tuple(0,"");
}