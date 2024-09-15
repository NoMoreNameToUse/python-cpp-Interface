# Prerequisits 

## Windows 
install Ninja first and add to PATH.

If on windows, change the path to c binary accordingly in main.py

Then run the following: 
```
cd /path/to/project[...]cmake/folder/

mkdir build && cd build

python -m venv virtenv

virtenv\Scripts\activate

pip install streamlit pybind11
```
And then build the C code
```
cmake -G Ninja ..

ninja
```

And run the program
```
streamlit run main.py
```

## Ubuntu

Install python venv

Run the following: 
```
cd /path/to/project[...]cmake/folder/

mkdir build && cd build

python3 -m venv virtenv

source ./virtenv/bin/activate

pip install streamlit pybind11
```
And then build the C code
```
cmake ..

make
```

And run the program
```
streamlit run main.py
```

if not in venv activate it again using source ./virtenv/bin/activate