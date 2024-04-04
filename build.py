#!/usr/bin/python
# -*- coding: UTF-8 -*-
import argparse
from typing import List
from builder import Builder, CMakeBuilder, CMakeWindowsVsMsvcBuilder, CMakeAndroidBuilder

def get_args() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Build and install the project")
    parser.add_argument("--platform", help="Build the project", default="Windows", choices=["Windows", "Android", "Linux"])
    parser.add_argument("--clean", action="store_true", help="Clean the build directory")
    parser.add_argument("--example", action="store_true", help="Build the example")
    args = parser.parse_args()
    return args

def get_builder(args) -> Builder:
    if args.platform == "Windows":
        return CMakeWindowsVsMsvcBuilder("build", "output")
    elif args.platform == "Android":
        return CMakeAndroidBuilder("build", "output")
    else:
        return CMakeBuilder("build", "output")
    
def get_options(args) -> List[str]:
    options = []
    if args.example:
        options += ["-DENABLE_EXAMPLE=ON"]
    return options

if __name__ == "__main__":
    args = get_args()
    builder = get_builder(args)
    options = get_options(args)
    if args.clean:
        builder.clean()
        exit(0)
    builder.build(options)
    builder.install()
