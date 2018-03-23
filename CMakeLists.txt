cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Procell VERSION 2.0 LANGUAGES CXX)
include(cmake/cmake_shared.cmake)
set(CMAKE_CXX_STANDARD 11)
include(GNUInstallDirs)
add_subdirectory(libMMMUtil)
add_subdirectory(libMQTT)

