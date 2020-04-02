#include "Vec3.hpp"
#include "Parser.hpp"
#include "RayEngine.hpp"
#include "HandlePng.hpp"

#include "lodepng.h"
#include "CLI11.hpp"

#include <iostream>
#include <cmath>
#include <string>
#include <cstdint>
#include <chrono>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;


// Annoying but required for now in the tests until we fix the RayApi
extern "C" {
void doRenderOfficial() {
}
}


// returns a list of paths to scenes that are under test
std::vector<std::string> getAllScenes(void) {
    std::vector<std::string> out;

    const std::string folder = "scenes/";

    out.emplace_back(folder + "test_shadow_2.json");
    out.emplace_back(folder + "test_shadow_3.json");
    out.emplace_back(folder + "refraction_7.json");
    out.emplace_back(folder + "refraction_9.json");
    out.emplace_back(folder + "refraction_shadow_3.json");
    out.emplace_back(folder + "refraction_shadow_4.json");
    out.emplace_back(folder + "soap_bubble_1.json");
    out.emplace_back(folder + "color_balls_refraction_2.json");
    out.emplace_back(folder + "cool_reflection_1.json");
    out.emplace_back(folder + "hit_order_1.json");
    out.emplace_back(folder + "three_color_balls_yellow.json");

    return out;
}



//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

// int test0(RayEngine *engine) {



//     return 0;
// }


void localRender(RayEngine* engine) {
    const auto start = std::chrono::steady_clock::now();
    engine->render();
    const auto end = std::chrono::steady_clock::now();


    if( true ) {
        const size_t elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>( 
            end - start
        ).count();
        const double elapsed_ms = elapsed_us / 1000.0;
        cout << "Render took " << elapsed_ms << "ms" << "\n";
    }
}


std::string p0 = "scenes/test_shadow_3.json";
std::string p1 = "scenes/test_shadow_2.json";

int test0(RayEngine* engine) {
    const unsigned restrictParse = 0;


    {
        auto [ret,error] = Parser::parseFile(p0, engine, restrictParse);

        cout << "Got code " << ret << " with message [" << error << "]\n";
        if( ret != 0 ) {
            return 3;
        }

        localRender(engine);


        const uint32_t px = 400;

        std::vector<unsigned char> imageBuf;
        imageBuf.reserve(px*px*4);




        auto scale = RayEngine::scale;
        float gain = 1.1;


        for( int y = 0; y < px; y++ ) {
            for( int x = 0; x < px; x++ ) {
                // const auto lookup = x+y*px;
                const auto lookup = x+((px-1)-y)*px;
                float r = engine->r[lookup];
                float g = engine->g[lookup];
                float b = engine->b[lookup];
                float rs = gain + (r / scale);
                float gs = gain + (g / scale);
                float bs = gain + (b / scale);

                uint8_t rb = (rs > 0) ? ( (rs>=255) ? 255 : rs ) : (0);
                uint8_t gb = (gs > 0) ? ( (gs>=255) ? 255 : gs ) : (0);
                uint8_t bb = (bs > 0) ? ( (bs>=255) ? 255 : bs ) : (0);

                imageBuf.emplace_back(rb);
                imageBuf.emplace_back(gb);
                imageBuf.emplace_back(bb);
                imageBuf.emplace_back(255);

                // *((Uint32*)screen->pixels + ((px-1-y) * px) + x) = SDL_MapRGBA(screen->format, rb, gb, bb, 255);


            }
        }

        encodeOneStep("img/test/test_shadow_3.png", imageBuf, px, px);

    }


    return 0;
}


int test1(RayEngine* engine) {

    {
        auto [ret,error] = Parser::parseFile(p1, engine);

        cout << "PARSE Got code " << ret << " with message [" << error << "]\n";
        if( ret != 0 ) {
            return 3;
        }

        localRender(engine);

        std::string savePath = "img/test/test_shadow_3.png";

        auto [ret2,error2] = HandlePng::save(savePath, engine);

        cout << "PNG Got code " << ret2 << " with message [" << error2 << "]\n";
        if( ret2 != 0 ) {
            return 4;
        }



    }

    return 0;
}





int main2(void) {
    RayEngine* engine;
    engine = new RayEngine();
    engine->resize(400);

    std::vector<int> results;

    // results.emplace_back(test0(engine));
    results.emplace_back(test1(engine));
 

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

    return 0;
}

