find_package(Qt4 COMPONENTS QtGui QtCore)
if(Qt4_FOUND)
    include(${QT_USE_FILE})
    add_library(QGenderSelector4 ${LIB_TYPE} ../src/QGenderSelector.cc ../include/QGenderSelector.h ../src/QGenderSelector.qrc)
    target_link_libraries(QGenderSelector4 Qt4::QtCore Qt4::QtGui)
    if(UNIX AND QGenderSelector_BUILD_SHARED_LIBS)
        set_target_properties(QGenderSelector4 PROPERTIES SONAME "QGenderSelector4"
                                                          SOVERSION ${QGenderSelector_VERSION_MAJOR}
                                                          VERSION ${QGenderSelector_VERSION_MAJOR}.${QGenderSelector_VERSION_MINOR})
    endif(UNIX AND QGenderSelector_BUILD_SHARED_LIBS)
    generate_export_header(QGenderSelector4 BASE_NAME QGenderSelector
                                            EXPORT_MACRO_NAME QGenderSelector_EXPORT
                                            EXPORT_FILE_NAME QGenderSelector4_Export.h
                                            STATIC_DEFINE QGenderSelector_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QGenderSelector4_Export.h DESTINATION include)
    install(TARGETS QGenderSelector4 ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    if(QGenderSelector_WITH_EXAMPLE)
        add_executable(QGenderSelector4-test ../src/demo.cc)
        target_link_libraries(QGenderSelector4-test QGenderSelector4)
        install(TARGETS QGenderSelector4-test RUNTIME DESTINATION bin)
    endif(QGenderSelector_WITH_EXAMPLE)

    if(QGenderSelector_WITH_DESIGNER_PLUGIN)
        add_definitions(-DQT_SHARED -DQT_PLUGIN)
        if(WIN32)
            add_definitions(-DQT_DLL)
        endif(WIN32)
        add_library(QGenderSelector4Plugin SHARED ../src/QGenderSelectorDesignerFactory.cc ../include/QGenderSelectorDesignerFactory.h)
        target_link_libraries(QGenderSelector4Plugin QGenderSelector4)
        install(TARGETS QGenderSelector4Plugin ARCHIVE DESTINATION lib/qt4/plugins/designer LIBRARY DESTINATION lib/qt4/plugins/designer RUNTIME DESTINATION lib/qt4/plugins/designer)
    endif(QGenderSelector_WITH_DESIGNER_PLUGIN)
endif(Qt4_FOUND)
