$directoryPath = "build";

if (-not (Test-Path -Path $directoryPath -PathType Container)) {
    New-Item -ItemType Directory -Path $directoryPath | Out-Null
    Write-Host "Directory created: $directoryPath"
} else {
    Write-Host "Directory already exists: $directoryPath"
};

Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Debug -G Ninja -DCMAKE_CXX_FLAGS=-m64 ; Set-Location ..
# Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -DCMAKE_CXX_FLAGS=-m64; Set-Location ..
# Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" -DCMAKE_CXX_FLAGS=-m64; Set-Location ..