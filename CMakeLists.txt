# Copyright © 2023 SberDevices LLC. All rights reserved.
#
# Confidential and Proprietary.
# Unauthorized copying of this file, via any medium is strictly prohibited.

cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project)

include_directories(./)

set(SOURCES
	condition_parser.cpp
	condition_parser_test.cpp
	database.cpp
	date.cpp
	main.cpp
	node.cpp
	token.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# install(TARGETS ${PROJECT_NAME} DESTINATION bin)

