# Prerequisits 

## Windows 
install Ninja first and add to PATH. Also install python.

If on windows, change the path to c binary accordingly in main.py

Then run the following: 
```
cd /path/to/project[...]cmake/folder/

mkdir build && cd build

pip install pybind11
```
And then build the C code
```
cmake -G Ninja ..

ninja
```

And run the program
```
python main.py
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
python3 ./main.py
```


