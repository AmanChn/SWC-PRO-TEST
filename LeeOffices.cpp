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

#include<bits/stdc++.h>
using namespace std;

int totalCost(vector<vector<int>> &cost, int mask, int pos, vector<vector<int>> &dp){
    int n = cost.size();

    if( mask == (1<<n) -1 ) return cost[pos][0];

    if( dp[mask][pos] != -1 ) return dp[mask][pos];

    int ans = INT_MAX;

    for( int i=0; i<n; i++ ){
        if( (mask & (1<<i)) == 0 ){
            ans = min(ans, cost[pos][i] + totalCost(cost,mask | (1<<i), i,dp));
        }
    }

    return dp[mask][pos] = ans;
}

int main(){
    int test_cases;
    cin>>test_cases;

    while( test_cases-- ){
        int n;
        cin>>n;

        vector<vector<int>> cost(n, vector<int>(n,0));

        for( int i=0; i<n; i++ ){
            for( int j=0; j<n; j++ ){
                cin>>cost[i][j];
            }
        }

        //TSP with bitmask DP
        int mask = 1, pos = 0;

        vector<vector<int>> dp((1<<n), vector<int>(n,-1));

        cout<<totalCost(cost,mask,pos,dp);

        cout<<endl;
        for( auto i : dp ){
            for( auto j : i){
                cout<<j<<" ";
            }
            cout<<endl;
        }cout<<endl;
    }

    return 0;
}