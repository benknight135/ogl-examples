# Simple OpenGL examples
OpenGL code examples using GLFW and GLAD.

## Build
Automatic build script is provided to make it quick and easy to build. All command line scripts in this repository are 'bash' scripts to make cross-platform simple possible. To run the scripts on Windows use Git-bash. 
Run build.sh in 'scripts' folder:
```
./scripts/build.sh
```

This will build all the examples in this project to 'build' folder and install them in 'install' folder. The project is built using CMake. GLFW and GLAD are included from their Github repositories using FetchContent inside the CMake build.

Some options are available for the automatic build script. For details on these options run the build script with the '--help' argument which will display the following output:
```
Automatically build project using CMake.
Use command line arguments to set options with the format '--[option] [value]'
echo "Some options can be used without specifiying a value e.g. './build.sh --debug'
echo "Options that can be used without a value will be marked with *.

Options"
  --help  *[show/hide]: Display help (Default: hide) (Empty: show)
  --debug *[on/off]: Build project in Debug mode (Default: off) (Empty: on)
  --clean *[on/off]: Clean project before build (Default: off) (Empty: on)
```