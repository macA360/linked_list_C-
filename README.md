# Linked List Implementation for Sensor Data Processing

## Project Description
This project implements a linked list in C++ designed to handle motion sensor data for a machine learning model. It supports both non-quantized (32-bit floating-point) and quantized (8-bit integer) data, with the type determined at runtime. The linked list preprocesses the data before storing it: normalizing for both types and quantizing for integers if necessary.

## Build and Run Instructions
To compile and run this project:

1. Open the solution file `biomex.sln` in Microsoft Visual Studio.
2. Set `classes.cpp` as the startup item by right-clicking on it in the Solution Explorer and selecting 'Set as StartUp Item'.
3. Build the project by selecting `Build > Build Solution` from the main menu, or by pressing `Ctrl+Shift+B`.
4. Run the program by selecting `Debug > Start Debugging`, or by pressing `F5`. Ensure the console window is open to view the program's output.

## Implementation Overview
The linked list is composed of `Node` objects, which are abstract and serve as a base for `FloatNode` and `IntNode` derived classes. Each `Node` class includes a `printData` method, polymorphically overridden to handle the specific data type's output. The `LinkedList` class manages nodes and provides an `append` method to add new nodes to the list, determining at runtime the type of node to create based on whether the model is quantized.

## Testing
The program has been tested with various floating-point values for both non-quantized and quantized nodes. On execution, the linked list is populated sequentially, first with non-quantized data, then with quantized data. The expected output is a console printout of the list contents after each addition, showing the processed (normalized and possibly quantized) values.

# Expected Output Example:

Appending non-quantized (float) nodes:

Contents of the non-quantized (float) list:
1.15 (float)
17.8 (float)
34.45 (float)

Appending quantized (int) nodes:

Contents of the quantized (int) list:
1.15 (float)
17.8 (float)
34.45 (float)
139 (int)
305 (int)
472 (int)


This output confirms that the list handles both data types as intended and applies the correct preprocessing steps.
