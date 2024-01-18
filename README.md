<p align="center"><b>Lumina</b></p>
<p align="center">
  <img src="https://img.shields.io/badge/license-MIT-blue.svg">
  <img src="https://img.shields.io/badge/version-0.1.0-yellow">
  <a href="https://app.codacy.com/gh/kadir014/lumina/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade"><img src="https://app.codacy.com/project/badge/Grade/9556f3db17d54b288557d3b2e9dbf366"></a>
</p>
<p align="center">
Lumina is a lightweight and cross-platform 2D game engine.
</p>



# Roadmap & Future
Lumina is a pretty recent project of mine which I started working over the semester break. Lumina is a latin origin word, meaning *"light"*. It is built on top of the brilliant SDL2 library. I want the game engine to be able to run (and build) easily on Android as well as desktop and web.



# Installing & Building

### Building for desktop
**❗ Prerequisite**: Make sure you have GCC / MinGW installed.

Clone (or download) the repository
```
$ git clone https://github.com/kadir014/lumina.git
```

Set working directory to Lumina
```
$ cd /path/to/lumina/
```

Run the build script. It will build the game engine and the basic example, then run it if succesful.
```
$ python build.py
```

### Building for web
**❗ Prerequisite**: Make sure you have Emscripten installed. ([Installing guide](https://emscripten.org/docs/getting_started/downloads.html))

Clone (or download) the repository
```
$ git clone https://github.com/kadir014/lumina.git
```

Set working directory to Lumina
```
$ cd /path/to/lumina/
```

Run the build script with `web` argument. It will build the game engine and the basic example, then host a local webserver where you can test the game on `localhost:8000`.
```
$ python build.py web
```




# Examples

Example demos are in [examples](https://github.com/kadir014/lumina/blob/main/examples/) directory.



# License
[MIT](LICENSE) © Kadir Aksoy