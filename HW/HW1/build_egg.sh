#!/bin/bash

# Builds Egg parser-generator; requires g++ installed.
cd egg-master
g++ -O2 --std=c++0x -o egg main.cpp
cp egg ../
