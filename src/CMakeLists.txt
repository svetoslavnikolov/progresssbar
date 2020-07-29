cmake_minimum_required(VERSION 3.15)


include(GenerateExportHeader)  # Multi-platform support for DLL Export

# -----------------------------------------------------------------------------
#   progressbar library
# -----------------------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(QTW_VER_MAJOR 1)
set(QTW_VER_MINOR 0)
set(QTW_VER_PATCH 0)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#find_package(Qt5 COMPONENTS Gui Core Widgets REQUIRED)

set(QTDIR E:/Lib/Qt/Qt5.13.0/5.13.0/msvc2017_64)
set(QTDIR_LIB ${QTDIR}/lib)
set(QTDIR_DLL ${QTDIR}/bin)
set(QTDIR_INCLUDE ${QTDIR}/include)

set(QTDLLs Qt5Core.dll Qt5Gui.dll Qt5Widgets.dll
           Qt5Cored.dll Qt5Guid.dll Qt5Widgetsd.dll)

find_package(Qt5Core PATHS ${QTDIR})
find_package(Qt5Gui PATHS ${QTDIR})
find_package(Qt5Widgets PATHS ${QTDIR})


set(CMAKE_CXX_STANDARD 17)        # Use standard lib c++17

project(progressbar
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

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${QTDIR_INCLUDE})

add_library(progressbar SHARED
    version.h
    progressbar.h
    progressbarwidget.h
    progressbarwidget.cpp
    progressbar_mgr.h
    progressbar_mgr.cpp
    progressbar_dllmain.cpp
    ${RC_FILES}
    )

foreach(DLL IN LISTS QTDLLs)
    add_custom_command(TARGET progressbar
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QTDIR_DLL}/${DLL} $<TARGET_FILE_DIR:progressbar>
        )
endforeach()    

target_link_directories(progressbar PUBLIC ${QTDIR}/lib)
target_link_libraries(progressbar Qt5Core Qt5Gui Qt5Widgets)

generate_export_header(progressbar)
install(TARGETS progressbar DESTINATION .)


# -----------------------------------------------------------------------------
#   test progress bar
# -----------------------------------------------------------------------------

add_executable(progressbar_demo
    progressbar_demo.cpp
    )

target_link_libraries(progressbar_demo progressbar)
