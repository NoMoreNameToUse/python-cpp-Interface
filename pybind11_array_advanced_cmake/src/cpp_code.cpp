#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
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

// Function to accept an array from Python and print it
void output_final_array(const std::vector<int>& array) {
    std::cout << "Final array: ";
    for (int num : array) {
        std::cout << num * 2 << " ";
    }
    std::cout << std::endl;
}

// Binding code, so easy when you do not need to handle conversion yourself
PYBIND11_MODULE(cpp_code, m) {
    m.def("create_random_vector", &create_random_vector, "Generate a random array of length n");
    m.def("output_final_array", &output_final_array, "Output the final array");
}