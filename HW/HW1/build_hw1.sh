#!/bin/bash

# Builds student submission for hw1; requires Egg built and g++ installed

./egg compile hw1.egg hw1.hpp && g++ -std=c++14 -o hw1 hw1.cpp