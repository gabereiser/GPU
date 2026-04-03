param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")]
    [string]$Configuration = "Release",

    [string]$BuildDir = "build"
)

$ErrorActionPreference = "Stop"

cmake -S . -B $BuildDir -DCMAKE_BUILD_TYPE=$Configuration
cmake --build $BuildDir --config $Configuration
