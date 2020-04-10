# Publish Gh Pages
To publish github pages, get to the version you want to publish.

* Edit `proxy_controls.html` and set `doPublicRender` to true.
* Verify `Makefile` has `O3`

Run
```bash
make copy wasm
```

