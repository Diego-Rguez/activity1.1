# Activity 1.1 - Problem A: Count Inversions

## Problem Description
Given an array of $N$ integers, count the total number of **inversions**. An inversion is defined as a pair of indices $(i, j)$ such that:
$$i < j \quad \text{and} \quad A[i] > A[j]$$

Inversions measure how "out of order" an array is. A completely sorted array has $0$ inversions, while a reverse-sorted array has the maximum possible inversions ($\frac{N(N-1)}{2}$).

## Algorithmic Approach
This problem is solved using **Divide and Conquer** by modifying the standard **Merge Sort** algorithm:

1. **Divide:** Split the array into left and right halves.
2. **Conquer:** Recursively count inversions in the left half and right half.
3. **Combine (Split Inversions):** During the merge step, if an element in the right subarray $A[j]$ is strictly smaller than an element in the left subarray $A[i]$, then $A[j]$ is smaller than *all* remaining elements in the left subarray (from index $i$ to $mid$). We accumulate `mid - i + 1` cross-inversions.

## Complexity Analysis
* **Time Complexity:** $\mathcal{O}(N \log N)$  
  The recursion tree has depth $\log N$, and merging at each level takes linear $\mathcal{O}(N)$ time.
* **Space Complexity:** $\mathcal{O}(N)$  
  Auxiliary vector used for merging elements alongside $O(\log N)$ call stack space.

## Compilation & Execution
```bash
g++ -std=c++17 -O2 main.cpp -o run
./run