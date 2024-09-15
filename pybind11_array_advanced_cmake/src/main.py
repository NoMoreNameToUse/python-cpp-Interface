import os
# After fumbling around find out you need to add your binary dlls on windows
if os.name == "nt":
    # CHANG INTO YOUR OWN c compiler binary Directory if on Windows!
    os.add_dll_directory("F:\\MSYS2\\ucrt64\\bin")
    
import cpp_code
import random

# Step 1: Generate a Python list of integers
n = 10
generated_array = [random.randint(0, 100) for _ in range(n)]
print(f"Generated array in Python: {generated_array}")

# Step 2: Call the C++ function to generate a random array of length n
random_array = cpp_code.create_random_vector(n,0,100)
print(f"Random array from C++: {random_array}")

# Step 3: Add the two arrays
added_array = [generated_array[i] + random_array[i] for i in range(n)]
print(f"Added array: {added_array}")

# Step 4: Pass the added array back to C++ for output
cpp_code.output_final_array(added_array)