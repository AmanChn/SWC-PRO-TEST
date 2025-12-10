#include<bits/stdc++.h>
using namespace std;

int totalCost(vector<vector<int>> &cost, int mask, int pos, vector<vector<int>> &dp){
    int n = cost.size();
    
    if( mask == (1<<n) -1 ) return cost[pos][0];

    if( dp[mask][pos] != -1 ) return dp[mask][pos];

    int ans = INT_MAX;

    for( int i=0; i<n ; i++ ){
        if( (mask & (1<<i)) == 0 ){
            ans = min(ans,cost[pos][i] + totalCost(cost,mask|(i<<i),i,dp));
        }
    }

    return dp[mask][pos] = ans;
}

int travellingSalesman(){
    vector<vector<int>> cost = {
        {0,111},
        {112,0}
    };

    int n = cost.size();

    vector<vector<int>> dp(n+1, vector<int>(n+1,-1));

    int mask = 1, pos = 0;

    return totalCost(cost,mask,pos,dp);
}

int main(){
    
    cout<<travellingSalesman();

    return 0;
}