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

open ray2.html in firefox (chrome is slower for me)


Notes
===
My initial version hand modifies the output (ray.html) and calls it (ray2.html).





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

