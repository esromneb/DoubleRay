#include "HandlePng.hpp"
#include "RayEngine.hpp"

#include "lodepng.h"

#include <iostream>
// #include <cmath>
#include <string>
#include <cstdint>
#include <chrono>




//The image argument has width * height RGBA pixels or width * height * 4 bytes
static std::tuple<unsigned,std::string> encodeOneStepp(const char* const filename, std::vector<unsigned char>& image, const unsigned width, const unsigned height) {
    //Encode the image
    const unsigned error = lodepng::encode(filename, image, width, height);

    std::string s = "";

    //if there's an error, display it
    if(error) {
        s = "PNG encoder error #" + std::to_string(error) + ": " + std::string(lodepng_error_text(error));
        std::cout << s << "\n";
    }

    return std::make_tuple(error, s);
}


///
/// Saves the engine's current render buffer to a png file on disk
///
std::tuple<unsigned,std::string> HandlePng::save(const std::string& path, RayEngine* engine) {

    // FIXME
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

    return encodeOneStepp(path.c_str(), imageBuf, px, px);

}
