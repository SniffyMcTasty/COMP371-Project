# Shader Viewer

## Dependencies

GLEW, GLFW3 and GLU need to be installed with VcPkg: https://vcpkg.io/en/getting-started.html
In order to use VcPkg, you need to include its path to your environment variables.
Make sure your IDE looks towards the installed packages, put `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake` as a CMake argument, `[path to vcpkg]` being your own path to your VcPkg clone.

If using the docker image from https://github.com/tiperiu/COMP371_dockerimage, no need to install dependencies.

## Description

To have a full description and demo of what the code does, please refer to the [self-contained web page](./web/index.html) within this repo.
