# tera-ranger-one-lib
A C++ library for reading the Tera Ranger One sensor over a USB connection.

Sensor is available from http://www.teraranger.com/

There are 2 files for test: 

- tera_ranger_one_continuous.cpp - for continuous data read,
and
- tera_ranger_one_on_request.cpp - for reading data on request - this is useful if you want to create a LIDAR and you read data only after a motor step has been performed.

# Usage

For use please create a console project and add all files from src and 1 file from tests. Don't forget to set the include path to the include folder of this project.

This sensor is used in Jenny 5 robot. See more details here: http://www.jenny5.org

Please send questions, comments etc. to mihai.oltean@gmail.com
