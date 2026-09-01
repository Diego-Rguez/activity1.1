#include <iostream>
#include <vector>
using namespace std;

struct Module
{
    int value;
    int time;
};

int study_Budget(int n, int T, vector<Module> modulos)
{
    vector<int> DP = vector<int>(T + 1, 0);

    for (int i = 0; i < n; i++)
    {
        for (int t = T; t >= modulos[i].time; t--)
        {
            int dont_Take = DP[t];
            int Take = modulos[i].value + DP[t - modulos[i].time];
            DP[t] = max(dont_Take, Take);
        }
    }
    return DP[T];
}

int main()
{
    // TEST 1: Ejemplo Original
    // T = 10, Módulos: (3, 4), (4, 5), (7, 10)
    // Esperado: 14 (Takes modules 1 y 3)
    vector<Module> test1 = {{4, 3}, {5, 4}, {10, 7}}; // {value, time}
    cout << "Test 1 (Original): " << study_Budget(3, 10, test1)
         << " | Esperado: 14\n";

    // TEST 2: Tight Budgets
    // T = 5,
    // Esperado: 27 (Takes modules 2 y 3: time 3+2 = 5, value 12+15 = 27)
    vector<Module> test2 = {{10, 3}, {12, 3}, {15, 2}}; // {value, time}
    cout << "Test 2 (Tight Budget): " << study_Budget(3, 5, test2)
         << " | Esperado: 27\n";

    // TEST 3: All Times > T
    // T = 10,
    // Esperado: 0
    vector<Module> test3 = {{100, 11}, {500, 15}, {1000, 20}}; // {value, time}
    cout << "Test 3 (All Times > T): " << study_Budget(3, 10, test3)
         << " | Esperado: 0\n";

    // TEST 4: Large Values
    // T = 10,
    // Esperado: 1800000 (Takes modules 1 y 2: time 4+6 = 10, valu 800000+1000000 = 1800000)
    vector<Module> test4 = {{800000, 4}, {1000000, 6}, {900000, 7}};
    cout << "Test 4 (Large Values): " << study_Budget(3, 10, test4)
         << " | Esperado: 1800000\n";

    return 0;
}