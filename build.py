import sys
import os
import shutil
import subprocess
import platform
from time import perf_counter
from pathlib import Path
from http.server import SimpleHTTPRequestHandler
from socketserver import ThreadingTCPServer


IS_WIN = platform.system() == "Windows"


BASE_PATH = Path(os.getcwd())
BUILD_PATH = BASE_PATH / "build"
SRC_PATH = BASE_PATH / "src"
INCLUDE_PATH = BASE_PATH / "include"
EXAMPLES_PATH = BASE_PATH / "examples"

BUILD_FOR_WEB = "web" in sys.argv


if os.path.exists(BUILD_PATH):
    shutil.rmtree(BUILD_PATH)

os.mkdir(BUILD_PATH)
os.chdir(BUILD_PATH)


srcs = [
    EXAMPLES_PATH / "bouncing.c"
]

for root, _, files in os.walk(SRC_PATH):
    for file in files:
        if file.endswith(".c"):
            srcs.append(os.path.join(root, file))

includes = [
    INCLUDE_PATH,
    BASE_PATH / "deps" / "include"
]


HTML_TEMPLATE = """
<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>Lumina Game</title>

    <style>
        html, body {
            margin: 0;
            padding: 0;
        }
    </style>
</head>

<body>
    <canvas id="canvas" oncontextmenu="event.preventDefault()" tabindex=-1></canvas>

    <script type="text/javascript">
        var Module = {
            canvas: (function() {return document.getElementById("canvas");})()
        };
    </script>

    <script src="index.js"></script>
</body>

</html>
"""


if BUILD_FOR_WEB:
    print("Building for web.\n")

    with open("index.html", "w", encoding="utf-8") as index_html:
        index_html.write(HTML_TEMPLATE)

    compiler = "emcc"
    options = "-std=gnu11 -g3 -Wall"
    extensions = "-sUSE_SDL=2 -sUSE_SDL_TTF=2 -sUSE_SDL_IMAGE=2"
    formats = "-sSDL2_IMAGE_FORMATS=[\"bmp\",\"png\",\"jpg\"]"
    preload = "../examples/assets@/assets"
    em_settings = f"-sWASM=1 -sEXIT_RUNTIME {extensions} {formats} --preload-file {preload}"

    compile_command = f"{compiler} {options} -o index.js {' '.join(str(i) for i in srcs)} -I{' -I'.join(str(i) for i in includes)} {em_settings}"
    print(compile_command)

    start = perf_counter()
    out = subprocess.run(compile_command, shell=True)
    end = perf_counter()

    print(f"\nCompilation finished in {round(end - start, 2)}s.")

    if out.returncode == 0:
        port = 8000
        httpd = ThreadingTCPServer(("", port), SimpleHTTPRequestHandler)
        address = "localhost"

        print(f"Starting HTTP server on http://{address}:{port}")

        try:
            httpd.serve_forever()
        
        except KeyboardInterrupt:
            print("Keyboard interrupt received, exiting.")
            os._exit(0)

else:
    print("Building for desktop.\n")

    compiler = "gcc"
    options = "-std=gnu11 -O3 -Wall"
    if IS_WIN:
        binary = "lumina_game.exe"
    else:
        binary = "lumina_game"

    libs = [
        BASE_PATH / "deps" / "lib" / "SDL2",
        BASE_PATH / "deps" / "lib" / "SDL2_ttf",
        BASE_PATH / "deps" / "lib" / "SDL2_image"
    ]

    links = "-lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image"

    compile_cmd = f"{compiler} {options} -o {binary} {' '.join(str(i) for i in srcs)} -I{' -I'.join(str(i) for i in includes)} -L{' -L'.join(str(i) for i in libs)} {links}"
    print(compile_cmd)

    start = perf_counter()
    result = subprocess.run(compile_cmd, shell=True)
    end = perf_counter()

    print(f"\nCompilation finished in {round(end - start, 2)}s.")

    if os.path.exists(binary):
        if IS_WIN:
           shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2" / "SDL2.dll", BUILD_PATH / "SDL2.dll")
           shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2_ttf" / "SDL2_ttf.dll", BUILD_PATH / "SDL2_ttf.dll")
           shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2_image" / "SDL2_image.dll", BUILD_PATH / "SDL2_image.dll")

        os.mkdir(BUILD_PATH / "assets")
        for *_, files in os.walk(EXAMPLES_PATH / "assets"):
            for file in files:
                shutil.copyfile(
                    EXAMPLES_PATH / "assets" / file,
                    BUILD_PATH / "assets" / file
                )

        if IS_WIN:
            result = subprocess.run(binary)
        else:
            result = subprocess.run(f"./{binary}")
        print(f"{binary} exited with code {result.returncode}")
