
# Build Quirks

Due to how emscripted operates, we pass it a shell file.  In the shell file is the line `{{{ SCRIPT }}}`.

* In dev and gh pages mode, we let this all happen.  emcc writes code into ray.html
* In module (the dist folder for npm).  We don't use ray.html at all as the user will use their own.  We capture the contents of this script
