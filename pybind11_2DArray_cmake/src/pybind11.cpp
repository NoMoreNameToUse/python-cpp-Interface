#include <pybind11/pybind11.h>
#include <pybind11/embed.h> // For embedding Python interpreter
#include <pybind11/stl.h>   // For converting STL containers (e.g., vectors)

#include <random> 
#include <iostream>
namespace py = pybind11;

// mxn random integer matrix 
std::vector<std::vector<int>> create_random_2d_vector(int m, int n, int min_val, int max_val) {
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    // RNG Copy Pasta from ChatGPT cause I'm lazy 
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(min_val, max_val);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Example main
int main() {
    // Start Python interpreter, from wiki no need to manually terminate, will stop once out of scope 
    py::scoped_interpreter python; 

    // Define the dimensions of the 2D array and the range for random integers
    int m = 5; // rows
    int n = 10; // columns
    int min_val = 0;  // Minimum random integer
    int max_val = 100;  // Maximum random integer

    // Create a random m x n 2D vector in C++
    std::vector<std::vector<int>> cpp_2d_vector = create_random_2d_vector(m, n, min_val, max_val);

    // Print the randomly generated 2D vector
    std::cout << "Randomly generated 2D integer vector (C++):" << std::endl;
    for (const auto& row : cpp_2d_vector) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    // Load Python module and function
    py::module python_module = py::module::import("module");  
    py::object python_function = python_module.attr("sort_2d_array"); 

    // Call Python function
    auto result = python_function(cpp_2d_vector).cast<std::vector<std::vector<int>>>();

    // Output the result from Python
    std::cout << "Result from Python:" << std::endl;
    for (const auto& row : result) {
        for (const auto& element : row) {
            std::cout << element*2 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}