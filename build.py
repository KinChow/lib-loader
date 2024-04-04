#!/usr/bin/python
# -*- coding: UTF-8 -*-

# Copyright (c) 2024, Zhou Zijian

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
    # builder.install()
