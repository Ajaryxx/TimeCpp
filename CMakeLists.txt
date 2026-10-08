cmake_minimum_required(VERSION 3.31.6)

#define project
project(TimeCpp
VERSION 1.0.0
LANGUAGES CXX)

#define options
option(BUILD_SHARED "Build the library as a shared libray" ON)
option(BUILD_STATIC "Build the library as a statuc libray" OFF)

option(BUILD_TEST "Build tests" ON)

if(BUILD_SHARED AND BUILD_STATIC)
	message(FATAL_ERROR "You can't have BUILD_SHARED and BUILD_STATIC enabled together!")
endif()

#define the library with static or shared
if(BUILD_SHARED)
    add_library(TimeCpp SHARED "dummy.cpp")
    message(STATUS "Build Library: Shared")
elseif(BUILD_STATIC)
    add_library(TimeCpp STATIC "dummy.cpp")
     message(STATUS "Build Library: Static")
else()
    message(FATAL_ERROR "Please enable static OR dynamic")
endif()

#export library
include(GNUInstallDirs)
target_include_directories(TimeCpp PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

install(TARGETS TimeCpp
	EXPORT TimeCppTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}

	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT TimeCppTargets
FILE TimeCppTargets.cmake
NAMESPACE TimeCpp::
DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TimeCpp)

#create library config
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TimeCppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/TimeCppConfig.cmake
    INSTALL_DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/TimeCpp
)
#define verision
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/TimeCppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
#install library
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/TimeCppConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/TimeCppConfigVersion.cmake

    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/TimeCpp
)

install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
   
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)


add_subdirectory(src)
if(BUILD_TEST)
add_subdirectory(test)
endif()