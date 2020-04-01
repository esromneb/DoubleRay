#include "Parser.hpp"
#include "RayApi.hpp"
#include "Macros.hpp"

#include "json.hpp"

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


// 0 is ok
// 1 is bad json
// 2 is missing required keys

std::tuple<int,std::string> Parser::parse(const char* const str, RayEngine* e) {

    cout << "Parsed called with:\n\n" << str << "\n\n";

    nlohmann::json obj;

    try {
        obj = nlohmann::json::parse(str);
    } catch(nlohmann::json::parse_error &er) {
        // cout << er.what() << "\n";
        return std::make_tuple(1,er.what());
    }

    setRayApiTarget(e);


    // auto 

    if( false ) {
        cout << obj["global"]["ambient_color"][0] << "\n";
        cout << obj["global"]["ambient_color"][1] << "\n";
    }

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
            cout << "loc size " << camera["loc"].size() << "\n";

            setCamera(VEC3_SPREAD(camera["loc"]), VEC3_SPREAD(camera["dir"]), VEC3_SPREAD(camera["rot"]));

        } else {
            cout << "Camera tree missing required keys\n";
        }

    } else {
        cout << "No Camera\n";
    }


    return std::make_tuple(0,"");
}
