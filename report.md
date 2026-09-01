# Mini Lab Report: Algorithm Design Techniques

**Curso:** Algoritmos Avanzados  
**Actividad:** Actividad 1.1 - Mini-Lab  
**Fecha:** Septiembre de 2026  
**Autor:** Diego Rodríguez Sánchez

---

## Report Summary
This report analices the desing, implementation and evaluation of 3 algorithm problems. Each problem was solved using a different design paradigm depending on the data structure and constraints:
1. **Problema A (Inversion Counting):** Solved using **Divide & Conquer** ($\mathcal{O}(N \log N)$ time, $\mathcal{O}(N)$ space).
2. **Problema B (Asignación de Salas de Reunión):** Solved using **Greedy algorithm with Min-Heap** ($\mathcal{O}(M \log M)$ time, $\mathcal{O}(M)$ space).
3. **Problema C (Plan de Estudio Presupuestado):** Solved using **Dinamic Programing (DP)** with optimization of space 1D (AI recommended)($\mathcal{O}(N \cdot T)$ time, $\mathcal{O}(T)$ space).

---

## Use of AI in this Activity
During the development of this activity i used Gemini to bounce ideas in order to solve doubts and some mistakes during the process of pseudocoding and ideating of the algorithm. In **Problem C** it was used in order to find the way to apply the DP because i knew it was DP because we needed to store certain information but i didnt figure out how to store it and use it. Also it was used to format the corresponding readme.md and report.md for a better structure.

---

## Problem A — Inversion Counter for Quality Control

### 1. Problem Summary
Given an array $A$ of $N$ integers, compute the total number of **inversions**. An inversion is defined as a pair of indices $(i, j)$ such that $i < j$ and $A[i] > A[j]$. Inversions measure how far an array is from being sorted. With constraints up to $N = 2 \cdot 10^5$, a brute-force approach using nested loops ($\mathcal{O}(N^2)$) exceeds the time limit.

### 2. High-Level Algorithm Idea
We apply the **Divide and Conquer** paradigm by adapting the **Merge Sort** algorithm:
1. **Divide:** Recursively split the array into left and right halves.
2. **Conquer:** Recursively count inversions in the left half and right half.
3. **Combine (Cross Inversions):** During the merge step of the two sorted subarrays, if an element in the right subarray $A[j]$ is strictly smaller than an element in the left subarray $A[i]$, then $A[j]$ is smaller than $A[i]$ **and all remaining elements in the left half** (from $i$ to $mid$). Thus, we accumulate `mid - i + 1` cross-inversions in $\mathcal{O}(1)$ time.

## 3. Pseudocode
The corresponding reasoning and pseudocode is included in 2 images in the corresponding problem file...

#### 4. Example Execution (Step-by-Step Run)
* **Input:** $A = [2, 4, 1, 3, 5]$
  1. **Divide:** Split array into left half $L = [2, 4]$ and right half $R = [1, 3, 5]$.
  2. **Recursive Step:**
     * Count inversions in $L = [2, 4] \rightarrow 0$ inversions.
     * Count inversions in $R = [1, 3, 5] \rightarrow 0$ inversions.
  3. **Merge Step (Cross Inversions):**
     * Compare $L[0]=2$ and $R[0]=1 \rightarrow L[0] > R[0] \implies$ Cross inversions $+ (1 - 0 + 1) = 2$ (Inversion pairs: $(2,1)$ and $(4,1)$).
     * Compare $L[0]=2$ and $R[1]=3 \rightarrow L[0] \le R[1] \implies$ Append $2$ to temporary array.
     * Compare $L[1]=4$ and $R[1]=3 \rightarrow L[1] > R[1] \implies$ Cross inversions $+ (1 - 1 + 1) = 1$ (Inversion pair: $(4,3)$).
     * Append remaining elements $4$ and $5$.
* **Output:** Total Inversions = $0 + 0 + (2 + 1) = \mathbf{3}$.

---

### Problem B — Minimum Meeting Rooms (Scheduling)

#### 1. Problem Summary
Given a set of $M$ meetings, each defined by an interval $[s_i, e_i]$, determine the minimum number of rooms required to schedule all meetings without overlap. Two meetings sharing a boundary ($e_i = s_j$) do not conflict and can reuse the same room.

