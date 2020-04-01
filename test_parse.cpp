#include "Vec3.hpp"
#include "Parser.hpp"
#include "RayEngine.hpp"

#include <iostream>
#include <cmath>

using namespace std;


const std::string t0 = "{\"global\":{\"ambient_color\":[1,0,0]}}";
const std::string t1 = "{\"global\":{\"ambient_color\":[1,0,0]}";
const std::string t2 = "{\"global\":{\"ambient_color\":[1,0,0]},\"camera\":{\"loc\":[1,0,0]}}";


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


    {
        auto [ret,error] = Parser::parse(t2.c_str(), engine);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret == 0 ) {
            return 3;
        }
    }




    return 0;
}

int test1(RayEngine* engine) {
    return 0;
}

int test2(RayEngine* engine) {
    return 0;
}



int main(void) {
    RayEngine* engine;
    engine = new RayEngine();
    engine->resize(400);

    std::vector<int> results;

    results.emplace_back(test0(engine));
    results.emplace_back(test1(engine));
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
