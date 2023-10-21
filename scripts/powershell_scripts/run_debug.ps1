$targetPath = ".\source"

# Get the *.cpp file in the folder
$cppFile = Get-ChildItem -Path $targetPath -Filter "*.cpp" -File

if ($cppFile) {
    $cppFileName = $cppFile.Name  # Extract the file name
    $exeFileName = $cppFileName -replace ".cpp$", ".exe"  # Replace .cpp extension with .exe
    & ".\executables\Debug\$exeFileName"
} else {
    Write-Host "No .cpp file found in the folder."
}
