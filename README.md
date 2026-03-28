This project compares quicksort and mergesort on large datasets. You can load generated data or import numeric values from a CSV file, then view timing and correctness results in the terminal.

Build With CMake:

From the project root:
   powershell
cmake -S . -B build
cmake --build build


Run the program:
   powershell
.\build\sort_comparator.exe


Build With g++:

If you want to compile directly without CMake:
   powershell
g++ -std=c++17 main.cpp comparator.cpp dataloader.cpp sorter.cpp -o sort_comparator.exe


Run the program:
   powershell
.\sort_comparator.exe


How To Use The Program

When the program starts, it shows a menu with four options:

1) Load Data
2) Sort Data & Compare
3) Run All Conditions (Full Benchmark)
4) Quit

Option 1: Load Data

You can choose one of these dataset types:

Random data, Nearly sorted data, Reverse sorted data, Load from CSV file

For generated datasets, the program asks for a size 100-1000000.

For CSV input:

Enter the file path when prompted, Enter the maximum number of values to load, The loader reads numeric values and skips non-numeric

Option 2: Sort Data & Compare

This runs both sorting algorithms on the currently loaded dataset and prints:

name, size, quicksort time, mergesort time, whether each result is sorted correctly, which algorithm was faster

Option 3: Full Benchmark

This automatically runs comparisons on:

- random data
- nearly sorted data
- reverse sorted data

Each benchmark dataset uses 100000 elements.

Option 4: Quit

This exits the program.


Load a dataset before choosing Sort Data & Compare
CSV files can contain comma-separated values
Non-numeric CSV entries are ignored
