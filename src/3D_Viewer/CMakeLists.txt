cmake_minimum_required(VERSION 3.5)

project(3D_Viewer VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

#add_subdirectory(QtGifImage)
set(PROJECT_SOURCES
        back/3d_viewer.h
        back/affine.c
        back/file_parser.c
        front/ViewerWindow/mainwindow.cpp
        front/ViewerWindow/mainwindow.h
        front/ViewerWindow/mainwindow.ui
        front/ViewerWindow/styleWindow.cpp
        front/ViewerWindow/transformationWindow.cpp
        front/ViewerWindow/settings.cpp
        front/OpenGL/glwidget.h
        front/OpenGL/glwidget.cpp
        front/OpenGL/style.cpp
        front/OpenGL/transform.cpp
        main.cpp
        QtGifImage/qgifimage.cpp
        QtGifImage/qgifimage.h
        QtGifImage/qgifimage_p.h
        QtGifImage/qgifglobal.h
        QtGifImage/giflib/dgif_lib.c
        QtGifImage/giflib/egif_lib.c
        QtGifImage/giflib/gifalloc.c
        QtGifImage/giflib/gif_err.c
        QtGifImage/giflib/gif_font.c
        QtGifImage/giflib/gif_hash.c
        QtGifImage/giflib/gif_hash.h
        QtGifImage/giflib/gif_lib.h
        QtGifImage/giflib/gif_lib_private.h
        QtGifImage/giflib/quantize.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3D_Viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3D_Viewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3D_Viewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3D_Viewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)

set_target_properties(3D_Viewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3D_Viewer)
endif()
