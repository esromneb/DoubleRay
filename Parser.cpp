#include "Parser.hpp"

#include "json.hpp"

#include <string>
#include <iostream>

using namespace std;


// 0 is ok
// 1 is bad json
// 2 is missing required keys

std::tuple<int,std::string> Parser::parse(const char* const str, RayEngine* e) {

    // std::string ex = "{\"global\":{\"ambient_color\":[1,0,0]}}";

    // cout << ex << "\n";

    nlohmann::json obj;

    try {
        obj = nlohmann::json::parse(str);
    } catch(nlohmann::json::parse_error &er) {
        // cout << er.what() << "\n";
        return std::make_tuple(1,er.what());
    }


    // auto 

    if( false ) {
        cout << obj["global"]["ambient_color"][0] << "\n";
        cout << obj["global"]["ambient_color"][1] << "\n";
    }

    if( obj["camera"].is_object() ) {

        cout << "Have Camera\n";
        const auto camera = obj["camera"];

        if( 
            camera["loc"].is_array() && 
            camera["dir"].is_array() && 
            camera["rot"].is_array() && 
            camera["depth"].is_number()
            ) {
            
        }

    } else {
        cout << "No Camera\n";
    }


    return std::make_tuple(0,"");
}
