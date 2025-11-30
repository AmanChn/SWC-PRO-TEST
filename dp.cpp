#include<bits/stdc++.h>
using namespace std;

int subsetSum(vector<int> &arr, int sum, int n) {
    if(sum == 0) {
        return 1;
    }

    if( n==0 ) return 0;

    if( arr[n-1] <= sum ){
        return subsetSum(arr,sum-arr[n-1],n-1) + subsetSum(arr,sum,n-1);
    }
    else{
        return subsetSum(arr,sum,n-1);
    }
}

int subsetSumIter(vector<int> &arr, int sum, int n){
    if( sum == 0 ) return 1;
    vector<vector<int>> dp(n+1, vector<int>(sum+1,0));

    for(int i=0; i<=n; i++){
        for( int j=0; j<=sum; j++ ){
            if( i == 0 ){
                dp[i][j] = 0;
            }
            if( j == 0 ){
                dp[i][j] = 1;
            }
        }
    }

    for(int i=1; i<=n; i++){
        for( int j=1; j<=sum; j++ ){
            if( arr[i-1] <= j ){
                dp[i][j] = dp[i-1][j-arr[i-1]] + dp[i-1][j];
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[n][sum];
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5,6,5,4,8,4};
    int n = arr.size();
    int sum = 15;
    
    cout<<"count of subset sum with a given sum:"<<subsetSum(arr,sum, n)<<endl;
    cout<<"count of subset sum with a given sum:"<<subsetSumIter(arr,sum, n)<<endl;

    return 0;
}