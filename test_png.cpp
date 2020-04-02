#include "Vec3.hpp"
#include "Parser.hpp"
#include "RayEngine.hpp"
#include "HandlePng.hpp"

#include "lodepng.h"

#include <iostream>
#include <cmath>
#include <string>
#include <cstdint>
#include <chrono>

using namespace std;


// Annoying but required for now in the tests until we fix the RayApi
extern "C" {
void doRenderOfficial() {
}
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





int main(void) {
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

}
