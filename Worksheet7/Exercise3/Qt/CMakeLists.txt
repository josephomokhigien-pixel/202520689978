cmake_minimum_required(VERSION 3.19)
project(Worksheet7 LANGUAGES CXX)

# ---- Qt ----
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ---- VTK ----
find_package(VTK REQUIRED)

qt_add_executable(Worksheet7
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    ModelPart.cpp
    ModelPart.h
    ModelPartList.cpp
    ModelPartList.h
    Icons.qrc
    optiondialog.h
    optiondialog.cpp
    optiondialog.ui
)

# Link libraries (FIXED: target name must be Worksheet7)
target_link_libraries(Worksheet7
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        ${VTK_LIBRARIES}
)

# Copy OpenVR bindings into build dir (worksheet requirement)
add_custom_target(VRBindings)
add_custom_command(TARGET VRBindings PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy_directory ${CMAKE_SOURCE_DIR}/vrbindings ${CMAKE_BINARY_DIR}/
)
add_dependencies(Worksheet7 VRBindings)

include(GNUInstallDirs)

install(TARGETS Worksheet7
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Worksheet7
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
