cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
#------------------------------------------------------------------------------------------
# Determine if CircularBuffer is built as a standalone project or included by other projects
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
# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#------------------------------------------------------------------------------------------
# Print out the build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
#------------------------------------------------------------------------------------------
if(MSVC)
    # MSVC specific warning flags
    add_library(common_options INTERFACE)
    target_compile_options(common_options INTERFACE /W4)  # Equivalent to -Wall in GCC/Clang
else()
    # GCC/Clang specific warning flags
    add_library(common_options INTERFACE)
    target_compile_options(common_options INTERFACE -Wall -Wextra -Wpedantic -pedantic-errors -Werror=format-security -fasynchronous-unwind-tables)
endif()
#------------------------------------------------------------------------------------------
# Set the runtime output directory only if this is a standalone project
if(TIMEIT_STANDALONE_PROJECT)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    # message(STATUS "Library output directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    # Optionally, to set these directories only for specific build configurations (Debug, Release, etc.),
    # you can use the following approach:
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
    message(STATUS "Library output directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    # Diagnostic output
    message(STATUS "ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    message(STATUS "LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    message(STATUS "RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
#------------------------------------------------------------------------------------------
# Offer switches for the type of the library and optional builds
option(BUILD_TIMEIT_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_TIMEIT_EXAMPLE "Build CircularBuffer example" ${TIMEIT_STANDALONE_PROJECT})
option(BUILD_TIMEIT_TESTS "Build CircularBuffer tests" ${TIMEIT_STANDALONE_PROJECT})
#------------------------------------------------------------------------------------------
# Force colored output
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." OFF)
if(${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options(-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-fcolor-diagnostics)
    endif()
endif()
#------------------------------------------------------------------------------------------
# Define the source and include directories
set(TIMEIT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TIMEIT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#------------------------------------------------------------------------------------------
# Define the source files
set(TIMEIT_SOURCES
    ${TIMEIT_SOURCE_DIR}/TimeIt.cpp
    ${TIMEIT_SOURCE_DIR}/TimeFunction.cpp
)
#------------------------------------------------------------------------------------------
# Define the CircularBuffer library target
#set(TIMEIT_LIBRARY_NAME "${TIMEIT_PROJECT_NAME}_lib")
# Check if the library should be built as a shared library
if(BUILD_TIMEIT_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${TIMEIT_SOURCES})
    # If needed, set properties specific to shared libraries here
else()
    add_library(${PROJECT_NAME} STATIC ${TIMEIT_SOURCES})
    # If needed, set properties specific to static libraries here
endif()
#------------------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${TIMEIT_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
#------------------------------------------------------------------------------------------
# Alias for CircularBuffer library
add_library(TimeIt::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
#------------------------------------------------------------------------------------------
# Set TIMEIT_LIBRARIES variable
if(TIMEIT_STANDALONE_PROJECT)
    set(TIMEIT_LIBRARIES TimeIt::${PROJECT_NAME})
else()
    set(TIMEIT_LIBRARIES TimeIt::${PROJECT_NAME} PARENT_SCOPE)
endif()
message(STATUS "TIMEIT_LIBRARIES: ${TIMEIT_LIBRARIES}")
#------------------------------------------------------------------------------------------
# Building examples
if(BUILD_TIMEIT_EXAMPLE)
    set(TIMEIT_EXAMPLE_NAME "${PROJECT_NAME}_example")
    add_executable(${TIMEIT_EXAMPLE_NAME} example/main.cpp)
    target_link_libraries(${TIMEIT_EXAMPLE_NAME} PRIVATE ${PROJECT_NAME})
endif()
#------------------------------------------------------------------------------------------
# Compiler-specific flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        "$<$<CONFIG:Release>:/O2>" 
        "$<$<CONFIG:Debug>:/Od>" 
        "$<$<CONFIG:Debug>:/Zi>"
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
    endif()

    set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )
else()
    # For non-MSVC compilers
    target_compile_options(${PROJECT_NAME} PRIVATE 
        "$<$<CONFIG:Release>:-O3>"
    )
    # Conditionally include AddressSanitizer flags only if standalone and in Debug mode
    if(TIMEIT_STANDALONE_PROJECT AND "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
        set(SANITIZE_FLAGS "$<$<CONFIG:Debug>:-fsanitize=address>")
        target_compile_options(${PROJECT_NAME} PRIVATE 
            "$<$<CONFIG:Debug>:-g>"
            "$<$<CONFIG:Debug>:-O0>"
            ${SANITIZE_FLAGS}
        )
        target_link_options(${PROJECT_NAME} PRIVATE ${SANITIZE_FLAGS})
    endif()
endif()
#------------------------------------------------------------------------------------------
# Enable testing and add the test directory if this is a standalone project
if(BUILD_TIMEIT_TESTS AND TIMEIT_STANDALONE_PROJECT)
    find_package(GTest QUIET)
    enable_testing()
    add_subdirectory(test)
endif()
#------------------------------------------------------------------------------------------
# Export the library targets (only if it's a standalone project)
if(TIMEIT_STANDALONE_PROJECT)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME} EXPORT CircularBufferTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY ${TIMEIT_INCLUDE_DIR}/${TIMEIT_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(EXPORT CircularBufferTargets
        FILE CircularBufferTargets.cmake
        NAMESPACE CircularBuffer::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${TIMEIT_PROJECT_NAME}
    )
endif()