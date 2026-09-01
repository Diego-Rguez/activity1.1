#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Meeting
{
    int start;
    int end;
};

int room_Scheduling(Meeting meetings[], int m)
{
    sort(meetings, meetings + m, [](Meeting a, Meeting b)
         { return a.start < b.start; });

    priority_queue<int, vector<int>, greater<int>> salas;

    for (int i = 0; i < m; i++)
    {
        if (!salas.empty() && salas.top() <= meetings[i].start)
        {
            salas.pop();
        }
        salas.push(meetings[i].end);
    }
    return salas.size();
}

int main()
{
    // TEST 1: Standard Case
    // Meetings: [1, 4], [2, 5], [7, 9], [3, 6]
    // General overlap scenario.
    // Expected: 3 rooms (at t=3, meetings [1,4], [2,5], and [3,6] are active simultaneously)
    Meeting test1[] = {{1, 4}, {2, 5}, {7, 9}, {3, 6}};
    cout << "Test 1 (Standard Case): " << room_Scheduling(test1, 4)
         << " | Expected: 3\n";

    // TEST 2: Many Identical Start Times
    // Multiple meetings start at the exact same time (t=2) with different durations
    // Meetings: [2, 5], [2, 8], [2, 3], [5, 7]
    // Expected: 3 rooms (the first three meetings require distinct rooms at t=2)
    Meeting test2[] = {{2, 5}, {2, 8}, {2, 3}, {5, 7}};
    cout << "Test 2 (Many Identical Start Times): " << room_Scheduling(test2, 4)
         << " | Expected: 3\n";

    // TEST 3: Nested Intervals
    // A long meeting completely contains smaller meetings inside its timeframe
    // Meetings: [1, 10], [2, 4], [3, 5], [6, 8]
    // Expected: 3 rooms (between t=3 and t=4, [1,10], [2,4], and [3,5] overlap)
    Meeting test3[] = {{1, 10}, {2, 4}, {3, 5}, {6, 8}};
    cout << "Test 3 (Nested Intervals): " << room_Scheduling(test3, 4)
         << " | Expected: 3\n";

    // TEST 4: Back-to-Back Meetings
    // A meeting ends at the exact same time the next one begins
    // Meetings: [1, 3], [3, 5], [5, 7], [2, 4]
    // Validates the condition: 'salas.top() <= meetings[i].start'
    // Expected: 2 rooms ([1,3], [3,5], and [5,7] can reuse the SAME room)
    Meeting test4[] = {{1, 3}, {3, 5}, {5, 7}, {2, 4}};
    cout << "Test 4 (Back-to-Back Meetings): " << room_Scheduling(test4, 4)
         << " | Expected: 2\n";

    return 0;
}