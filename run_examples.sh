#!/bin/bash
### use: ./run_examples <program.c>

gcc -Wall -ansi -pedantic $1 -o proj2
./proj2 < tests/ex0.in > tests/ex0.mine.out; diff -q tests/ex0.out ex0.mine.out
./proj2 < tests/ex1.in > tests/ex1.mine.out; diff -q tests/ex1.out ex1.mine.out
./proj2 < tests/ex2.in > tests/ex2.mine.out; diff -q tests/ex2.out ex2.mine.out
./proj2 < tests/ex3.in > tests/ex3.mine.out; diff -q tests/ex3.out ex3.mine.out
./proj2 < tests/ex4.in > tests/ex4.mine.out; diff -q tests/ex4.out ex4.mine.out
