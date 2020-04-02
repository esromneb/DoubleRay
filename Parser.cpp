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


/*
// Working code for using a input input adapter callback
// using nlohmann::detail::input_adapter ;
// using nlohmann::detail::input_adapter_protocol ;
typedef nlohmann::detail::parser<nlohmann::basic_json<>>::parse_event_t json_parse_event_t;
typedef std::function<bool(int depth, json_parse_event_t event, nlohmann::basic_json<>& parsed)> json_cb_t;
json_cb_t the_callback = [](int depth, json_parse_event_t event, nlohmann::basic_json<>& parsed) {
    const uint8_t _event = (uint8_t)event;
    cout << "Depth: " << depth << " in the callback " << (int) _event << "\n";
    return true;
};

*/



using nlohmann::detail::input_buffer_adapter ;

// this function is required to parse without exceptions
std::optional<nlohmann::json> jsonParseExceptionFree(const std::string& str) {
    const char* first = str.c_str();
    auto len = str.size();

    // The resulting json object
    nlohmann::json j;

    // some stuff I don't understand
    auto ia = std::make_shared<input_buffer_adapter>(reinterpret_cast<const char*>(&(*first)), len);
    nlohmann::detail::parser<nlohmann::basic_json<>>(ia, nullptr, false).parse(false, j);

    if( j.is_discarded() ) {
        // parse error
        return {};
    } else {
        // parsed correctly
        return j;
    }
}



// 0 is ok
// 1 is bad json
// 2 is missing required keys


std::tuple<unsigned,std::string> Parser::parse(const char* const str, RayEngine* e, const unsigned restrictParse) {

    // cout << "Parsed called with:\n\n" << str << "\n\n";

    nlohmann::json obj;

    std::string _str = str;

    auto maybeParsed = jsonParseExceptionFree(_str);

    if( maybeParsed.has_value() ) {
        obj = maybeParsed.value();
    } else {
        const std::string parseError = "Json parse error";
        // cout << parseError << "\n";
        return std::make_tuple(1,parseError);
    }

    // try {
    //     obj = nlohmann::json::parse(str);
    // } catch(nlohmann::json::parse_error &er) {
    //     cout << er.what() << "\n";
    //     return std::make_tuple(1,er.what());
    // }

    setRayApiTarget(e);

    unsigned subCode = 0;
    std::string subMessage;

    switch(restrictParse) {
        default:
        case 0: 
            std::tie(subCode, subMessage) = parseCamera(obj, e);

            if( subCode ) {
                return std::make_tuple(subCode, subMessage);
            }

            std::tie(subCode, subMessage) = parseGlobal(obj, e);

            if( subCode ) {
                return std::make_tuple(subCode, subMessage);
            }

            break;
        case 1:
            return parseCamera(obj, e);
            break;
        case 2:
            return parseGlobal(obj, e);
            break;
    }


    return std::make_tuple(0,"");

}

std::tuple<unsigned,std::string> Parser::parseCamera(const nlohmann::json& obj, RayEngine* e) {
    if( valid_object(obj, "camera") ) {

        // cout << "Have Camera\n";
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
    if( valid_object(obj, "global") ) {

        const auto gg = obj["global"];

        if(
            (valid_vec3(gg, "color") || valid_vec3(gg, "ambient_color")) &&
            valid_number(gg, "c")
            ) {
            const std::string ambientKey = valid_vec3(gg, "color") ? "color" : "ambient_color";

            cout << "Ambient using key: " << ambientKey << "\n";

            setAmbientColor(VEC3_SPREAD(gg[ambientKey]));
            setGlobalC(gg["c"]);

        } else {
            return std::make_tuple(2,"Global tree missing required keys");
        }

        if(valid_vec3(gg, "nohit_color")) {
            setNoHitColor(VEC3_SPREAD(gg["nohit_color"]));
        }


    } else {
        return std::make_tuple(2,"Global tree missing");
    }
    return std::make_tuple(0,"");
}
