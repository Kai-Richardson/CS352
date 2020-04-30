#!/bin/bash

./egg compile calc.egg calc.hpp
echo "egged"
g++ -std=c++14 ./calc.cpp -o calc
echo "built and launched:"
./calc