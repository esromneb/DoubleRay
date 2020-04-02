Raytracer
===
From UC Davis ECS175


Compile
===
```bash
make
```

Run
===
```bash
cd out
sudo python -m SimpleHTTPServer 80
```

open ray.html in firefox (chrome is slower for me)


Notes
===
We use template/controls.html to generate ray.html





Deps
===
On ubuntu:

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk/
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
realpath ./emsdk_env.sh 
```

Instructions from: https://emscripten.org/docs/getting_started/downloads.html




See Also Ratracing
===
* https://github.com/mtharrison/wasm-raytracer - a working wasm raytracer
* http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/ - ray sphere intersection
* https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
* https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF - phong
* http://paulbourke.net/geometry/reflected/ - reflect ray from normal
* http://viclw17.github.io/2018/08/05/raytracing-dielectric-materials/ - dielectric
* https://www.cs.utah.edu/~lediaev/courses/cs6620/prj14.html - goals
* https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
* https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted
* http://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html - texture mapping

See Also Emscripten
===
* https://emscripten.org/docs/compiling/Deploying-Pages.html - emscripten instructions for custom html
* https://blog.scottlogic.com/2014/03/12/native-code-emscripten-webgl-simmer-gently.html - webgl
* https://compile.fi/canvas-filled-three-ways-js-webassembly-and-webgl/ - 3 ways to canvas
* https://brionv.com/log/2019/10/24/exception-handling-in-emscripten-how-it-works-and-why-its-disabled-by-default/ - exceptions

See Also Offtopic
===
* https://github.com/antimatter15/jsgif
* https://nlohmann.github.io/json/classnlohmann_1_1basic__json_a8a3dd150c2d1f0df3502d937de0871db.html - nlohmann parse without exception 


Libraries Used
===
* https://github.com/nlohmann/json
* https://github.com/lvandeve/lodepng
* https://github.com/CLIUtils/CLI11



Notes
===
Last version with my canvas and emscripten official canvas is in templates/both.html
