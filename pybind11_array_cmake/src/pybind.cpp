#include <pybind11/pybind11.h>
#include <pybind11/embed.h> // For embedding Python interpreter
#include <pybind11/stl.h>   // For converting STL containers (e.g., vectors)

#include <random> 
#include <iostream>
namespace py = pybind11;

// n random integer matrix 
std::vector<int> create_random_vector(int n, int min_val, int max_val) {
    std::vector<int> matrix(n);
    // RNG Copy Pasta from ChatGPT cause I'm lazy 
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(min_val, max_val);
    for (int j = 0; j < n; ++j) {
        matrix[j] = dis(gen);
    }
    return matrix;
}

int main() {
    // Start Python interpreter, from wiki no need to manually terminate, will stop once out of scope 
    py::scoped_interpreter python; 

    // Define the dimensions of the array and the range for random integers
    int n = 30; // Array length
    int min_val = 0;  // Minimum random integer
    int max_val = 100;  // Maximum random integer

    // Create a random n lenghed vector in C++
    std::vector<int> cpp_vector = create_random_vector(n, min_val, max_val);

    // Print randomly generated vector
    std::cout << "Randomly generated 2D integer vector (C++):" << std::endl;
    for (int j = 0; j < n; j++) {
         std::cout << cpp_vector[j] << " ";
    }
    std::cout << std::endl;

    // Load Python module and function
    py::module python_module = py::module::import("module");  
    py::object python_function = python_module.attr("sort_array"); 

    // Call Python function
    auto result = python_function(cpp_vector).cast<std::vector<int>>();

    // Output the result from Python
    std::cout << "Result from Python:" << std::endl;
    for (int j = 0; j < n; j++) {
         std::cout << result[j] << " ";
    }
    std::cout << std::endl;

    return 0;
}