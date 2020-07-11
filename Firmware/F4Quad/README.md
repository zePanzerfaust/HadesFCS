# Toolchains
## Command line
Possible call to cmake could look like this
```
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_TOOLCHAIN_FILE:FILEPATH=/home/<user>/HadesFCS/ARMGCCToolchain.cmake -DCROSS_COMPILER_TOOLCHAIN_DIR:STRING=/opt/local/bin -H/home/<user>/HadesFCS -B/home/<user>/HadesFCS/build/Debug -G "Unix Makefiles"
```
## Visual Studio Code
Configuration examples can be found in `Samples/Configuration/vscode`.
### Required/recommended plugins
[C/C++ - Microsoft](https://github.com/Microsoft/vscode-cpptools)  
[CMake Tools - Microsoft](https://github.com/microsoft/vscode-cmake-tools)  
[Cortex-Debug](https://github.com/Marus/cortex-debug.git)

# Debugging
## Debug probe
### Segger J-Link
Segger J-Link EDU is the low-cost variant and can be used for non-commercial purposes.

The `Cortex-Debug` plugin can be configured to use Segger hardware. A sample configuration can be found in `Samples/Configuration/vscode/launch.json`