std::string stripPath(const std::string& s1) {
    const auto int w = s1.find_last_of("\\/");

    // cout << "found w " << w << "\n";

    if( w == string::npos ) {
        return s1;
    } else {
        return s1.substr(w+1, s1.size()-w);
    }
}

std::string stripExtension(const std::string& s1) {
    const auto int w = s1.find_last_of(".");

    if( w == string::npos ) {
        return s1;
    } else {
        return s1.substr(0, w);
    }
}

std::string outputPathForInput(const std::string& s1) {
    const auto noPath = stripPath(s1);

    const auto noExtension = stripExtension(noPath);

    return "img/test/" + noExtension + ".png";
}


void batchRender(const std::vector<std::string>& paths, const bool cleanBetween) {

    RayEngine* engine;
    if( !cleanBetween ) {
        engine = new RayEngine();
        engine->resize(400);
    }

    for(const auto& p : paths ) {
        if( cleanBetween ) {
            // leak the old one for now
            engine = new RayEngine();
            engine->resize(400);
        }

        const auto outputPath = outputPathForInput(p);

        cout << "Rendering " << p << " to " << outputPath << "\n";

        auto [ret,error] = Parser::parseFile(p, engine);

        // cout << "PARSE Got code " << ret << " with message [" << error << "]\n";
        if( ret != 0 ) {
            cout << "File: " << p << " failed with " << error << "\n";
            continue;
        }

        localRender(engine);

        // std::string savePath = "img/test/test_shadow_3.png";

        auto [ret2,error2] = HandlePng::save(outputPath, engine);

        // cout << "PNG Got code " << ret2 << " with message [" << error2 << "]\n";
        if( ret2 != 0 ) {
            cout << "Writin file to disk " << outputPath << " failed with " << error2 << "\n";
        }
    }
}



int main(int argc, char** argv) {
    CLI::App app{"Engine Unit Test using PNGs"};


    bool exitAfterOptions = false;

    bool renderAll = false;
    bool renderOne = false;
    std::string onePath;
    bool cleanEngine = false;
    bool randomizeList = false;


    auto buildAllCb = [&](const std::int64_t count) {
        renderAll = true;
        // cout << "In lambda C with count " << count << "\n";
    };
    app.add_flag_function("-a", buildAllCb,
        "Build all scenes");


    auto buildOneCb = [&](const std::string oneScene) {
        renderOne = true;
        // cout << "In lambda S with " << oneScene << "\n";
        onePath = oneScene;
    };
    app.add_option_function<std::string>("-s", buildOneCb, 
        "Build one scene (path to json file)");


    auto cleanCb = [&](const std::int64_t count) {
        cleanEngine = true;
    };
    app.add_flag_function("-c", cleanCb,
        "Clean Engine betweeen builds");

    auto rndCb = [&](const std::int64_t count) {
        randomizeList = true;
    };
    app.add_flag_function("-r", rndCb,
        "Randomize order scenes are rendered");


    auto dumpScenesCb = [&](const std::int64_t count) {
        // renderAll = true;
        // cout << "In lambda C with count " << count << "\n";
        exitAfterOptions = true;
        auto all = getAllScenes();
        for(const auto&s : all) {
            cout << s << "\n";
        }
    };
    app.add_flag_function("--dump", dumpScenesCb,
        "Dump scenes that will be run with -a");



    // If you pass --help, this macro will exit and no code
    // below it will run
    CLI11_PARSE(app, argc, argv);

    if( exitAfterOptions ) {
        return 0;
    }

    if( !renderAll && !renderOne ) {
        cout << "Dumping because no options\n";
        cout << app.help();
        return 0;
    }

    if( renderAll && renderOne) {
        cout << "\nPlease specify either -a or -s but not both\n\n";
        cout << app.help();
        return 0;
    }


    std::vector<std::string> paths = renderOne ? std::vector<std::string>{onePath} : getAllScenes();

    if( randomizeList ) {
        std::srand ( unsigned ( std::time(0) ) );
        // Shuffel list using built-in random generator
        std::random_shuffle ( paths.begin(), paths.end() );
    }


    batchRender(paths,cleanEngine);




    return 0;
}





    // app.add_option_function<void>("-c",
    //            lc,
    //            "lambda call void");

    // bool defaultA = false;
    // app.add_option("-a", defaultA, "Build All Scenes");
