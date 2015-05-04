project(QGenderSelector)
cmake_minimum_required(VERSION 2.6.6)
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
option(QGenderSelector_INSTALL_DESIGNER_PLUGIN "Install Qt Designer plugin to Qt plugin directory?" OFF)
option(QGenderSelector_WITH_EXAMPLE "Build small example program for QGenderSelector?" ON)

if(NOT QGenderSelector_BUILD_AS_SUBMODULE)
    set(CPACK_PACKAGE_VERSION_MAJOR 1)
    set(CPACK_PACKAGE_VERSION_MINOR 0)
    set(CPACK_PACKAGE_VERSION_PATCH 1)
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

include(GenerateExportHeader)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


#
# Library for QGenderSelector
set(QGenderSelector_MOC_HDRS QGenderSelector.h)
qt4_wrap_cpp(QGenderSelector_MOC_SRCS ${QGenderSelector_MOC_HDRS})
set(QGenderSelector_SRCS QGenderSelector.cc)
set(QGenderSelector_QRC_HDRS QGenderSelector.qrc)
qt4_add_resources(QGenderSelector_QRC_SRCS ${QGenderSelector_QRC_HDRS})
add_library(QGenderSelector ${LIB_TYPE} ${QGenderSelector_SRCS} ${QGenderSelector_MOC_SRCS} ${QGenderSelector_QRC_SRCS})
target_link_libraries(QGenderSelector ${QT_LIBRARIES})
generate_export_header(QGenderSelector BASE_NAME QGenderSelector
                                       EXPORT_MACRO_NAME QGenderSelector_EXPORT
                                       EXPORT_FILE_NAME QGenderSelector_Export.h
                                       STATIC_DEFINE QGenderSelector_BUILT_AS_STATIC)
if(UNIX AND QGenderSelector_BUILD_SHARED_LIBS)
    set_target_properties(QGenderSelector PROPERTIES SONAME QGenderSelector SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})
endif(UNIX AND QGenderSelector_BUILD_SHARED_LIBS)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QGenderSelector_Export.h DESTINATION include)
install(TARGETS QGenderSelector DESTINATION ARCHIVE DESTINATION lib
                                            LIBRARY DESTINATION lib
                                            RUNTIME DESTINATION bin)
install(FILES ${QGenderSelector_MOC_HDRS} DESTINATION include/)


#
# Qt designer plugin
if(QGenderSelector_WITH_DESIGNER_PLUGIN)
  add_definitions(${QT_DEFINITIONS})
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
  if(WIN32)
    add_definitions(-DQT_DLL)
  endif(WIN32)
  set(libQGenderSelectorPlugin_MOC_HDRS QGenderSelectorDesignerFactory.h)
  set(libQGenderSelectorPlugin_SRCS QGenderSelectorDesignerFactory.cc)
  qt4_wrap_cpp(libQGenderSelectorPlugin_MOC_SRCS ${libQGenderSelectorPlugin_MOC_HDRS})
  add_library(QGenderSelectorPlugin SHARED ${libQGenderSelectorPlugin_MOC_SRCS} ${libQGenderSelectorPlugin_SRCS})
  target_link_libraries(QGenderSelectorPlugin QGenderSelector ${QT_LIBRARIES})
  if(QGenderSelector_INSTALL_DESIGNER_PLUGIN)
    install(TARGETS QGenderSelectorPlugin DESTINATION ${QT_DIR}/plugins)
  else(QGenderSelector_INSTALL_DESIGNER_PLUGIN)
    install(TARGETS QGenderSelectorPlugin ARCHIVE DESTINATION lib
                                          LIBRARY DESTINATION lib
                                          RUNTIME DESTINATION bin)
  endif(QGenderSelector_INSTALL_DESIGNER_PLUGIN)
endif(QGenderSelector_WITH_DESIGNER_PLUGIN)


#
# Simple demo executable
if(QGenderSelector_WITH_EXAMPLE)
    add_executable(QGenderSelector-demo demo.cc)
    target_link_libraries(QGenderSelector-demo QGenderSelector)
    target_link_libraries(QGenderSelector-demo ${QT_LIBRARIES})
endif(QGenderSelector_WITH_EXAMPLE)
