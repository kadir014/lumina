import sys
import os
import shutil
import subprocess
import webbrowser
from time import perf_counter
from pathlib import Path
from http.server import SimpleHTTPRequestHandler
from socketserver import ThreadingTCPServer


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
    EXAMPLES_PATH / "basic.c"
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
    em_settings = "-sWASM=1 -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sEXIT_RUNTIME --preload-file ../examples/assets@/assets"

    compile_command = f"{compiler} {options} -o index.js {' '.join(str(i) for i in srcs)} -I{' -I'.join(str(i) for i in includes)} {em_settings}"
    print(compile_command)

    start = perf_counter()
    out = subprocess.run(compile_command, shell=True)
    end = perf_counter()

    print(f"\nCompilation finished in {round(end - start, 2)}s.")

    if out.returncode == 0:
        port = 8000
        httpd = ThreadingTCPServer(("", port), SimpleHTTPRequestHandler)
        address = httpd.socket.getsockname()

        print(f"Starting HTTP server on {address}:{port}")

        webbrowser.open(f"http://localhost:{port}")

        try:
            httpd.serve_forever()
        
        except KeyboardInterrupt:
            print("Keyboard interrupt received, exiting.")
            os._exit(0)

else:
    print("Building for desktop.\n")

    compiler = "gcc"
    options = "-std=gnu11 -g3 -Wall"
    binary = "lumina_game.exe"

    libs = [
        BASE_PATH / "deps" / "lib" / "SDL2",
        BASE_PATH / "deps" / "lib" /"SDL2_ttf"
    ]

    links = "-lSDL2main -lSDL2 -lSDL2_ttf"

    compile_cmd = f"{compiler} {options} -o {binary} {' '.join(str(i) for i in srcs)} -I{' -I'.join(str(i) for i in includes)} -L{' -L'.join(str(i) for i in libs)} {links}"
    print(compile_cmd)

    start = perf_counter()
    result = subprocess.run(compile_cmd, shell=True)
    end = perf_counter()

    print(f"\nCompilation finished in {round(end - start, 2)}s.")

    if os.path.exists(binary):
        shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2" / "SDL2.dll", BUILD_PATH / "SDL2.dll")
        shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2_ttf" / "SDL2_ttf.dll", BUILD_PATH / "SDL2_ttf.dll")

        os.mkdir(BUILD_PATH / "assets")
        for *_, files in os.walk(EXAMPLES_PATH / "assets"):
            for file in files:
                shutil.copyfile(
                    EXAMPLES_PATH / "assets" / file,
                    BUILD_PATH / "assets" / file
                )

        result = subprocess.run(binary)
        print(f"{binary} exited with code {result.returncode}")