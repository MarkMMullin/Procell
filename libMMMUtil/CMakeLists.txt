cmake_minimum_required(VERSION 3.5.2)
project(MMMUtil)
#Version Information

set(MMMUTIL_VERSION_MAJOR
        "2"  CACHE
        STRING "Major Library Build Version." FORCE)
set(MMMUTIL_VERSION_MINOR
        "1"  CACHE
        STRING "Minor Library Build Version." FORCE)
set(MMMUTIL_VERSION_PATCH
        "1"  CACHE
        STRING "Patch Library Build Version." FORCE)

add_definitions(-DMAJORVER=${MMMUTIL_VERSION_MAJOR} -DMINORVER=${MMMUTIL_VERSION_MINOR} -DPATCHVER=${MMMUTIL_VERSION_PATCH})
include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

#Generate the static library from the sources
add_library(MMMUtil STATIC ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
# install(TARGETS testStudent DESTINATION /usr/lib)
