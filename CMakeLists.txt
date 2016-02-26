# This Source Code Form is subject to the terms of the Mozilla Public License,
# v. 2.0. If a copy of the MPL was not distributed with this file, You can
# obtain one at http://mozilla.org/MPL/2.0/.
# 
# 
# Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)
SET(CMAKE_EXPORT_COMPILE_COMMANDS 1) # For vim color_coded plugin
PROJECT(clext)

SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake")

SET(CMAKE_CXX_FLAGS "-std=c++11 -O2 -Wall -Wextra -DUNIX")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

FIND_PACKAGE(OpenCL REQUIRED)
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIRS})

ADD_LIBRARY(clext SHARED kernel.cpp initializer.cpp optimization.cpp string.cpp)
