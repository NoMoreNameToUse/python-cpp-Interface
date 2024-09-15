# This is created with help of https://cmake.org/cmake/help/latest/guide/tutorial/, 
# Stackoverflow and some ChatGPT Copy Pasta. Should work on windows and Ubuntu but no guarantee
# This is created with help of https://cmake.org/cmake/help/latest/guide/tutorial/, 
# Stackoverflow and some ChatGPT Copy Pasta. Should work on windows and Ubuntu but no guarantee

cmake_minimum_required(VERSION 3.12)
project(PybindAdvancedArray VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Python interpreter and development files
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Query Python to get the path to pybind11's CMake files
execute_process(
    COMMAND ${Python3_EXECUTABLE} -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
find_package(pybind11 REQUIRED)

# Add the Python extension module (shared library)
add_library(cpp_code MODULE src/cpp_code.cpp)

# Include directories for Python and pybind11
target_include_directories(cpp_code PRIVATE ${Python3_INCLUDE_DIRS} ${pybind11_INCLUDE_DIRS})

# Link the Python library and pybind11
target_link_libraries(cpp_code PRIVATE ${Python3_LIBRARIES} pybind11::module)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set_target_properties(cpp_code PROPERTIES
        SUFFIX ".pyd"  # Windows Python extension uses .pyd suffix
        PREFIX ""  # No "lib" prefix on Windows
    )

    # Ensure the Pythonpath is set correctly for debugging
    set_target_properties(cpp_code PROPERTIES
        VS_DEBUGGER_ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:cpp_code>"
    )
    
elseif(UNIX AND NOT APPLE)
    # Linux-specific settings
    message(STATUS "Configuring for Linux platform (Ubuntu)")
    
    # Set the suffix to .so for Linux and remove the "lib" prefix
    set_target_properties(cpp_code PROPERTIES
        SUFFIX ".so"  # Linux Python extension uses .so suffix
        PREFIX ""  # Remove the "lib" prefix on Linux
    )

    # On Linux, additional libraries such as pthread, dl, and util might be needed
    find_library(PYTHON_LIB NAMES python3.10 python3.12 python3)
    if(NOT PYTHON_LIB)
        message(FATAL_ERROR "Python library not found!")
    endif()
    target_link_libraries(cpp_code PRIVATE ${PYTHON_LIB} pthread dl util)
endif()

# Ensure the main Python file is copied to the correct output directory
add_custom_command(
    TARGET cpp_code POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/src/main.py
        $<TARGET_FILE_DIR:cpp_code>
)
