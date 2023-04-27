## The Subset Sum Problem: A Brute-Force and Heuristic Solution, and Mappings to other NP-Complete Problems
The subset sum problem is a common NP-Hard problem that **takes an input of integers, as well as a target sum, and determines whether a subset from the input can be added together to reach the target sum.** More information on the subset sum problem can be found on [Wikipedia.](https://en.wikipedia.org/wiki/Subset_sum_problem). The traditional subset sum problem returns only a "yes" or "no" depending on if the subset sum can be found; in this implementation, if the subset is found, the subset is also returned and printed for the user's convenience. Although findind the list of included elements adds to the overall time to find the subset sum, the list could potentially be useful and is simple to remove if the user only wants a yes/no answer.

## Getting started and important information
  ### Installation
  This project is written entirely in C++. Click [here](https://techdecodetutorials.com/how-to-install-c-compiler-in-windows-10/) to learn how to download a C++  
   compiler. There are numerous IDEs that will work well with C++. Click [here](https://code.visualstudio.com/download) to download Visual Studio Code, which is one of 
   the most popular IDEs for C++.
  ### Compiling and Running
  This project comes with a makefile. In order to compile, simply run make build, make clean, make, or make all. To run the project, type ./a.out into the terminal and press enter. The code will then prompt you to enter a number between 1 and 4 to execute different areas of the project (execute basic subset sum, map from vertex cover to subset sum, map from 3sat to subset sum, or exit). The description of each command is clearly described in the prompt. Once you type in the number of command you wish to execute, you will be prompted to enter a file that is of the correct format. For example, if you wish to execute a mapping between vertex cover and subset sum, you will need to provide a file that contains a correctly formatted vertex cover problem. Once the file has been specified, the code runs the mapping and outputs whether the subset sum could be found. You are then given the option to either type in another command, or exit the program.

## The Solution to Subset Sum
  ### File format
The input for a subset sum file should be formatted like the following: <br />
15 <br />
7<br />
6<br />
5<br />
5<br />
3<br />
3<br />
1<br />
3<br />
4<br />
5<br />
$ <br />
The first line represents the target sum and each subsequent line before the $ represents an element in the set.<br /><br />
There are two solutions for solving the subset sum problem. For each type of solution, a timer was used to track how long the algorithm took to complete. Below are the two types of solutions.
  ### 1. Brute force solution
  In this solution, the subset sum problem is solved using traditional methods that return the correct result 100% of the time. However, the downside of this solution is   the time taken to find the solution. The code for this solution is titled "brute.cpp." To understand the algorithm fully, please examine the code and comments. 
  
  A brief definition is as follows: the function is given a vector of integers, the size of the vector, and a target sum. It then creates a vector of vectors of      
  boolean type, called the cache. The cache size will be (size of vector of integers + 1) x (target sum + 1). Once the cache is completed, a user could access cache[i]
  [j] and, if the value at cache[i][j] is true, the user would know there is a subset from [0 ... i] that sums to j. Below is a visualization of how the cache works. 
  
       0    1   2   3   ...     sum
    
    0  T    F   F   F   F       F
    
    5  T    F   F   F   F       F
    
    3  T    F   F   T   F       F
    
    8  T    F   F   T   F       F
    
    .
    .
    .
  
  Once the cache has been filled, we execute a loop to check which elements were used to find the subset sum. We passed a vector, called "included," to the function  in the beginning by reference; this vector is edited to now hold the elements included. When the function returns to main, the elements are printed along with how long the algorithm took to complete.
  ### 2. Heuristic solution
  The heuristic solution is designed to be exponentially faster than the brute force method. The algorithm provides a solution in pseudo-polynomial time. The downside of this solution is that unlike the brute force method, it does not provide the correct answer 100% of the time. Below is how the algorithm works: <br />
  1. The array is sorted in descending order. Every 0 in the array is taken out, as these do not add anything to the subset. <br />
  2. An int variable called "remaining" and set equal to the sum. This variable will keep track of the remaining sum needed as elements are added. <br />
  3. The algorithm finds the first index in the array that is less than or equal to the sum needed, called "j." This allows the algorithm to run faster, as it does not have to enter the for loop with elements too large to add. This would be especially helpful if the given array of integers contains a large amount of numbers larger than the target sum. <br />
  4. The code then enters a for loop, starting at j and ending at the size of the array. The for loop has various if statements. <br />
      a. **if remaining < array.back()** this if statement checks if the remaining amount needed is less than the smallest element in the array available. If this is true, the code block removes a random element from the list of included elements and adds it back to the original array. To avoid adding the element again on the next iteration, a variable called "dontAddBack" is set to the element removed. <br />
      b. **if array[i] == remaining** this if statement checks if the current element equals the remaining amount needed. If this is true, it adds the element to the included vector and breaks from the loop. <br />
      c. **if array[i] > remaining** this if statement checks if the current element is larger than the remaining amount needed. If this is the case, the code does a search to find the next largest element that is less than or equal to the remaining amount needed. Once found, the element is added to the included vector and deleted from the original array. If that element made remaining 0, a break statement is executed. Otherwise, the iterator "i" is set to the new index found minus 1. <br />
      d. **if remaining > array[i]** this if statement checks if the current element is less than the remaining amount needed. If this is true, the element is added to the included vector and deleted from the original array. <br />
  Once the loop is exited, either because the size of array has been reached or because of a break statement, a final check is used to ensure the list of included elements actually equals the target sum. If it does, it returns true. Otherwise, it returns false. Once the function returns to main, main prints whether the solution could be found, as well as how long it took and the list of included elements (if applicable). 
  
## Mapping from vertex cover to subset sum
A vertex cover of a graph is a set of vertices that includes at least one endpoint to every edge of the graph. To learn more, visit the vertex cover [Wikipedia.](https://en.wikipedia.org/wiki/Vertex_cover) 
  ### File format
  An example input for vertex cover looks like the following: <br />
7 3 <br />
6 5 1 <br />
5 4 1 <br />
4 3 1 <br />
3 2 1 <br />
2 1 1 <br />
1 0 1 <br />
$ <br />
The first line contains 2 important numbers: the first tells the program how many vertices there are. The second is the required size of the vertex cover. This number is important for the subset sum to correctly compute the subset sum and therefore the vertex cover.
  ### Algorithm
 Refer to the file "mapFromVC.cpp" to see the full algorithm that maps vertex cover to subset sum. <br /> The algorithm begins by creating n + m integers, where n is the number of vertices and m is the number of edges. It also creates a target value T equal to  $$k * 4 +\sum_{i=0}^{m-1} 2 * 4^i$$ Where k is the size of the vertex cover. Each integer is a m + 1-digit number in base 4. For the integers between 0 and the number of vertices, the most significient digit is 1. For the rest, the value at an index i is 1 if the ith edge contains the vertex. For the integers between the number of vertices and the number of edges, the most significant digit is 0 and each index i is 1 if the integer represents an edge. Below is an example of this format: <br />
 
 Vertices: {0,1,2,3}<br />
 Edges: {(3,2), (2,1), (1,0)}<br />
 New integers: <br />
 1 0 0 1 <- 0 appears in the last edge<br />
 1 0 1 1 <- 1 appears in the second to last and last edge<br />
 1 1 1 0 <- 2 appears in the first and second edge<br />
 1 1 0 0 <- 3 appears only in the first edge<br />
 0 1 0 0 <- edge (3,2) <br />
 0 0 1 0 <- edge (2,1)<br />
 0 0 0 1 <- edge (1,0)<br />
 
 The graph has a vertex cover of size k if there is a subset of the integers above that sum to T. These numbers are passed to the subset sum brute algorithm and heurisitc algorithm, which returns whether a subset sum could be found.

## Mapping from 3sat to subset sum
The boolean satisfiability problem (SAT) is the problem of determining if there exists an interpretation that satisfies a given boolean formula. The 3SAT problem is a variant of the SAT, where each clause contains exactly 3 literals. More information on the SAT problem can be found on the [Wikipedia.](https://en.wikipedia.org/wiki/Boolean_satisfiability_problem)
### File format
The format for a 3SAT input should look like the following:
3<br />
1 2 -3<br />
-1 2 -3<br />
$<br />
Where the first line specifies the number of variables, and each subsequent line is a clause.
### Algorithm
The algorithm is similar to the mapping from vertex cover to subset sum. For each variable, we create an integer of size n + m, where n is the number of variables and m is the number of clauses. The total number of these integers will be (n + m) * 2, because for each variable and clause, we will have an integer to represent the variable and clause, as well as the negation. These integers will be filled with 1s and 0s. Below is an example of how the data structure works.<br />
Variables: 3<br />
Clauses: (1 2 -3) (-1 2 -3)<br />


         1    2   3   C1   C2
    
    1   1    0   0   1     0    <- the variable 1 appears in clause 1
    
    1'  1    0   0   0     0    <- the negation of 1 appears in neither clause 1 nor clause 2
    
    2   0    1   0   1     1    <- the variable 2 appears in clause 1 and clause 2
    
    2'  0    1   0   0     0    <- the negation of 2 appears in neither clause 1 nor clause 2
    
    3   0    0   1   0     0    <- the variable 3 appears in neither clause 1 nor clause 2
    
    3'  0    0   1   1     1    <- the negation of 3 appears in clause 1 and clause 2
    
    C1  0    0   0   1     0    <- clause 1
    
    C1' 0    0   0   1     0    <- negation of clause 1
    
    C2  0    0   0   0     1    <- clause 2
    
    C2' 0    0   0   0     1    <- negation of clause 2
    
    
  The target sum will be a base 4 number of digit size (n + m). Starting at the most significant digit, a 1 is added for each variable. After all variables have been accounted for, each clause adds a 3 to the end of the integer. For the example above, the target sum would be 11133. The integers and target sum are then passed to the subset sum brute force and heuristic algorithms, which returns whether the subset sum can be found and therefore whether the 3sat problem can be solved.
 
