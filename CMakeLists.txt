project(QGenderSelector)
cmake_minimum_required(VERSION 2.6.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

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

include(GenerateExportHeader)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(QGenderSelector_MOC_HDRS QGenderSelector.h)
qt4_wrap_cpp(QGenderSelector_MOC_SRCS ${QGenderSelector_MOC_HDRS})
set(QGenderSelector_SRCS QGenderSelector.cc)
set(QGenderSelector_QRC_HDRS QGenderSelector.qrc)
qt4_add_resources(QGenderSelector_QRC_SRCS ${QGenderSelector_QRC_HDRS})

add_library(QGenderSelector ${QGenderSelector_MOC_SRCS}
  ${QGenderSelector_QRC_SRCS}
  ${QGenderSelector_SRCS}
)

install(TARGETS QGenderSelector DESTINATION lib/)
install(FILES ${QGenderSelector_MOC_HDRS} DESTINATION include/)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_SHARED)
if(WIN32)
  add_definitions(-DQT_DLL)
endif(WIN32)
set(libQGenderSelectorPlugin_MOC_HDRS QGenderSelectorDesignerFactory.h)
set(libQGenderSelectorPlugin_SRCS QGenderSelectorDesignerFactory.cc)
qt4_wrap_cpp(libQGenderSelectorPlugin_MOC_SRCS ${libQGenderSelectorPlugin_MOC_HDRS})
add_library(QGenderSelectorPlugin SHARED ${QGenderSelector_MOC_SRCS} ${QGenderSelector_SRCS}
                                         ${libQGenderSelectorPlugin_MOC_SRCS} ${libQGenderSelectorPlugin_SRCS})
target_link_libraries(QGenderSelectorPlugin ${QT_LIBRARIES})
install(TARGETS QGenderSelectorPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)


add_executable(QGenderSelector-demo demo.cc)
target_link_libraries(QGenderSelector-demo QGenderSelector)
target_link_libraries(QGenderSelector-demo ${QT_LIBRARIES})
