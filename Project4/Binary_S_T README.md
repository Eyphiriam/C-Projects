# README for Dish Counter Binary Search Tree

This README provides a comprehensive overview of the Dish Counter Binary Search Tree program implemented in C++. This program uses a binary search tree (BST) to manage and count dish orders based on user input.

## Project Overview

The Dish Counter Binary Search Tree is a simple C++ application designed to demonstrate the use of binary search trees for counting occurrences of items. It allows users to input a sequence of dish numbers, and it maintains a count of each dish using a BST. The program then displays each dish with its corresponding count, providing a clear summary of all dishes ordered.

## Features

- **Binary Search Tree Implementation**: Efficiently manages dish numbers and their counts.
- **Dynamic Input Handling**: Processes a string of dish numbers entered by the user.
- **Count Display**: Outputs the count of each dish in ascending order of dish numbers.
- **Dish Mapping**: Maps dish numbers to specific dish names for user-friendly output.

## How It Works

1. **Node Structure**: Each node in the BST contains:
   - `dishNumber`: The number of the dish.
   - `counter`: The count of how many times the dish has been ordered.
   - `left` and `right`: Pointers to the left and right child nodes.

2. **BST Operations**:
   - **Insertion**: Adds a new dish or increments the counter if the dish already exists.
   - **Search**: Checks if a dish number is already in the tree.
   - **In-order Display**: Recursively displays dishes in numerical order.

3. **Main Functionality**:
   - Reads a line of input representing dish numbers separated by spaces.
   - For each dish number, the program either adds a new node to the BST or increments the existing node's counter.
   - After processing all input, the program displays the list of dishes with their counts.

## Usage

### Compilation

Compile the program using a C++ compiler that supports C++11. For example, using g++:

```bash
g++ -o dish_counter main.cpp
```

### Running the Program

Execute the compiled program:

```bash
./dish_counter
```

Enter dish numbers separated by spaces when prompted. For example:

```
Please enter:
1 2 2 3 4 5 6 7 7 7
```

### Output

The program will display the count of each dish ordered:

```
1 - Fried Chicken 1
2 - Pork Chops 2
3 - Baked Chicken 1
4 - Grilled Salmon 1
5 - Roast Beef 1
6 - Grilled Steak 1
7 - Meat Loaf 3
```

## Dish Mapping

The dishes are mapped as follows:

- `1`: Fried Chicken
- `2`: Pork Chops
- `3`: Baked Chicken
- `4`: Grilled Salmon
- `5`: Roast Beef
- `6`: Grilled Steak
- `7`: Meat Loaf

This README provides all necessary information to understand, compile, and run the Dish Counter Binary Search Tree program. It includes a description of features, usage examples, and details about the program's functionality.

Citations:
