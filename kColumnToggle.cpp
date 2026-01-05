// Given a Binary Matrix of M x N , and a value K, You can toggle columns of matrix k times, 
// with this given k, tell the maximum number of rows that can be made all 1s.

#include<bits/stdc++.h>
using namespace std;

int maxRowsOne(vector<vector<int>> &grid, int k){
    unordered_map<string, int> mp; // row:count

    int ans = INT_MIN;

    // go to each row and make it in string. now if multple rows are same, then on toggling a column
    // all will become 1 if one of the similar rows become 1.
    // in a row, num of 0 must be <= K for making all 1.
    // and also (k - numZero) should be divisible by 2 
    //because on toggling 2 times it will come to original state.
    // the map will have the count of rows that can be made all 1. so find max in that.
    for( auto row : grid ){
        string r = "";
        int numZero = 0;
        for( auto e : row ){
            if( e == 0 ) numZero++;
            r += e + '0';
        }
        if( numZero <= k && (k - numZero)%2 == 0 ){
            mp[r]++;
            ans = max(ans,mp[r]);
        }
    }

    return ans;
}

int main(){
    vector<vector<int>> grid = {
        {1,0,1,0},
        {1,0,0,0},
        {1,0,1,0}
    };
    
    int k=2;
    
    cout<<maxRowsOne(grid,k);

    return 0;
}