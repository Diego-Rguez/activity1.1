# Activity 1.1 - Problem B: Room Scheduling (Meeting Rooms II)

## Problem Description
Given an array of $M$ meeting time intervals consisting of start and end times `[start, end]`, find the **minimum number of conference rooms** required to hold all meetings without any schedule overlaps.

## Algorithmic Approach
This problem is solved using a **Greedy Strategy with a Min-Heap (Priority Queue)**:

1. **Sort Intervals:** Sort all meetings chronologically by their `start` time.
2. **Min-Heap for Active Rooms:** Use a min-priority queue to track the `end` times of ongoing meetings in occupied rooms. The root of the heap always represents the room that will be freed first (`salas.top()`).
3. **Allocation Logic:** For each meeting:
   * If the earliest freeing room finishes before or at the current meeting's start time (`salas.top() <= meeting.start`), reuse that room by popping the old end time.
   * Allocate a room by pushing the current meeting's `end` time into the heap.
4. **Result:** The size of the min-heap at the end represents the peak number of simultaneous rooms needed.

## Complexity Analysis
* **Time Complexity:** $\mathcal{O}(M \log M)$  
  Sorting takes $\mathcal{O}(M \log M)$. Each meeting performs at most one `push` and `pop` on a heap of size $\le M$, costing $\mathcal{O}(\log M)$ per meeting.
* **Space Complexity:** $\mathcal{O}(M)$  
  In the worst-case scenario where all $M$ meetings overlap, the priority queue stores $M$ end times.

## Compilation & Execution
```bash
g++ -std=c++17 -O2 main.cpp -o run
./run