project(QGenderSelector)
cmake_minimum_required(VERSION 2.6.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_DESCRIPTION "Qt gender selection widget")
set(CPACK_PACKAGE_VENDOR "#das-system Networks")
include(CPack)

include(CheckCXX11Features)
foreach(flag ${CXX11_FEATURE_LIST})
  add_definitions(-D${flag})
endforeach()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++0x")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS)

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
endif(MSVC)

option(BUILD_STATIC_LIBRARIES "Build as static library instead of shared library/DLL" OFF)

include(GenerateExportHeader)
add_compiler_export_flags(QGenderSelector_EXPORT_FLAGS)
message(STATUS "Export-specific compiler flags: ${QGenderSelector_EXPORT_FLAGS}")

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
if(BUILD_STATIC_LIBRARIES)
  # Build static library
  add_library(QGenderSelector STATIC ${QGenderSelector_MOC_SRCS}
    ${QGenderSelector_QRC_SRCS}
    ${QGenderSelector_SRCS})
else(BUILD_STATIC_LIBRARIES)
  # Build shared library/DLL
  add_library(QGenderSelector SHARED ${QGenderSelector_MOC_SRCS}
    ${QGenderSelector_QRC_SRCS}
    ${QGenderSelector_SRCS})
  set_target_properties(QGenderSelector PROPERTIES
    SONAME QGenderSelector
    SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})
endif(BUILD_STATIC_LIBRARIES)

# Auto-generate export header for DLLs
generate_export_header(QGenderSelector
  BASE_NAME QGenderSelector
  EXPORT_MACRO_NAME QGenderSelector_EXPORT
  EXPORT_FILE_NAME QGenderSelector_export.h)

# Install rules for all of the above
install(TARGETS QGenderSelector DESTINATION lib/)
install(FILES ${QGenderSelector_MOC_HDRS} DESTINATION include/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QGenderSelector_export.h DESTINATION include/)


#
# Qt designer plugin
option(QGENDERSELECTOR_WITH_DESIGNER_PLUGIN "Build Plugin for Qt Designer" ON)
if(QGENDERSELECTOR_WITH_DESIGNER_PLUGIN)
  add_definitions(${QT_DEFINITIONS})
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
  if(WIN32)
    add_definitions(-DQT_DLL)
  endif(WIN32)
  set(libQGenderSelectorPlugin_MOC_HDRS QGenderSelectorDesignerFactory.h)
  set(libQGenderSelectorPlugin_SRCS QGenderSelectorDesignerFactory.cc)
  qt4_wrap_cpp(libQGenderSelectorPlugin_MOC_SRCS ${libQGenderSelectorPlugin_MOC_HDRS})
  add_library(QGenderSelectorPlugin SHARED ${QGenderSelector_MOC_SRCS}
    ${QGenderSelector_SRCS} ${QGenderSelector_QRC_SRCS}
    ${libQGenderSelectorPlugin_MOC_SRCS} ${libQGenderSelectorPlugin_SRCS})
  target_link_libraries(QGenderSelectorPlugin ${QT_LIBRARIES})
  install(TARGETS QGenderSelectorPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)
endif(QGENDERSELECTOR_WITH_DESIGNER_PLUGIN)


#
# Simple demo executable
add_executable(QGenderSelector-demo demo.cc)
target_link_libraries(QGenderSelector-demo QGenderSelector)
target_link_libraries(QGenderSelector-demo ${QT_LIBRARIES})
