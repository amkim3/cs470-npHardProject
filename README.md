## The Subset Sum Problem: A Brute-Force and Heuristic Solution, and Mappings to other NP-Complete Problems
The subset sum problem is a common NP-Hard problem that **takes an input of integers, as well as a target sum, and determines whether a subset from the input can be added together to reach the target sum.** More information on the subset sum problem can be found on [Wikipedia.](https://en.wikipedia.org/wiki/Subset_sum_problem). The traditional subset sum problem returns only a "yes" or "no" depending on if the subset sum can be found; in this implementation, if the subset is found, the subset is also returned and printed for the user's convenience. Although findind the list of included elements adds to the overall time to find the subset sum, the list could potentially be useful and is simple to remove if the user only wants a yes/no answer.

## The Solution
There are two main parts of this project:
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
  ### 2. Heuristic solution
  The heuristic solution is designed to be exponentially faster than the brute force method. This solution provides a solution in pseudo-polynomial time. The downside of   this solution is that unlike the brute force method, it does not provide the correct answer 100% of the time.
