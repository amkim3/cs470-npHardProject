## The Subset Sum Problem: A Brute-Force and Heuristic Solution, and Mappings to other NP-Complete Problems
The subset sum problem is a common NP-Hard problem that **takes an input of integers, as well as a target sum, and determines whether a subset from the input can be added together to reach the target sum.** More information on the subset sum problem can be found on [Wikipedia.](https://en.wikipedia.org/wiki/Subset_sum_problem). The traditional subset sum problem returns only a "yes" or "no" depending on if the subset sum can be found; in this implementation, if the subset is found, the subset is also returned and printed for the user's convenience. Although findind the list of included elements adds to the overall time to find the subset sum, the list could potentially be useful and is simple to remove if the user only wants a yes/no answer.

## The Solution
There are two main parts of this project. For each type of solution, a timer was used to track how long the algorithm took to complete. Below are the two types of solutions.
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
      
