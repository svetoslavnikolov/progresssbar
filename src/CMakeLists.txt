cmake_minimum_required(VERSION 3.15)



include(GenerateExportHeader)  # Multi-platform support for DLL Export


set(QTW_VER_MAJOR 1)
set(QTW_VER_MINOR 0)
set(QTW_VER_PATCH 0)


project(qt_widgets
    VERSION ${QTW_VER_MAJOR}.${QTW_VER_MINOR}.${QTW_VER_PATCH})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/version.h)

if (WIN32)
     configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
                    ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
endif(WIN32)

if(WIN32)
    set(RC_FILES ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
else()
    set(RC_FILES "")
endif(WIN32)


add_library(progressbar SHARED
    version.h
    dllmain.cpp
    ${RC_FILES}
    )

generate_export_header(progressbar)
install(TARGETS progressbar DESTINATION .)