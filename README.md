# OpencvApp

OpenCV images processing test app.

This is not a useful tool, this is only test.

### Available commands 

load (ld)  <name> <filename> - Load image file <filename> to the slot <name>

store (s)  <name> <filename> - Save image from the slot <name> to the file <filename>

blur <from_name> <to_name> <size> - Blur image from the slot <from_name> with bluring size <size> and place it to the slot <to_name>

resize <from_name> <to_name> <new_width> <new_height> - Resize image from the slot <from_name> to <new_width> <new_height> size and place it to the slot <to_name>

exit, quit, q - exit

help, h - this text


### Requirements

OpenCV version 451, OPENCV_DIR environment variable should be set.
Cmake 3.0 or newer
Microsoft Visual Studio 2019

### Compiling

In Windows just run build.cmd from the command line.
Linux build is not tested, try to run build.sh



