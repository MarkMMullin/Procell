#Compiler setup
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -MMD " CACHE
        STRING "Global build flags." FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3" CACHE
        STRING "Release build flags." FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g3" CACHE
        STRING "Debug build flags." FORCE)
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS} -pg" CACHE
        STRING "Profile build flags." FORCE)
get_filename_component(BUILDDIR ${CMAKE_CURRENT_BINARY_DIR} NAME_WE)

if(BUILDDIR MATCHES "Release$")
    message(STATUS, "Building RELEASE package")
    set(CMAKE_BUILD_TYPE "Release" CACHE
            STRING "Directory forced RELEASE build." FORCE)
elseif(BUILDDIR MATCHES "Debug$")
    message(STATUS, "Building DEBUG package")
    set(CMAKE_BUILD_TYPE "Debug" CACHE
            STRING "Directory forced DEBUG build." FORCE)
elseif(BUILDDIR MATCHES "Profile$")
    message(STATUS, "Building PROFILING package")
    set(CMAKE_BUILD_TYPE "Profile" CACHE
            STRING "Directory forced PROFILE build." FORCE)
elseif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "Profile")
endif()
add_definitions(-DBUILDTYPE="${CMAKE_BUILD_TYPE}")