#### 2. High-Level Algorithm Idea
We utilize a **Greedy Strategy** combined with a **Min-Heap (Priority Queue)**:
1. **Sorting:** Sort all meetings chronologically by their start time $s_i$.
2. **Min-Heap Structure:** Maintain a min-heap storing the end times of active meetings in occupied rooms. The root of the heap represents the room that will be freed first.
3. **Greedy Allocation:** For each meeting, if its start time is greater than or equal to the root of the heap (`heap.top() <= meeting.start`), the room has been vacated and is reused (by performing a `pop`). Otherwise, a new room is allocated. We then push the current meeting's end time into the min-heap.

#### 3. Pseudocode
The corresponding reasoning and pseudocode is included in 2 images in the corresponding problem file...

#### 4. Example Execution (Step-by-Step Run)
* **Input:** Meetings: $(0, 30), (5, 10), (15, 20)$
  1. **Sort by Start Time:** Already sorted as $[(0, 30), (5, 10), (15, 20)]$.
  2. **Process $(0, 30)$:**
     * Min-Heap is empty $\rightarrow$ Allocate Room 1.
     * Push end time $30$. Heap state: `[30]` (Active Rooms: 1).
  3. **Process $(5, 10)$:**
     * Earliest end time $= 30 > 5 \rightarrow$ Conflict! Cannot reuse room.
     * Allocate Room 2 and push end time $10$. Heap state: `[10, 30]` (Active Rooms: 2).
  4. **Process $(15, 20)$:**
     * Earliest end time $= 10 \le 15 \rightarrow$ Room freed! Pop $10$ and reuse Room 2.
     * Push new end time $20$. Heap state: `[20, 30]` (Active Rooms: 2).
* **Output:** Minimum rooms required = $\mathbf{2}$.

---

### Problem C — Budgeted Study Plan (0/1 Knapsack)

#### 1. Problem Summary
Given $N$ study modules, where each module $i$ requires $t_i$ hours and yields $v_i$ benefit points, compute the maximum total score achievable within a strict time budget $T$. Each module can be selected at most once (0/1 decision). With $N \le 2000$ and $T \le 5000$, brute-force evaluation of $2^N$ subsets is infeasible.

#### 2. High-Level Algorithm Idea
We apply **Dynamic Programming with 1D Memory Optimization**:
1. **State Definition:** Let `DP[t]` store the maximum value achievable using at most $t$ hours ($0 \le t \le T$).
2. **Base Case:** An array `DP` of size $T + 1$ initialized to $0$.
3. **State Transition:** For each module $(time, value)$, update the array backwards from $T$ down to $time$:
   $$\text{DP}[t] = \max(\text{DP}[t], \text{value} + \text{DP}[t - \text{time}])$$
4. **Space Optimization:** Iterating backwards (from $T$ down to $time$) guarantees that `DP[t - time]` holds the value from the previous item iteration, preventing a module from being selected more than once.

#### 3. Pseudocode
The corresponding reasoning and pseudocode is included in 2 images in the corresponding problem file...

#### 4. Example Execution (Step-by-Step Run)
* **Input:** $N=3$, Budget $T=10$. Modules $(time, value)$: $(3, 4), (4, 5), (7, 10)$
  * **Initial State:** `DP` array of size 11 initialized to $0$:  
    `DP = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]`

  1. **Process Module 1 $(time=3, value=4)$:**
     * Iterate $t$ from $10$ down to $3$:
     * `DP[3...10]` updated to $\max(\text{DP}[t], 4 + \text{DP}[t-3]) = 4$.
     * `DP` state: `[0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4]`

  2. **Process Module 2 $(time=4, value=5)$:**
     * Iterate $t$ from $10$ down to $4$:
     * For $t \in [4, 6]$: `DP[t] = max(4, 5 + 0) = 5`.
     * For $t \in [7, 10]$: `DP[t] = max(4, 5 + DP[t-4]) = max(4, 5 + 4) = 9`.
     * `DP` state: `[0, 0, 0, 4, 5, 5, 5, 9, 9, 9, 9]`

  3. **Process Module 3 $(time=7, value=10)$:**
     * Iterate $t$ from $10$ down to $7$:
     * For $t = 10$: `DP[10] = max(9, 10 + DP[3]) = max(9, 10 + 4) = 14`.
     * For $t \in [7, 9]$: `DP[t] = max(9, 10 + DP[t-7]) = max(9, 10 + 0) = 10`.
     * `DP` state: `[0, 0, 0, 4, 5, 5, 5, 10, 10, 10, 14]`

* **Output:** Maximum total benefit at $T=10$ is $\text{DP}[10] = \mathbf{14}$.