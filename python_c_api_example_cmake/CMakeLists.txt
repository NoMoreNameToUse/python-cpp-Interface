# This is created with help of https://cmake.org/cmake/help/latest/guide/tutorial/, 
# Stackoverflow and some ChatGPT Copy Pasta. Should work on windows and Ubuntu but no guarantee

cmake_minimum_required(VERSION 3.12)
project(PythonAPIExample VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Python interpreter
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Add the executable
add_executable(python_c_api_example src/main.cpp)

# Include directories for Python and pybind11
target_include_directories(python_c_api_example PRIVATE ${Python3_INCLUDE_DIRS})

# Link Python library and pybind11
target_link_libraries(python_c_api_example PRIVATE ${Python3_LIBRARIES})

# Platform-specific settings
if(UNIX AND NOT APPLE)
    # On Linux (Ubuntu)
    message(STATUS "Configuring for Linux platform (Ubuntu)")
    find_library(PYTHON_LIB NAMES python3.10 python3.12 python3)
    if(NOT PYTHON_LIB)
        message(FATAL_ERROR "Python library not found!")
    endif()
    target_link_libraries(python_c_api_example PRIVATE ${PYTHON_LIB})
    target_link_libraries(python_c_api_example PRIVATE pthread dl util)
endif()

# Copy Python module to output dir after build
add_custom_command(
    TARGET python_c_api_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/src/module.py
        $<TARGET_FILE_DIR:python_c_api_example>
)

# Ensure the executable knows where the module.py is located (Not sure why but do not hurt)
set_target_properties(python_c_api_example PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:python_c_api_example>"
)
