cmake_minimum_required(VERSION 3.5)

project(DP_Pairwise_Alignment LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        dp_visualiser.cpp
        dp_visualiser.h
        dp_visualiser.ui
        dp_table.cpp
        dp_table.h
        controller.cpp
        controller.h
        dp_view.cpp
        dp_view.h
        alignmentmodel.cpp
        alignmentmodel.h
        alignment.cpp
        alignment.h
        scoringfunction.cpp
        scoringfunction.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DP_Pairwise_Alignment
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(DP_Pairwise_Alignment SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(DP_Pairwise_Alignment
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DP_Pairwise_Alignment PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
