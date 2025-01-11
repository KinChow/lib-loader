#!/usr/bin/env python3
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
from enum import Enum
from typing import List
from builder import Builder, BuilderType, BuilderFactory


class Platform(Enum):
    WINDOWS = "Windows"
    ANDROID = "Android"
    LINUX = "Linux"


def get_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Build and install the project")
    parser.add_argument(
        "--platform",
        type=Platform,
        choices=list(Platform),
        default=Platform.WINDOWS,
        help="Build platform"
    )
    parser.add_argument(
        "--clean",
        action="store_true",
        help="Clean the build directory"
    )
    parser.add_argument(
        "--prefix",
        default="",
        help="Prefix path of compiler"
    )
    parser.add_argument(
        "--example",
        action="store_true",
        help="Build the example"
    )
    args = parser.parse_args()
    return args


def get_builder(args: argparse.Namespace) -> Builder:
    builder_map = {
        Platform.ANDROID: (BuilderType.CMAKE_ANDROID, "build"),
        Platform.WINDOWS: (BuilderType.CMAKE_WINDOWS_VS_MSVC, "build"),
        Platform.LINUX: (BuilderType.CMAKE_GCC, "build", args.prefix),
    }
    builder_type, *builder_args = builder_map.get(args.platform, (None,))
    return BuilderFactory.create(builder_type, *builder_args) if builder_type else None


def get_options(args) -> List[str]:
    options = []
    if args.example:
        options += ["-DENABLE_EXAMPLE=ON"]
    return options


def main():
    args = get_args()
    builder = get_builder(args)

    if not builder:
        print("Unsupported platform")
        return 1

    if args.clean:
        builder.clean()
        return 0

    options = get_options(args)
    builder.build(options)
    return 0


if __name__ == "__main__":
    exit(main())
