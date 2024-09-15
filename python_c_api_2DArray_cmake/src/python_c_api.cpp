// Based on a heavily modified example of pure embedding on official python wiki:
// https://docs.python.org/3.10/extending/embedding.html
// Spaghetti mostly pure c code, but should work

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <vector>
#include <random>

// One Big Stupid Function to handle conversion
int call_python_function(const char *module_name, const char *function_name, const std::vector<std::vector<int>> &input, std::vector<std::vector<int>> &output)
{
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    int i;

    // Import Python Module
    pName = PyUnicode_DecodeFSDefault(module_name);
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    // Error Checking
    if (pModule == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", module_name);
        return 1;
    }
    
    // Get requested Function
    pFunc = PyObject_GetAttrString(pModule, function_name);
    if (pFunc && PyCallable_Check(pFunc))
    {   
        // ################## Possibly add more functions here ##################// 

        // Convert the C++ 2D vector to a Python list of lists
        PyObject *pOuterList = PyList_New(input.size());
        for (size_t i = 0; i < input.size(); ++i)
        {
            PyObject *pInnerList = PyList_New(input[i].size());
            for (size_t j = 0; j < input[i].size(); ++j)
            {
                PyObject *pFloat = PyLong_FromLong(input[i][j]);
                PyList_SetItem(pInnerList, j, pFloat);
            }
            PyList_SetItem(pOuterList, i, pInnerList); 
        }

        // Create a tuple to hold the arguments for the Python function
        pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs, 0, pOuterList); 

        // ### Finally Call the Python function with the 2D array as an argument
        pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);

        if (pValue != nullptr)
        {
            // Parse the returned list and some basic error checking
            if (PyList_Check(pValue))
            {
                Py_ssize_t result_rows = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < result_rows; ++i)
                {
                    PyObject *pInnerList = PyList_GetItem(pValue, i);
                    if (PyList_Check(pInnerList))
                    {
                        Py_ssize_t result_cols = PyList_Size(pInnerList);
                        std::vector<int> row;
                        for (Py_ssize_t j = 0; j < result_cols; ++j)
                        {
                            PyObject *pItem = PyList_GetItem(pInnerList, j);
                            int val = PyLong_AsLong(pItem);
                            row.push_back(val);
                        }
                        output.push_back(row);
                    }
                    else
                    {
                        fprintf(stderr, "Inner item is not a list\n");
                        Py_DECREF(pValue);
                        return 1;
                    }
                }
            }
            else
            {
                fprintf(stderr, "Return value is not a list\n");
                Py_DECREF(pValue);
                return 1;
            }
            Py_DECREF(pValue);
        }
        else
        {
            PyErr_Print();
            Py_DECREF(pValue);
            fprintf(stderr, "Call failed\n");
            return 1;
        }
    }
    else
    {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function \"%s\"\n", function_name);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    return 0;

}


// Example Usage
int main(int argc, char *argv[])
{
    int m = 2;
    int n = 500;

    // RNG Copy Pasta from ChatGPT cause I'm lazy 
    std::vector<std::vector<int>> input(m, std::vector<int>(n));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            input[i][j] = dis(gen);
        }
    }

    const char module_name[] = "module";
    const char function_name[] = "sort_2d_array";

    std::vector<std::vector<int>> output;

    // Start Python Intepreter. !This wil not close automatically
    // Cleanup needed with Py_FinalizeEx
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");

    // Call the python function
    int val = call_python_function(module_name, function_name, input, output);
    if (val != 0) return val;

    // Print the result
    for (size_t i = 0; i < output.size(); ++i)
    {
        for (size_t j = 0; j < output[i].size(); ++j)
        {
            printf("Result[%zu][%zu] = %d\n", i, j, output[i][j] * 2);
        }
    }

    if (Py_FinalizeEx() < 0) return 120;

    return 0;
}