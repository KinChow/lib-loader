#!/usr/bin/python
# -*- coding: UTF-8 -*-
import os
from abc import ABCMeta, abstractmethod
import subprocess
import sys
import shutil
from typing import List, Optional


def run_cmd(args: List[str]):
    try:
        print(subprocess.check_output(
            args, shell=False).decode("utf-8", "ignore"))
    except subprocess.CalledProcessError:
        print(f"cmd run failed: {args}")
        sys.exit(-1)


class Builder(metaclass=ABCMeta):
    @abstractmethod
    def build(self, build_options: Optional[List[str]] = None):
        pass

    @abstractmethod
    def clean(self):
        pass

    @abstractmethod
    def install(self):
        pass


class BuilderImpl(Builder):
    def __init__(self, build_dir: str, install_dir: str):
        self.build_dir: str = build_dir
        self.install_dir: str = install_dir

    @abstractmethod
    def build(self, build_options: Optional[List[str]] = None):
        pass

    def clean(self):
        shutil.rmtree(self.build_dir, ignore_errors=True)
        shutil.rmtree(self.install_dir, ignore_errors=True)

    @abstractmethod
    def install(self):
        pass


class NdkBuilder(BuilderImpl):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        env = "ANDROID_NDK"
        if os.getenv(env) is None:
            print(f"{env} is not exist")
            sys.exit(-1)
        ndk_build_tool = os.path.join(os.environ[env], "ndk-build")
        self.build_cmd = [
            ndk_build_tool,
            "V=1",
            f"NDK_OUT={self.build_dir}",
            f"NDK_LIBS_OUT={self.build_dir}",
        ]

    def build(self, build_options: Optional[List[str]] = None):
        if build_options is None:
            build_options = []
        self.build_cmd += build_options
        run_cmd(self.build_cmd)

    def install(self):
        if os.path.exists(self.install_dir):
            shutil.rmtree(self.install_dir)
        shutil.copytree(
            self.build_dir, self.install_dir
        )


class CMakeBuilder(BuilderImpl):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        self.config_cmd = [
            "cmake",
            f"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY={self.install_dir}",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={self.install_dir}",
        ] + ["-B", self.build_dir]
        self.build_cmd = ["cmake", "--build", self.build_dir]

    def build(self, build_options: Optional[List[str]] = None):
        if build_options is None:
            build_options = []
        self.config_cmd += build_options
        run_cmd(self.config_cmd)
        run_cmd(self.build_cmd)

    def clean(self):
        shutil.rmtree(self.build_dir, ignore_errors=True)
        shutil.rmtree(self.install_dir, ignore_errors=True)

    def install(self):
        if os.path.exists(self.install_dir):
            shutil.rmtree(self.install_dir)
        shutil.copytree(
            os.path.join(self.build_dir, self.install_dir), self.install_dir
        )


class CMakeWindowsVsMsvcBuilder(CMakeBuilder):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        self.config_cmd += ["-G", "Visual Studio 17 2022"]


class CMakeWindowsMingwBuilder(CMakeBuilder):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        env = "MinGW"
        if os.getenv(env) is None:
            print(f"{env} is not exist")
            sys.exit(-1)
        self.config_cmd += [
            "-G",
            "Ninja",
            f"-DCMAKE_C_COMPILER:FILEPATH={os.path.join(os.environ[env], 'bin', 'gcc.exe')}",
            f"-DCMAKE_CXX_COMPILER:FILEPATH={os.path.join(os.environ[env], 'bin', 'g++.exe')}",
        ]


class CMakeWindowsClangMsvcBuilder(CMakeBuilder):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        env = "LLVM"
        if os.getenv(env) is None:
            print(f"{env} is not exist")
            sys.exit(-1)
        self.config_cmd += [
            "-G",
            "Ninja",
            f"-DCMAKE_C_COMPILER:FILEPATH={os.path.join(os.environ[env], 'bin', 'clang.exe')}",
            f"-DCMAKE_CXX_COMPILER:FILEPATH={os.path.join(os.environ[env], 'bin', 'clang++.exe')}",
        ]


class CMakeAndroidBuilder(CMakeBuilder):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        env = "ANDROID_NDK"
        if os.getenv(env) is None:
            print(f"{env} is not exist")
            sys.exit(-1)
        cmake_toolchain = os.path.join(
            os.environ[env], "build", "cmake", "android.toolchain.cmake"
        )
        self.config_cmd += [
            "-G",
            "Ninja",
            f"-DCMAKE_TOOLCHAIN_FILE={cmake_toolchain}",
            "-DANDROID_ABI=arm64-v8a",
            "-DANDROID_STL=c++_shared",
            "-DANDROID_PLATFORM=android-31",
        ]


class CMakeOhosBuilder(CMakeBuilder):
    def __init__(self, build_dir: str, install_dir: str):
        super().__init__(build_dir, install_dir)
        env = "OHOS_SDK"
        if os.getenv(env) is None:
            print(f"{env} is not exist")
            sys.exit(-1)
        cmake_toolchain = os.path.join(
            os.environ[env], "build", "cmake", "ohos.toolchain.cmake"
        )
        self.config_cmd += [
            "-G",
            "Ninja",
            f"-DCMAKE_TOOLCHAIN_FILE={cmake_toolchain}",
            "-DANDROID_ABI=arm64-v8a",
            "-DANDROID_STL=c++_shared",
            "-DANDROID_PLATFORM=OHOS",
        ]
