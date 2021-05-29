# get path to script (useful for relative paths)
SCRIPT_PATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

# set current path to project folder
cd $SCRIPT_PATH/../

# default values for script options
debug=${debug:-OFF}
clean=${clean:-OFF}
help=${help:-HIDE}

# read options from command line arguments
# (format './build.sh --build_debug=on')
while [ $# -gt 0 ]; do

   if [[ $1 == *"--"* ]]; then
        param="${1/--/}"
        value=$2
        # if parameter value includes "--"
        # then value was not given for parameter
        # as the next parameter is inside value
        # so set it to empty
        if [[ $value == *"--"* ]]; then
            value=""
        fi
        declare $param="$value"
        # echo $1 $2 // Optional to see the parameter:value result
   fi

  shift
done

# check valid 'help' option
# default: off
if [[ "$help" == "" || "$help" == "SHOW" || "$help" == "Show" || "$help" == "show" ]]; then
    # show help
    echo ""
    echo "Automatically build project using CMake."
    echo "Use command line arguments to set options with the format '--[option] [value]'"
    echo "Some options can be used without specifiying a value e.g. './build.sh --debug'"
    echo "Options that can be used without a value will be marked with *."
    echo ""
    echo "Options"
    echo "  --help  *[show/hide]: Display help (Default: hide) (Empty: show)"
    echo "  --debug *[on/off]: Build project in Debug mode (Default: off) (Empty: on)"
    echo "  --clean *[on/off]: Clean project before build (Default: off) (Empty: on)"
    exit 0 # terminate after showing help
elif [[ "$help" == "HIDE" || "$help" == "Hide" || "$help" == "hide" ]]; then
    # no action required but elsif needed so as not to error help is off
    :
else
    echo "ERROR: Invalid argument for 'help'. Should be 'on'/'off' or empty e.g. '--help' to display help. Received: '$help'"
    exit 1 # terminate and indicate error
fi

# check valid 'clean' option
# default: off
if [[ "$clean" == "" || "$clean" == "ON" || "$clean" == "On" || "$clean" == "on" ]]; then
    echo "Clean before build: On"
    clean="on"
elif [[ "$clean" == "OFF" || "$clean" == "Off" || "$clean" == "off" ]]; then
    echo "Clean before build: Off"
    clean="off"
else
    echo "ERROR: Invalid argument for 'clean'. Should be 'on'/'off' or empty e.g. '--clean' to enable clean. Received: '$clean'"
    exit 1 # terminate and indicate error
fi

# define cmake build type from option (empty or on = Debug, off = Release)
# default: off
if [[ "$debug" == "" || "$debug" == "ON" || "$debug" == "On" || "$debug" == "on" ]]; then
    build_type=Debug
    echo "Build type: Debug"
elif [[ "$debug" == "OFF" || "$debug" == "Off" || "$debug" == "off" ]]; then
    build_type=Release
    echo "Build type: Release"
else
    echo "ERROR: Invalid argument for 'debug'. Should be 'on'/'off' or empty e.g. '--debug' to enable debug. Received: '$debug'"
    exit 1 # terminate and indicate error
fi

if [[ "$clean" == "on" || "$remove" == "on" ]]; then
    rm -rf build
    rm -rf install
fi

# create build & install folders
mkdir build
mkdir install

# set current directory to build folder
cd build

# configure cmake project
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=$build_type -DCMAKE_INSTALL_PREFIX="../install" ..
# build cmake project (and install)
cmake --build . --config $build_type --target install