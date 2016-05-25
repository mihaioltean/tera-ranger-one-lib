# Tera Ranger One Library

A C++ asynchronous, cross-platform library for reading the Tera Ranger One sensor over a USB connection.


## About
Sensor is available from http://www.teraranger.com/

There are 2 files for test: 

- tera_ranger_one_continuous.cpp - for continuous data read,
and
- tera_ranger_one_on_request.cpp - for reading data on request - this is useful if you want to create a LIDAR and you read data only after a motor step has been performed.

## Usage

Create a C++ console project and add all files from src and 1 file from tests. Don't forget to set the include path to the include folder of this project.

This sensor is used by Jenny 5 robot. See more details here: http://www.jenny5.org

Currently has been tested for Windows only.

## Contact

Please send questions, comments etc. to mihai.oltean@gmail.com

## Screenshot

![tera ranger one usage screenshot](https://cloud.githubusercontent.com/assets/3392157/15533594/fc089dd6-226d-11e6-846c-3b0f44dd2f89.png)