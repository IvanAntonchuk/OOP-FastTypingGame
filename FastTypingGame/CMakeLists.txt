cmake_minimum_required(VERSION 3.19)
project(FastTypingGame LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(FastTypingGame
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    gameengine.h gameengine.cpp

    modewindow.h modewindow.cpp modewindow.ui
    gamewindow.h gamewindow.cpp gamewindow.ui
)

target_link_libraries(FastTypingGame
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(FastTypingGame PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS FastTypingGame
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET FastTypingGame
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
