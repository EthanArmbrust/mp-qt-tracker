cmake_minimum_required(VERSION 3.5)

project(mp-qt-tracker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES mp-qt-tracker_en_US.ts)

if(WIN32)
    set(PLATFORM_CODE  WIN32 DolphinProcess/Windows/WindowsDolphinProcess.cpp)
else()
    set(PLATFORM_CODE  DolphinProcess/Linux/LinuxDolphinProcess.cpp)
endif()

if(ANDROID)
  add_library(mp-qt-tracker SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
  )
else()
  add_executable(mp-qt-tracker
    ${PLATFORM_CODE}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Resources.qrc
    primehook.cpp
    Common/MemoryCommon.cpp
    MemoryWatch/MemWatchEntry.cpp
    DolphinProcess/DolphinAccessor.cpp
    ${TS_FILES}
  )
endif()

target_link_libraries(mp-qt-tracker PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
