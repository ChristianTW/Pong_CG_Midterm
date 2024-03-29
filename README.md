# Pong Game for Computer Graphics Class 2024

A simple game for a project in the SAU Computer Graphics class in spring 2024.

Controls are W and S for the left player and Up and Down for the right.

'knux' for a thing

to build, you must change a submodule file, in the provided image.



# canis-demos


git clone --recursive https://github.com/EricWRogers/canis-demos.git
-or-
git clone --recursive git@github.com:EricWRogers/canis-demos.git


## DEPENDENCES

- LINUX

    -   CMake minimum version 3.18

    -   libgl1-mesa-dev

    -   librandr-dev

    -   libxinerama-dev

    -   libcursor-dev

    -   libxi-dev

    -   gdb

- WINDOWS

    -  CMake minimum version 3.18
    -  https://cmake.org/download/
    -  window x64 installer
    -  make sure to select add to path in the installer

    -  download vscode
    -  open the project with vscode
    -  goto the extension tab and install "c/c++ Extension Pack"

    - after this point you should get an option to scan for a compiler if it does not find one continue to the next step

    -  https://visualstudio.microsoft.com/downloads/?q=build+tools
    -  scroll down until you see "Build Tools for Visual Studio 2022" then click download
    -  on the left make sure that Desktop development with c++ is selected
    -   then on the right make sure cmake and clang are selected then install

    -  Troubleshoot for msvcp140.dll or vcruntime140.dll is missing error
    -   -   https://docs.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170
