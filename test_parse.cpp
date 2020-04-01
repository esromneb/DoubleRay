#include "Vec3.hpp"
#include "Parser.hpp"
#include "RayEngine.hpp"

#include <iostream>
#include <cmath>

using namespace std;


// Annoying but required for now in the tests until we fix the RayApi
extern "C" {
void doRenderOfficial() {
}
}


const std::string t0 = "{\"global\":{\"ambient_color\":[1,0,0]}}";
const std::string t1 = "{\"global\":{\"ambient_color\":[1,0,0]}";
const std::string t2 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0]}}";
const std::string t3 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0],\"dir\": [-1, 0, 0],\"rot\": [0, 0, 1],\"depth\": 6}}";         // good
const std::string t4 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0],\"dir\": [-1, 0, 0],\"rot\": [0, 0, 1.00001],\"depth\": 6}}";   // good
const std::string t5 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0],\"dir\": [-1, 0, 0],\"rot\": [0, 0],\"depth\": 6}}";            // bad
const std::string t6 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0],\"dir\": [-1, 0, 0],\"rot\": [0, 0, 1],\"depeth\": 6}}";        // bad
const std::string t7 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0],\"dir\": [-1, 0, 0],\"rot\": [0, 0, 1],\"depth\": [6]}}";       // bad
const std::string t8 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0],\"dir\": \"a\",\"rot\": [0, 0, 1],\"depth\": 6}}";              // bad

const std::string t9 = "{\"global\":{\"ambient_color\":[1,0,0],\"c\":10}}";
const std::string t10 = "{\"global\":{\"color\":[1,0,0],\"c\":10}}";


int test0(RayEngine *engine) {

    {
        auto [ret,error] = Parser::parse(t0.c_str(), engine);

        cout << "Got code " << ret << " with message [" << error << "]\n";

        if( ret != 0 ) {
            return 1;
        }
    }

    {
        auto [ret,error] = Parser::parse(t1.c_str(), engine);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret == 0 ) {
            return 2;
        }
    }


    return 0;
}

int test1(RayEngine* engine) {

    const unsigned restrictParse = 1;


    {
        auto [ret,error] = Parser::parse(t4.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 0 ) {
            return 3;
        }
    }

    {
        auto [ret,error] = Parser::parse(t5.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 2 ) {
            return 3;
        }
    }

    {
        auto [ret,error] = Parser::parse(t6.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 2 ) {
            return 3;
        }
    }

    {
        auto [ret,error] = Parser::parse(t7.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 2 ) {
            return 3;
        }
    }

    {
        auto [ret,error] = Parser::parse(t8.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 2 ) {
            return 3;
        }
    }

    {
        auto [ret,error] = Parser::parse(t0.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 2 ) {
            return 3;
        }
    }



    return 0;
}

int test2(RayEngine* engine) {
    const unsigned restrictParse = 2;


    {
        auto [ret,error] = Parser::parse(t9.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 0 ) {
            return 3;
        }
    }

    {
        auto [ret,error] = Parser::parse(t10.c_str(), engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 0 ) {
            return 3;
        }
    }


    return 0;
}



int main(void) {
    RayEngine* engine;
    engine = new RayEngine();
    engine->resize(400);

    std::vector<int> results;

    // results.emplace_back(test0(engine));
    // results.emplace_back(test1(engine));
    results.emplace_back(test2(engine));

    unsigned failCount = 0;
    unsigned i = 0;
    for(const auto r : results) {
        if( r ) {
            failCount++;
            cout << "Test #" << i << " Failed";
        }
        i++;
    }

    if( failCount ) {
        cout << "\n" << failCount << " Tests failed\n";
    } else {
        cout << "\nALL Tests passed\n";
    }

}
