#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import os.path
import subprocess
path = os.getcwd()

# excluded_directories = ["/build/generated/", "cmake-build-debug/", "cmake-build-release", "CMakeFiles"]
included_directories = ["Demos", "Components"]
exclude_patterns = ["tgaimage","build","3rdparty","Libraries"]
for root, dirs, files in os.walk(path):
    # if any(excluded_dir in root for excluded_dir in excluded_directories):
    #     continue
    if not any(included_dir in root for included_dir in included_directories):
        continue
    for name in files:
        if name.endswith((".h", ".c", ".inl", ".hpp", ".cpp")):
            localpath = os.path.join(root, name)
            if any(pattern in localpath.lower() for pattern in exclude_patterns):
                continue
            print(localpath)
            subprocess.run(["clang-format", "-i", localpath, "-style=File"], check=True)