/*
You have to place an electronic banner of a company as high as it can be, so that whole the city can view the banner 
standing on top of TWO PILLERS.
The height of two pillers are to be chosen from given array.. say [1, 2, 3, 4, 6]. We have to maximise the height
of the two pillars standing side by side, so that the pillars are of EQUAL HEIGHT and banner can be placed on top of it.
In the above array, (1, 2, 3, 4, 6) we can choose pillars like this, say two pillars as p1 and p2.
In case, there is no combination possible, print 0.

INPUT :
1
5
1 2 3 4 6
Output :
8
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<int> rods(n);
    int total_sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> rods[i];
        total_sum += rods[i];
    }

    // dp[i] stores the maximum height of the taller pillar 
    // such that (taller - shorter) == i.
    // We initialize with -1 to represent unreachable states.
    vector<int> dp(total_sum + 1, -1);
    
    // Base case: Two pillars of height 0 have a difference of 0.
    dp[0] = 0;

    for (int x : rods) {
        // We create a copy of the current DP state to avoid using 
        // values updated in this same iteration.
        vector<int> next_dp = dp;

        for (int d = 0; d <= total_sum; ++d) {
            // If the current difference 'd' is unreachable, skip it
            if (dp[d] == -1) continue;

            int h1 = dp[d];      // Height of the taller pillar
            int h2 = h1 - d;     // Height of the shorter pillar

            // Option 1: Add rod 'x' to the taller pillar
            // New diff becomes (d + x)
            if (d + x <= total_sum) {
                next_dp[d + x] = max(next_dp[d + x], h1 + x);
            }

            // Option 2: Add rod 'x' to the shorter pillar
            // The new difference is the absolute difference between the pillars
            int new_diff = abs(d - x);
            // The new max height depends on which pillar becomes taller
            int new_taller_height = max(h1, h2 + x);
            
            next_dp[new_diff] = max(next_dp[new_diff], new_taller_height);
        }
        // Update the main dp array for the next rod
        dp = next_dp;
    }

    // dp[0] holds the max height where diff is 0. 
    // If it's 0 (and we had rods), it means no non-zero solution was found.
    // However, the problem asks to print 0 if no combination is possible.
    cout << dp[0] << endl;
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}