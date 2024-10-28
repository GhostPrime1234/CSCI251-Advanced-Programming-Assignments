# README

## Overview

This project is a simulation of a crowd sourcing system where tasks are assigned to workers based on their performance. The program processes two input files: `Tasks.txt` and `Workers.txt`, and generates an output file, `Output.txt`, detailing the assignment of tasks to workers. The project follows procedural programming principles and is implemented in C++ using structs for data management.

## File Structure

The project consists of the following source code files:

1. **driver.cpp**:
    - This file contains the `main()` function, which serves as the entry point for the program. The main function is responsible for reading the input files, invoking functions to process tasks and workers, and generating the output file.
    - It ensures the correct number of command-line arguments are provided and then proceeds with initializing arrays for tasks and workers. After reading the worker and task data, it calls the appropriate functions to assign tasks to workers.

2. **header.h**:
    - This header file contains the declarations of the structs (`Worker` and `Task`) used to store the information about workers and tasks.
    - It also includes the prototypes for the functions used to read data from files, calculate worker performance, and assign tasks to workers.

3. **header.cpp**:
    - This file contains the implementations of the functions declared in `header.h`.
    - Functions include reading tasks and workers from files, calculating the average performance of workers based on a normal distribution, and assigning tasks to workers based on their performance.

## How to Run the Program

1. **Compile the Program**:  
   Ensure that the source files (`driver.cpp`, `header.h`, `header.cpp`) are in the same directory. Use the following command to compile the program:
   ```bash
   g++ driver.cpp header.cpp -o prog -std=c++17
   ```

2. **Run the Program**:  
   After compiling, you can run the program by providing the `Tasks.txt`, `Workers.txt`, and `Output.txt` as arguments:
   ```bash
   ./prog Tasks.txt Workers.txt Output.txt
   ```
    - `Tasks.txt`: The input file containing the list of tasks.
    - `Workers.txt`: The input file containing the list of workers.
    - `Output.txt`: The output file where the results of the task assignments are saved.

3. **Output**:  
   The output file (`Output.txt`) will contain detailed information about each task processed, including whether it was successfully assigned to a worker, the workers' performance scores, and the results of their trials.

## Important Notes

- The input files `Tasks.txt` and `Workers.txt` must follow the specific format described in the assignment specifications.
- The program assumes a maximum of 20 workers and 20 tasks, as per the assignment requirements.
- The output file will be overwritten each time the program is run.

