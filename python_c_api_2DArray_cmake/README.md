# Prerequisits 

## Windows 
install Ninja first and add to PATH.


And then build the C code
```
cd /path/to/this/folder/

mkdir build && cd build

cmake -G Ninja ..

ninja
```

And run the program
```
./python_c_api_2DArray.exe 
```

## Ubuntu

Run the following: 
```
cd /path/to/project[...]cmake/folder/

mkdir build && cd build

pip install pybind11
```
And then build the C code
```
cmake ..

make
```

And run the program
```
./program_name
```