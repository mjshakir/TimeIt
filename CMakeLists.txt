cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
#------------------------------------------------------------------------------------------
# Determine if TimeIt is built as a standalone project or included by other projects
set(TIMEIT_STANDALONE_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(TIMEIT_STANDALONE_PROJECT ON)
endif()
#------------------------------------------------------------------------------------------
# Get the parent directory name and use it as the project name
get_filename_component(PARENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PARENT_DIR_NAME ${PARENT_DIR_NAME})
project(${PARENT_DIR_NAME} VERSION 1.0 DESCRIPTION "A timing function library" LANGUAGES CXX)
#------------------------------------------------------------------------------------------
# Set the C++ standard, require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#------------------------------------------------------------------------------------------
# Option to always produce ANSI-colored output (GNU/Clang only)
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." OFF)
MESSAGE(STATUS "FORCE_COLORED_OUTPUT: " ${FORCE_COLORED_OUTPUT})
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()
#------------------------------------------------------------------------------------------
# Library target
add_library(${PROJECT_NAME} ${LIB_TYPE} 
    src/TimeIt.cpp
    src/TimeFunction.cpp
    )
#------------------------------------------------------------------------------------------
# Compiler flags for optimization
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    add_compile_options(/W4)  # Equivalent to -Wall in GCC/Clang
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    add_compile_options(-Wall -Wextra -Wpedantic -pedantic-errors -Werror=format-security -fasynchronous-unwind-tables)
endif()
#------------------------------------------------------------------------------------------
# Option for building shared/static library, default to static
option(BUILD_TIMING_SHARED_LIBS "Build using shared libraries" ON)
if(BUILD_TIMING_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()
#------------------------------------------------------------------------------------------
# Include directories
include_directories(include)
#------------------------------------------------------------------------------------------
# Check if this is a top-level project or included by other projects
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(TIMING_CODE_TOP_LEVEL TRUE)
else()
    set(TIMING_CODE_TOP_LEVEL FALSE)
endif()
#------------------------------------------------------------------------------------------
# Specify the output directories for standalone project
if(TIMEIT_STANDALONE_PROJECT)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()
#------------------------------------------------------------------------------------------
# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
#------------------------------------------------------------------------------------------
# Installation and export setup
if(TIMEIT_STANDALONE_PROJECT)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )

    # Exporting and versioning
    install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE TimeIt::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
endif()
#------------------------------------------------------------------------------------------
# Alias for TimeIt library
add_library(TimeIt::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
#------------------------------------------------------------------------------------------
# Set TIMEIT_LIBRARIES variable
if(TIMEIT_STANDALONE_PROJECT)
    set(TIMEIT_LIBRARIES TimeIt::${PROJECT_NAME})
else()
    set(TIMEIT_LIBRARIES TimeIt::${PROJECT_NAME} PARENT_SCOPE)
endif()
#------------------------------------------------------------------------------------------
# For building examples and tests only if this is a standalone project
if(TIMEIT_STANDALONE_PROJECT)
    add_subdirectory(example)
    enable_testing()
    add_subdirectory(test)
endif()
#------------------------------------------------------------------------------------------