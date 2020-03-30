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




See Also
===
* https://emscripten.org/docs/compiling/Deploying-Pages.html - emscripten instructions for custom html
* https://blog.scottlogic.com/2014/03/12/native-code-emscripten-webgl-simmer-gently.html - webgl
* https://compile.fi/canvas-filled-three-ways-js-webassembly-and-webgl/ - 3 ways to canvas
* https://github.com/mtharrison/wasm-raytracer - a working wasm raytracer
* http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/ - ray sphere intersection
* https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
* https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF - phong


Notes
===
Last version with my canvas and emscripten official canvas is in templates/both.html
