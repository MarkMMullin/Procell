cmake_minimum_required(VERSION 3.2)
project(MQTT)
#Version Information

set(MQTT_VERSION_MAJOR
        "2"  CACHE
        STRING "Major Library Build Version." FORCE)
set(MQTT_VERSION_MINOR
        "1"  CACHE
        STRING "Minor Library Build Version." FORCE)
set(MQTT_VERSION_PATCH
        "1"  CACHE
        STRING "Patch Library Build Version." FORCE)
add_definitions(-DMAJORVER=${MQTT_VERSION_MAJOR} -DMINORVER=${MQTT_VERSION_MINOR} -DPATCHVER=${MQTT_VERSION_PATCH})
include_directories(inc ../libMMMUtil/inc)

file(GLOB SOURCES "src/*.cpp")

#Generate the static library from the sources
add_library(MQTT STATIC ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
# install(TARGETS testStudent DESTINATION /usr/lib)
