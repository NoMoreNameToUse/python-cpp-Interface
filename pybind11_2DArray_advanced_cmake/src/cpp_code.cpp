#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
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

// Function to accept 2D array from Python and print it
void output_final_2d_vector(const std::vector<std::vector<int>>& matrix) {
    std::cout << "Final matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num * 2 << " ";
        }
        std::cout << std::endl;
    }
}

// Binding code, so easy when you do not need to handle conversion yourself
PYBIND11_MODULE(cpp_code, m) {
    m.def("create_random_2d_vector", &create_random_2d_vector, "Generate a random nxm matrix");
    m.def("output_final_2d_vector", &output_final_2d_vector, "Output the final matrix");
}