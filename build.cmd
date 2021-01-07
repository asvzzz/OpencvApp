set BUILDTYPE="Release"
REM set BUILDTYPE="Debug"
set TOOLSET=v142
set HOME=%~dp0
set HOME=%HOME:\=/%

echo "=>build"
mkdir bin
cd bin
mkdir build_windows
cd build_windows
cmake  -DCMAKE_GENERATOR_TOOLSET=%TOOLSET% -DCMAKE_BUILD_TYPE="%BUILDTYPE%" -DCMAKE_GENERATOR_PLATFORM=x64 ../../src

cmake --build . --config "%BUILDTYPE%"
echo "<=build"
cd %HOME%

:eof
