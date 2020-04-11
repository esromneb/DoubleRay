# Publish Gh Pages
To publish github pages, get to the version you want to publish.

* Edit `proxy_controls.html` and set `doPublicRender` to true.
* Verify `Makefile` has `O3`

Run
```bash
OPT3=1 make copy wasm
git symbolic-ref HEAD refs/heads/gh-pages
git reset
rm .gitignore
git add out
```

Commit from here


To get back to master:

```bash
git symbolic-ref HEAD refs/heads/master
git reset
git checkout .gitignore
```

