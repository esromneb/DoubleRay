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

    std::vector<unsigned char> imageBuf;

    // cout << "Before copy\n";
    engine->copyToPixels(imageBuf);
    // cout << "After copy\n";

    return encodeOneStepp(path.c_str(), imageBuf, engine->xPx, engine->yPx);
}



/// Decode from disk to raw pixels with a single function call
/// the Pixels in the vector are 4 bytes per pixel, ordered RGBARGBA...
///
static std::tuple<unsigned,std::string> decodeOneStep(const char* filename, std::vector<unsigned char>& image,  png_size_t& sz) {
    // std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    std::string s = "";

    //if there's an error, display it
    if(error) {
        s = "PNG decoder error #" + std::to_string(error) + ": " + std::string(lodepng_error_text(error));
        std::cout << s << "\n";
    } else {
        sz = std::make_tuple(width, height);
    }

    return std::make_tuple(error, s);
}

std::tuple<unsigned,std::string> HandlePng::load(const std::string& path, std::vector<unsigned char>& image,  png_size_t& sz) {
    // int error = 0;
    // std::string s = "";
    return decodeOneStep(path.c_str(), image, sz);
}
