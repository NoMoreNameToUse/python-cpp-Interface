import os
# After fumbling around find out you need to add your binary dlls on windows
if os.name == "nt":
    # CHANG INTO YOUR OWN c compiler binary Directory if on Windows!
    os.add_dll_directory("F:\\MSYS2\\ucrt64\\bin")
import time
import random
import streamlit as st  # Import Streamlit

import cpp_code  # Import C++ code for matrix operations

# Sidebar (you can add more controls here)
st.sidebar.title("多余的但是很漂亮的界面")
st.sidebar.write("这玩意比命令行好看多了，数据实时显示而且还可以互动之类的")
st.sidebar.write("尤其是训练模型时的一些可视化和图表可以直接生成")
st.sidebar.write("而且如果不更新界面的话算力消耗很小")
st.sidebar.write("更多信息 https://streamlit.io/ 可以运行下 streamlit hello或者看网上的示例")
st.sidebar.write("这个大部分是chatgpt帮我生成的懒得手写了， C++不用改，代码同2DArray_Advanced")
st.sidebar.write("每秒运行一次，C 输出还是命令行")
# Number of rows and columns for the matrices
rows = 5
cols = 4

# Create placeholders for dynamic content
col1, col2, col3 = st.columns(3)

# Add descriptions outside of placeholders so they don't get overridden
col1.write("Generated 2D Array in Python:")
col2.write("Random 2D Array from C++:")
col3.write("Added 2D Array:")

# Create placeholders for the matrices
col1_placeholder = col1.empty()
col2_placeholder = col2.empty()
col3_placeholder = col3.empty()

# Infinite loop to update the matrices once per second
while True:
    # Step 1: Generate 2D array in Python
    generated_matrix = [[random.randint(0, 100) for _ in range(cols)] for _ in range(rows)]

    # Step 2: Call the C++ function to generate a random 2D array
    random_matrix = cpp_code.create_random_2d_vector(rows, cols, 0, 100)

    # Step 3: Add the two arrays
    added_matrix = [[generated_matrix[i][j] + random_matrix[i][j] for j in range(cols)] for i in range(rows)]

    # Update the dataframes in their respective placeholders
    col1_placeholder.write("Generated 2D Array in Python:")
    col1_placeholder.dataframe(generated_matrix)

    col2_placeholder.write("Random 2D Array from C++:")
    col2_placeholder.dataframe(random_matrix)

    col3_placeholder.write("Added 2D Array:")
    col3_placeholder.dataframe(added_matrix)

    # Sleep for 1 second before updating again
    time.sleep(1)