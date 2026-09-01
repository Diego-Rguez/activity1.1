# Activity 1.1 - Problem C: Budgeted Study Plan (0/1 Knapsack)

## Problem Description
Given $N$ study modules, where each module $i$ requires $time_i$ hours and yields $value_i$ points, determine the **maximum total score** achievable within a strict time budget $T$. Each module can be selected at most once (0/1 choice).

## Algorithmic Approach
This problem is solved using **Dynamic Programming with 1D Memory Optimization**:

1. **State Definition:** Let `dp[t]` store the maximum value achievable with a time capacity of $t$ hours ($0 \le t \le T$).
2. **Base Case:** Initialize `dp` array of size $T + 1$ with all $0$s.
3. **State Transition:** For each module with cost $time$ and reward $value$, update the states backwards from $T$ down to $time$:
   $$\text{dp}[t] = \max(\text{dp}[t], \text{value} + \text{dp}[t - \text{time}])$$
4. **Space Optimization Note:** Iterating $t$ in reverse (from $T$ down to $time$) guarantees that values from the current item do not overwrite states needed for the same item, preventing an item from being picked more than once.

## Complexity Analysis
* **Time Complexity:** $\mathcal{O}(N \cdot T)$  
  Nested loops: outer loop runs $N$ times, inner loop runs up to $T$ times.
* **Space Complexity:** $\mathcal{O}(T)$  
  Optimized from the naive $\mathcal{O}(N \cdot T)$ 2D matrix down to a 1D vector of size $T + 1$.

## Compilation & Execution
```bash
g++ -std=c++17 -O2 main.cpp -o run
./run