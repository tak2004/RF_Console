# Define a project if this file wasn't included.
if(NOT CMAKE_PROJECT_NAME OR "${CMAKE_PROJECT_NAME}" MATCHES "^RF_Console$")
    cmake_minimum_required(VERSION 2.8.11)
    project(RF_Console)
    # put the libraries to the dist directory
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)    
endif()

include("Integrate.cmake")
rcf_addpackage(radonframework "dev")
rcf_addpackage(rf_colorspace "dev")

rcf_generate(module RF_CONSOLE RadonFrameworkConsole "Framework")
    rcf_add_recursive("src/" "Source")
    rcf_add_recursive("include/RadonFramework/" "Includes")
    if(NOT WIN32)
        SET_SOURCE_FILES_PROPERTIES("System/IO/ConsoleWindows.cpp" PROPERTIES HEADER_FILE_ONLY ON)
    endif()
    rcf_add_public_include("${CMAKE_CURRENT_SOURCE_DIR}/include/")
    rcf_dependencies(RadonFramework RadonFrameworkColorSpace)
rcf_endgenerate()

option(RF_CONSOLE_BUILD_TEST "Enable the tests." OFF)
if(RF_CONSOLE_BUILD_TEST)
    rcf_addpackage(rf_test)
    include("tests/test.cmake")
endif()