/*
Mr. Lee has to travel various offices abroad to assist branches of each place. But he has a problem. 
The airfare would be real high as all offices he has to visit are in foreign countries. He wants to visit every 
location only one time and return home with the lowest expense. Help this company-caring man calculate the lowest expense.


Input format
Several test cases can be included in the inputs. T, the number of cases is given in the first row of the inputs. 
After that, the test cases as many as T (T ≤ 30) are given in a row. N, the number of offices to visit is given on 
the first row per each test case. At this moment, No. 1 office is regarded as his company (Departure point). 
(1 ≤ N ≤ 12) Airfares are given to move cities in which branches are located from the second row to N number rows.
i.e. jth number of ith row is the airfare to move from ith city to jth city. If it is impossible to move between 
two cities, it is given as zero.

Output format
Output the minimum airfare used to depart from his company, visit all offices, and then return his company on the 
first row per each test case.

Example of Input

3
5
0 14 4 10 20
14 0 7 8 7
4 5 0 7 16
11 7 9 0 2
18 7 17 4 0
5
9 9 2 9 5
6 3 5 1 5
1 8 3 3 3
6 0 9 6 8
6 6 9 4 8
3
0 2 24
3 0 2
0 4 0

Example of Output

30
18
4
*/

#include <bits/stdc++.h>
using namespace std;

int totalCost(vector<vector<int>> &cost, int mask, int pos, int n, vector<vector<int>> &dp) {
    // If all offices are visited, return the cost to go back to the starting office (office 0)
    if (mask == (1 << n) - 1) {
        if (cost[pos][0] == 0) return 1e9; // Return a large value if return path is impossible
        return cost[pos][0];
    }

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = 1e9; // Use a sufficiently large value to represent infinity

    for (int i = 0; i < n; i++) {
        // If the office is not visited and there is a valid path to it
        if ((mask & (1 << i)) == 0 && cost[pos][i] != 0) {
            ans = min(ans, cost[pos][i] + totalCost(cost, mask | (1 << i), i, n, dp));
        }
    }

    return dp[mask][pos] = ans;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<vector<int>> cost(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    // DP table initialized with -1. Max states: 2^n * n
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    
    // Start at office 0 (No. 1 office), mask starts as 1 (only office 0 visited)
    int min_expense = totalCost(cost, 1, 0, n, dp);

    // If min_expense is still our "infinity" value, it means no valid route was found
    if (min_expense >= 1e9) {
        cout << 0 << "\n";
    } else {
        cout << min_expense << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int test_cases;
    if (cin >> test_cases) {
        while (test_cases--) {
            solve();
        }
    }
    return 0;
}
