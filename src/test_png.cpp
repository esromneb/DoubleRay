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

// using namespace std;

using std::cout;
using std::endl;
using std::min;
using std::max;


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
    out.emplace_back(folder + "test_scale_1.json");
    out.emplace_back(folder + "specular_diffuse_test.json");
    out.emplace_back(folder + "false_color_reflection_1.json");
    out.emplace_back(folder + "alpha_3.json");

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


std::string stripPath(const std::string& s1) {
    const auto w = s1.find_last_of("\\/");

    // cout << "found w " << w << "\n";

    if( w == string::npos ) {
        return s1;
    } else {
        return s1.substr(w+1, s1.size()-w);
    }
}

std::string stripExtension(const std::string& s1) {
    const auto w = s1.find_last_of(".");

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

std::string idealPathForInput(const std::string& s1) {
    const auto noPath = stripPath(s1);

    const auto noExtension = stripExtension(noPath);

    return "img/ideal/" + noExtension + ".png";
}


void batchRender(const std::vector<std::string>& paths, const bool cleanBetween, const bool skipWrite) {

    RayEngine* engine;
    if( !cleanBetween ) {
        engine = new RayEngine();
        engine->resize(400,400);
    }

    for(const auto& p : paths ) {
        if( cleanBetween ) {
            // leak the old one for now
            engine = new RayEngine();
            engine->resize(400,400);
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

        if( skipWrite ) {
            continue;
        }

        // std::string savePath = "img/test/test_shadow_3.png";

        auto [ret2,error2] = HandlePng::save(outputPath, engine);

        // cout << "PNG Got code " << ret2 << " with message [" << error2 << "]\n";
        if( ret2 != 0 ) {
            cout << "Writin file to disk " << outputPath << " failed with " << error2 << "\n";
        }
    }
}



// xl,xh,yl,yh,count

// low should be = 
// and high should be <=
// this is a datatype which records a square region of the image
// and records how many different pixels we found there between test and ideal
// the idea is to make it more simple for me to identify regions of changes between images
typedef std::tuple<unsigned,unsigned,unsigned,unsigned,unsigned,int,int,int> blemish_t;

bool _blin(const unsigned x, const unsigned xl, const unsigned xh) {
    if( x >= xl && x <= xh) {
        return true;
    }
    return false;
}


bool blin(const unsigned x, const unsigned xl, const unsigned xh, const unsigned tol) {
    return _blin(x, max(0,(signed)xl-(signed)tol), xh+tol);
}


blemish_t growBlem(
    const blemish_t& b,
    const unsigned x,
    const unsigned y,
    const int dr,
    const int dg,
    const int db ) {
    const auto [xl,xh,yl,yh,count,edr,edg,edb] = b;

    return std::make_tuple(
        min(x,xl),
        max(x,xh),
        min(y,yl),
        max(y,yh),
        count+1,
        edr+dr,
        edg+dg,
        edb+db
        );
}



void addBlemish(
    std::vector<blemish_t>& blem,
    const unsigned x,
    const unsigned y,
    const int dr = 0,
    const int dg = 0,
    const int db = 0,
    const unsigned tol = 10
    ) {

    bool addNew = true;

    for(unsigned i = 0; i < blem.size(); i++ ) {
        auto search = blem[i];
        const auto [xl,xh,yl,yh,count,dnc0,dnc1,dnc2] = search;
        if( blin(x, xl, xh, tol) && blin(y, yl, yh, tol) ) {
            blem[i] = growBlem(search, x, y,dr,dg,db);
            addNew = false;
            break;
        }
    }

    if(addNew) {
        blem.emplace_back(x,x,y,y,1,dr,dg,db);
        return;
    }
}

void reportBlemish(const std::vector<blemish_t>& blem) {
    for(const auto& w : blem) {
        const auto [xl,xh,yl,yh,count,dr,dg,db] = w;
        const double _ar = ((double)(dr) / count);
        const double _ag = ((double)(dg) / count);
        const double _ab = ((double)(db) / count);
        const double ar = ((int)((_ar*10)+0.5))/10.0;
        const double ag = ((int)((_ag*10)+0.5))/10.0;
        const double ab = ((int)((_ab*10)+0.5))/10.0;
        cout << "Region: x: [" << xl << "," << xh << "] y: [" << yl << "," << yh
             << "] with " << count << " pixels, average [" << ar << "," << ag << "," << ab << "]\n";
    }
}

std::tuple<int,std::string> compareImages(
    const std::vector<unsigned char>& ideal, const png_size_t& ideal_sz,
    const std::vector<unsigned char>& test, const png_size_t& test_sz,
    const bool printAllValues = false
    ) {
    if( ideal_sz == test_sz ) {
        // cout << "Sizes match\n";
    } else {
        return std::make_tuple(1, "Different sized images");
    }

    std::string msg;

    const auto [fx,fy] = ideal_sz;

    const unsigned end = fx*fy*4;

    unsigned total = 0;


    std::vector<blemish_t> blem;
    // int px = 2;

    unsigned char ir;
    unsigned char ib;
    unsigned char ig;
    unsigned char ia;
    unsigned char tr;
    unsigned char tb;
    unsigned char tg;
    unsigned char ta;

    for(unsigned i = 0; i < end; i+=4) {


        ir = ideal[i+0];
        ig = ideal[i+1];
        ib = ideal[i+2];
        ia = ideal[i+3];

        tr = test [i+0];
        tg = test [i+1];
        tb = test [i+2];
        ta = test [i+3];

        bool mismatch = true;

        if( ir==tr && ig==tg && ib==tb && ia==ta ) {
            mismatch = false;
        }

        if( mismatch ) {
            total++;
            const int p = (i / 4);
            const int y = (fy-1) - (p / fy);
            const int x = p % fx;

            addBlemish(
                blem,
                x,
                y,
                (signed)tr-(signed)ir,
                (signed)tg-(signed)ig,
                (signed)tb-(signed)ib
                );

            if( printAllValues ) {
                cout << "[" << x << "," << y << "]: ";
                if( ia != ta ) {
                    cout << "[" << (int)ir << " " << (int)ig << " " << (int)ib << " " << (int)ia << "] [" << (int)tr << " " << (int)tg << " " << (int)tb << " " << (int)ta  << "]\n";
                } else {
                    cout << "[" << (int)ir << " " << (int)ig << " " << (int)ib << "] [" << (int)tr << " " << (int)tg << " " << (int)tb << "]\n";
                }
            }
        }
    }

    if( total ) {
        msg += "Total Different Pixels: " + std::to_string(total) + "\n";
        cout << "\n";
        reportBlemish(blem);

        return std::make_tuple(1, msg);
    }


    return std::make_tuple(0, "");
}

int batchCompare(const std::vector<std::string>& paths, const bool printAllValues = false) {

    bool allComparePassed = true;

    for(const auto& p : paths ) {
        const auto testPath = outputPathForInput(p);
        const auto idealPath = idealPathForInput(p);

        const bool printLoadSz = false;
        const bool printFullPathCompare = false;

        if( printFullPathCompare ) {
            cout << "Comparing " << testPath << " against " << idealPath << "\n";
        } else {
            cout << "Comparing " << testPath << "\n";
        }

        std::vector<unsigned char> ideal;
        std::vector<unsigned char> test;

        png_size_t ideal_sz;
        png_size_t test_sz;

        unsigned ret;
        std::string error;

        std::tie(ret,error) = HandlePng::load(idealPath, ideal, ideal_sz);
        if( ret != 0 ) {
            cout << "File: " << idealPath << " failed to load with " << error;
            return 1;
        } else {
            auto [x,y] = ideal_sz;
            if( printLoadSz ) {
                cout << "loaded with size " << x << ", " << y << "\n";
            }
        }


        std::tie(ret,error) = HandlePng::load(testPath, test, test_sz);
        if( ret != 0 ) {
            cout << "File: " << testPath << " failed to load with " << error;
            return 2;
        } else {
            auto [x,y] = test_sz;
            if( printLoadSz ) {
                cout << "loaded with size " << x << ", " << y << "\n";
            }
        }



        std::tie(ret,error) = compareImages(ideal, ideal_sz, test, test_sz, printAllValues);
        if( ret != 0 ) {
            cout << "  Compare Failed: " << error << "\n";
            allComparePassed = false;
        } else {
            cout << "  Compare Passed\n";
        }
    }

    if( allComparePassed ) {
        return 0;
    } else {
        return 3;
    }

}



int main(int argc, char** argv) {
    CLI::App app{"Engine Unit Test using PNGs"};


    bool exitAfterOptions = false;

    // only one of these is allowed
    bool renderAll = false;
    bool renderOne = false;
    bool compareOnly = false;
    bool compareAndRender = false;
    bool printAllValues = false;
    bool skipWrite = false;


    std::string onePath;

    // any combination is fine
    bool newEnginePerRender = false;
    bool randomizeList = false;


    auto buildAllCb = [&](const std::int64_t count) {
        (void)count;
        renderAll = true;
        // cout << "In lambda C with count " << count << "\n";
    };
    app.add_flag_function("-a", buildAllCb,
        "Build all scenes");


    auto buildOneCb = [&](const std::string oneScene) {
        renderOne = true;
        onePath = oneScene;
    };
    app.add_option_function<std::string>("-s", buildOneCb, 
        "Build one scene (path to json file)");

    auto compareOnlyCb = [&](const std::int64_t count) {
        (void)count;
        compareOnly = true;
    };
    app.add_flag_function("-c", compareOnlyCb,
        "Compare png images");

    auto compareAndRenderCb = [&](const std::int64_t count) {
        (void)count;
        compareAndRender = true;
    };
    app.add_flag_function("-g", compareAndRenderCb,
        "Build, then compare png images");

    auto printAllValuesCb = [&](const std::int64_t count) {
        (void)count;
        printAllValues = true;
    };
    app.add_flag_function("-p", printAllValuesCb,
        "Print every pixel value that does not match during compare");


    auto cleanCb = [&](const std::int64_t count) {
        (void)count;
        newEnginePerRender = true;
    };
    app.add_flag_function("-n", cleanCb,
        "Call new() RayEngine betweeen builds");

    auto rndCb = [&](const std::int64_t count) {
        (void)count;
        randomizeList = true;
    };
    app.add_flag_function("-r", rndCb,
        "Randomize order scenes are rendered");

    auto skipCb = [&](const std::int64_t count) {
        (void)count;
        skipWrite = true;
    };
    app.add_flag_function("--skip", skipCb,
        "Skip writing png to disk");


    auto dumpScenesCb = [&](const std::int64_t count) {
        (void)count;
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
        cout << "Quitting because I need -a or -s\n";
        cout << app.help();
        return 0;
    }

// for (std::vector v{1, 2, 3}; auto& e : v) {
//   std::cout << e;
// }
    unsigned optCount = 0;
    const std::vector opts{renderAll,renderOne};
    for(auto b : opts) {
        if( b ) {
            optCount++;
        }
        // cout << "Bool: " << (b?"true":"false") << "\n";
    }

    if( optCount > 2 ) {
        cout << "\nPlease specify only one of [-a -s]\n\n";
        cout << app.help();
        return 1;
    }




    std::vector<std::string> paths = renderOne ? std::vector<std::string>{onePath} : getAllScenes();

    if( randomizeList ) {
        std::srand ( unsigned ( std::time(0) ) );
        // Shuffel list using built-in random generator
        std::random_shuffle ( paths.begin(), paths.end() );
    }

    if( compareAndRender ) {
        if( compareOnly ) {
            cout << "Please note that -c is implied when -g is used\n";
        }
        cout << "Render First\n";
        batchRender(paths,newEnginePerRender, skipWrite);
        cout << "Then Compare\n";
        return batchCompare(paths, printAllValues);
    }
    if( compareOnly ) {
        cout << "Do compare\n";
        if( newEnginePerRender ) {
            cout << "Please note that -n has no effect when -c is used\n";
        }
        return batchCompare(paths, printAllValues);
    } else if( renderAll || renderOne ) {
        batchRender(paths,newEnginePerRender, skipWrite);
    } else {
        cout << "internal options error\n";
        cout << app.help();
        return 1;
    }






    return 0;
}





    // app.add_option_function<void>("-c",
    //            lc,
    //            "lambda call void");

    // bool defaultA = false;
    // app.add_option("-a", defaultA, "Build All Scenes");




int test2(void) {

    std::vector<blemish_t> blem;

    addBlemish(blem, 0, 10);
    addBlemish(blem, 0, 11);
    addBlemish(blem, 0, 12);
    addBlemish(blem, 0, 13);
    addBlemish(blem, 3, 13);
    // addBlemish(blem, 12, 13);

    addBlemish(blem, 13, 10);

    reportBlemish(blem);

    return 0;
}


int test3(void) {
    std::vector<blemish_t> b;

    addBlemish(b,349,227);
    addBlemish(b,350,227);
    addBlemish(b,351,227);
    addBlemish(b,352,227);
    addBlemish(b,353,227);
    addBlemish(b,354,227);
    addBlemish(b,355,227);
    addBlemish(b,344,226);
    addBlemish(b,345,226);
    addBlemish(b,22,23);
    addBlemish(b,23,23);
    addBlemish(b,24,23);
    addBlemish(b,22,22);
    addBlemish(b,23,22);
    addBlemish(b,24,22);
    addBlemish(b,22,21);
    addBlemish(b,23,21);
    addBlemish(b,24,21);

    reportBlemish(b);

    if( b.size() != 2 ) {
        cout << "Blemish classification wrong\n";
        return 1;
    }

    return 0;
}

int test4(void) {
    std::vector<blemish_t> b;
    addBlemish(b,0,399);
    addBlemish(b,1,399);

    reportBlemish(b);

    if( b.size() != 1 ) {
        cout << "Blemish classification wrong\n";
        return 1;
    }

    return 0;
}





int main2(void) {

    std::vector<int> results;

    // results.emplace_back(test2());
    // results.emplace_back(test3());
    results.emplace_back(test4());
 

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
