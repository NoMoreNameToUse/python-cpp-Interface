import os
# After fumbling around find out you need to add your binary dlls on windows
if os.name == "nt":
    # CHANG INTO YOUR OWN c compiler binary Directory if on Windows!
    os.add_dll_directory("F:\\MSYS2\\ucrt64\\bin")

import cpp_code
import random

# Step 1: Generate 2D aray
rows = 5
cols = 4
generated_matrix = [[random.randint(0, 100) for _ in range(cols)] for _ in range(rows)]
print(f"Generated 2D Array in Python: {generated_matrix}")

# Step 2: Call the C++ function to generate a random 2D array of length nxm
random_matrix = cpp_code.create_random_2d_vector(rows, cols, 0,100)
print(f"Random array from C++:")
for row in random_matrix:
    print(row)

# Step 3: Add the two arrays
added_matrix = [[generated_matrix[i][j] + random_matrix[i][j] for j in range(cols)] for i in range(rows)]
print(f"Added matrix:")
for row in added_matrix:
    print(row)

# Step 4: Pass the added 2D array back to C++ for output
cpp_code.output_final_2d_vector(added_matrix)