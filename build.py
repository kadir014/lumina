import sys
import os
import shutil
import subprocess
from time import perf_counter
from pathlib import Path


BASE_PATH = Path(os.getcwd())
BUILD_PATH = BASE_PATH / "build"
SRC_PATH = BASE_PATH / "src"
INCLUDE_PATH = BASE_PATH / "include"
EXAMPLES_PATH = BASE_PATH / "examples"


if os.path.exists(BUILD_PATH):
    shutil.rmtree(BUILD_PATH)

os.mkdir(BUILD_PATH)
os.chdir(BUILD_PATH)

if "examples" in sys.argv:
    compiler = "gcc"
    options = "-std=gnu11 -g3 -Wall"
    binary = "-o lumina_example.exe"

    srcs = [
        EXAMPLES_PATH / 'basic.c'
    ]

    for root, _, files in os.walk(SRC_PATH):
        for file in files:
            if file.endswith(".c"):
                srcs.append(os.path.join(root, file))

    includes = [
        INCLUDE_PATH,
        BASE_PATH / "deps" / "include"
    ]

    libs = [
        BASE_PATH / "deps" / "lib" / "SDL2",
        BASE_PATH / "deps" / "lib" /"SDL2_ttf"
    ]

    links = "-lSDL2main -lSDL2 -lSDL2_ttf"

    compile_cmd = f"{compiler} {options} {binary} {' '.join(str(i) for i in srcs)} -I{' -I'.join(str(i) for i in includes)} -L{' -L'.join(str(i) for i in libs)} {links}"

    print(compile_cmd)
    start = perf_counter()
    result = subprocess.run(compile_cmd)
    end = perf_counter()

    print(f"\nCompilation finished in {round(end - start, 2)}s.")

    if os.path.exists("lumina_example.exe"):
        shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2" / "SDL2.dll", BUILD_PATH / "SDL2.dll")
        shutil.copyfile(BASE_PATH / "deps" / "bin" / "SDL2_ttf" / "SDL2_ttf.dll", BUILD_PATH / "SDL2_ttf.dll")

        result = subprocess.run("lumina_example.exe")
        print(f"lumina_example.exe exited with code {result.returncode}")