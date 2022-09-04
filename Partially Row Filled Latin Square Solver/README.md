# Partially Row Filled Latin Square Solver

This algorithm converts any nxn partially row filled Latin Square into a valid Latin Square. User input creates the nxn partially row filled Latin Square.

The algorithm is able to solve the Latin Square through recursive backtracking or a bitmask approach. Both approaches take the same upper bound time complexity of O(n^m) where m is the number of blank spaces and n is the number of possibilities to fill that space. However, the bitmask approach can check if a number is valid in a certain index in constant time. 

A partially row filled Latin Square(also known as a Latin Rectangle) is a Latin Square that has at least 1 out of n rows fully filled in. However, it must not have n rows filled in because that would make it a Latin Square. Using an application of Hall's Marriage Theorem as proof, any partially row filled Latin Square can be fully completed into a Latin Square.

Further Reading: http://www.math.caltech.edu/~2014-15/1term/ma006a/class28.pdf

Acknowledgements: https://www.geeksforgeeks.org/sudoku-backtracking-7/


