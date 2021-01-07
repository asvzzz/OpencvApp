cmake_minimum_required(VERSION 3.0)

set(APPNAME "OpencvApp")

project(${APPNAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

if (CMAKE_HOST_WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os /EHsc")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -O2 -Wno-psabi")
endif()

include_directories($ENV{OPENCV_DIR}/../../include)

add_executable(${APPNAME} OpencvApp.cpp)


if (CMAKE_HOST_WIN32)

    target_compile_definitions(${APPNAME} PUBLIC WIN32=1)
    target_compile_definitions(${APPNAME} PUBLIC _WIN32=1)
    target_compile_definitions(${APPNAME} PUBLIC WIN32_LEAN_AND_MEAN=1)
    target_compile_definitions(${APPNAME} PUBLIC _WINSOCK_DEPRECATED_NO_WARNINGS=1)
    target_compile_definitions(${APPNAME} PUBLIC _CRT_SECURE_NO_WARNINGS=1)

    if(CMAKE_BUILD_TYPE MATCHES Release)
        set (LIBOPENCVHASH "opencv_img_hash451.lib")
        set (LIBOPENCVWORLD "opencv_world451.lib")
    else()
        set (LIBOPENCVHASH "opencv_img_hash451d.lib")
        set (LIBOPENCVWORLD "opencv_world451d.lib")
    endif()

    target_link_libraries( # Specifies the target
                       ${APPNAME}
                       kernel32.lib
                       user32.lib
                       $ENV{OPENCV_DIR}/lib/${LIBOPENCVHASH}
                       $ENV{OPENCV_DIR}/lib/${LIBOPENCVWORLD}
                       )
else()

# NOT TESTED!!!

    set (LIBOPENCVHASH  "opencv_img_hash451")
    set (LIBOPENCVWORLD "opencv_world451")

    target_link_libraries( # Specifies the target
                       ${APPNAME}
		       pthread
		       dl
		       cap
                       $ENV{OPENCV_DIR}/lib/${LIBOPENCVHASH}
                       $ENV{OPENCV_DIR}/lib/${LIBOPENCVWORLD}
                       )
endif()
