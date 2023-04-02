# Shader Viewer

## Dependencies

GLEW, GLFW3 and GLU need to be installed with VcPkg: https://vcpkg.io/en/getting-started.html
In order to use VcPkg, you need to include its path to your environment variables.
Make sure your IDE looks towards the installed packages, put `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake` as a CMake argument, `[path to vcpkg]` being your own path to your VcPkg clone.

If using the docker image from https://github.com/tiperiu/COMP371_dockerimage, no need to install dependencies.

## Description

To have a full description and demo of what the code does, please refer to the [self-contained web page](./web/index.html) within this repo.

## Important note

The program uses the (slightly modified) base Phong shaders and the <i>teapot1</i> object from the original 
[lab capsule](https://github.com/tiperiu/COMP371_all/tree/313f6fc0d026d7274f2f98a053728dadad7c42bf/Lab_capsules/capsule3) when first booting up, 
which are located inside the <i>assets</i> folder.
Moreover, all the shaders implemented in this project have been implemented inside the same folder.
This means this folder is critical to the program's operation and <b><u>SHOULD NOT</u></b> be moved or deleted.