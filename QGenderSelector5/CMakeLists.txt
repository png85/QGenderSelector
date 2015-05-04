find_package(Qt5Widgets)
if(Qt5Widgets_FOUND AND QGenderSelector_ENABLE_QT5)
    add_library(QGenderSelector5 ${LIB_TYPE} ../src/QGenderSelector.cc ../include/QGenderSelector.h ../src/QGenderSelector.qrc)
    qt5_use_modules(QGenderSelector5 Widgets)
    if(UNIX AND QGenderSelector_BUILD_SHARED_LIBS)
        set_target_properties(QGenderSelector5 PROPERTIES SONAME "QGenderSelector4"
                                                          SOVERSION ${QGenderSelector_VERSION_MAJOR}
                                                          VERSION ${QGenderSelector_VERSION_MAJOR}.${QGenderSelector_VERSION_MINOR})
    endif(UNIX AND QGenderSelector_BUILD_SHARED_LIBS)
    generate_export_header(QGenderSelector5 BASE_NAME QGenderSelector
                                            EXPORT_MACRO_NAME QGenderSelector_EXPORT
                                            EXPORT_FILE_NAME QGenderSelector5_Export.h
                                            STATIC_DEFINE QGenderSelector_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QGenderSelector5_Export.h DESTINATION include)
    install(TARGETS QGenderSelector5 ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    if(QGenderSelector_WITH_EXAMPLE)
        add_executable(QGenderSelector5-test ../src/demo.cc)
        target_link_libraries(QGenderSelector5-test QGenderSelector5)
        install(TARGETS QGenderSelector5-test RUNTIME DESTINATION bin)
    endif(QGenderSelector_WITH_EXAMPLE)

    if(QGenderSelector_WITH_DESIGNER_PLUGIN)
        add_definitions(-DQT_PLUGIN -DQT_SHARED)
        if(WIN32)
            add_definitions(-DQT_DLL)
        endif(WIN32)
        add_library(QGenderSelector5Plugin SHARED ../src/QGenderSelectorDesignerFactory.cc ../include/QGenderSelectorDesignerFactory.h)
        qt5_use_modules(QGenderSelector5Plugin Widgets)
        target_link_libraries(QGenderSelector5Plugin QGenderSelector5)
        install(TARGETS QGenderSelector5Plugin ARCHIVE DESTINATION lib/qt5/plugins/designer LIBRARY DESTINATION lib/qt5/plugins/designer RUNTIME DESTINATION lib/qt5/plugins/designer)
    endif(QGenderSelector_WITH_DESIGNER_PLUGIN)
endif(Qt5Widgets_FOUND AND QGenderSelector_ENABLE_QT5)
