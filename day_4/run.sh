#!/bin/bash

# Run the program
mpic++ -o sol sol.cpp && mpirun -np 141 ./sol