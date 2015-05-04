project(QGenderSelector)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#
# Enable C++11 for GCC builds
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" GCC_stdcxx11)
    check_cxx_compiler_flag("-std=c++0x" GCC_stdcxx0x)

    if(GCC_stdcxx11)
        # Compiler supports -std=c++11
        message(STATUS "Using -std=c++11 to enable C++11 in GCC")
        add_definitions(-std=c++11)
    elseif(GCC_stdcxx0x)
        # Compiler doesn't support -std=c++11 but -std=c++0x
        message(STATUS "Using -std=c++0x to enable C++11 in GCC")
        add_definitions(-std=c++0x)
    else()
        # Neither -std=c++11 nor -std=c++0x are supported
        message(WARNING "Failed to determine C++11 flag for GCC :-(")
    endif()
endif(CMAKE_COMPILER_IS_GNUCXX)
include(CheckCXX11Features)

option(QGenderSelector_BUILD_AS_SUBMODULE "Build QGenderSelector as git submodule?" OFF)
option(QGenderSelector_BUILD_SHARED_LIBS "Build QGenderSelector as shared library?" ON)
option(QGenderSelector_WITH_DESIGNER_PLUGIN "Build plugin to use QGenderSelector with Qt Designer?" ON)
option(QGenderSelector_WITH_EXAMPLE "Build small example program for QGenderSelector?" ON)
option(QGenderSelector_ENABLE_QT4 "Build QGenderSelector for Qt4?" ON)
option(QGenderSelector_ENABLE_QT5 "Build QGenderSelector for Qt5?" ON)

set(QGenderSelector_VERSION_MAJOR 1)
set(QGenderSelector_VERSION_MINOR 1)
set(QGenderSelector_VERSION_PATCH 0)

if(NOT QGenderSelector_BUILD_AS_SUBMODULE)
    set(CPACK_PACKAGE_VERSION_MAJOR ${QGenderSelector_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${QGenderSelector_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${QGenderSelector_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION "Qt gender selection widget")
    set(CPACK_PACKAGE_VENDOR "#das-system Networks")
    if(WIN32)
        set(CPACK_GENERATOR "ZIP")
    endif(WIN32)
    include(CPack)
endif(NOT QGenderSelector_BUILD_AS_SUBMODULE)

if(QGenderSelector_BUILD_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else(QGenderSelector_BUILD_SHARED_LIBS)
    set(LIB_TYPE STATIC)
endif(QGenderSelector_BUILD_SHARED_LIBS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include(GenerateExportHeader)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


if(NOT QGenderSelector_ENABLE_QT4 AND NOT QGenderSelector_ENABLE_QT5)
    message(ERROR "You need to enable at least one of Qt4/5!")
endif(NOT QGenderSelector_ENABLE_QT4 AND NOT QGenderSelector_ENABLE_QT5)

if(QGenderSelector_ENABLE_QT4)
    add_subdirectory(QGenderSelector4)
endif(QGenderSelector_ENABLE_QT4)
if(QGenderSelector_ENABLE_QT5)
    add_subdirectory(QGenderSelector5)
endif(QGenderSelector_ENABLE_QT5)

