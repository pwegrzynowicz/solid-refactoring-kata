cmake_minimum_required(VERSION 3.10)
project(ocp)

set(CMAKE_CXX_STANDARD 14)

add_executable(ocp main.cpp)

add_executable(ocp_refactor_map_1 command_map_1/main.cpp command_map_1/command.h command_map_1/parser.h)

add_executable(ocp_refactor_chain_1 command_chain_1/main.cpp command_chain_1/command.h command_chain_1/parser.h)

add_executable(ocp_refactor_chain_2 command_chain_2/main.cpp command_chain_2/command.h command_chain_2/parser.h)