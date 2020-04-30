
# CS 352 Assignment 6

## By Kai Richardson

### Notes

I have constructed two cpp files for this assignment.
One (retirement_par) follows all of your instructions in the "Tips for Parallelising" and is a reasonable speedup.
The other (retirement_par_fast) does not, and gets a much higher speedup. Furthermore, it consumes less resources.
This is due to my fast version being able to support the -O3 level of compilation.

Note: My optimizations and programming are tailored towards OMP_NUM_THREADS=8.

Parameters: 15000 0.06 35 0.04 5000000

#### Sequential data

25th percentile: 1567402.88
         median: 1747570.95
75th percentile: 1949903.14

--Sequential--
wall: 9.43 sec
 CPU: 9.43 sec

#### Slower Data

25th percentile: 1554550.23
         median: 1814094.91
75th percentile: 2079293.99

--8-way Parallel--
wall: 5.82 sec
CPU: 43.54 sec

#### Faster Data

25th percentile: 1569888.62
         median: 1792788.40
75th percentile: 2064527.21

--8-way Parallel (Fast)--
wall: 5.11 sec
 CPU: 37.56 sec
