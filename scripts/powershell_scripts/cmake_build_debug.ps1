$directoryPath = "executables";

if (-not (Test-Path -Path $directoryPath -PathType Container)) {
    Write-Host "There is no directory: '$directoryPath' exist."
} else {
	Remove-Item .\executables -Recurse -Force
};

$targetPath = ".\source"

# Get the *.cpp file in the folder
$cppFile = Get-ChildItem -Path $targetPath -Filter "*.cpp" -File

if ($cppFile) {
    $cppFileName = $cppFile.Name  # Extract the file name
    $targetFileName = $cppFileName -replace ".cpp$", ""  # Replace .cpp extension with blank space
} else {
    Write-Host "No .cpp file found in the folder."
}

cmake --build build --config Debug --target $targetFileName -j 8 -v