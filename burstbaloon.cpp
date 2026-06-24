/*
There are n balloons and n bullets and each balloon is assigned with a particular number (point).
Whenever a particular balloon is shot the no of points increases by
1.the multiplication of point assigned to balloon on left and that of right side.
2.point assigned to left if no right exists
3.point assigned to right if no left exists.
4.the point assigned to itself if no other balloon exists.
 
You have to output the maximum no of points possible.
 
Input-1
1 2 3 4
 
Output-1
20

Input-2
1 0 2 3 0 4

Output-2
34
*/

#include <bits/stdc++.h>
using namespace std;

int maxCoins(vector<int>& nums) {
    int n = nums.size();
        vector<int> arr(n+2);
        arr[0] = 1, arr[n+1] = 1;
        for(int i=0; i<n; i++){
            arr[i+1] = nums[i];
        }
        // vector<vector<int>> dp(n+2, vector<int>(n+2, -1));
        // return get(arr, 1, n, dp);
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        for(int i=n; i>=1; i--){
            for(int j=i; j<=n; j++){
                int maxi = 0;
                for(int ind=i; ind<=j; ind++){
                    int cost = arr[i-1]*arr[ind]*arr[j+1] + dp[i][ind-1] + dp[ind+1][j];
                    maxi = max(maxi, cost);
                }
                dp[i][j] = maxi;
            }
        }

        return dp[1][n];
}

int main(){
    vector<int> v;
    int x;
    while(cin>>x) v.push_back(x);

    cout << maxCoins(v);
}


#include <bits/stdc++.h>
using namespace std;

vector<int> a;
int dp[505][505];

int solve(int i, int j){
    if(i+1 == j) return 0;  // no balloon between

    if(dp[i][j] != -1) return dp[i][j];

    int res = 0;
    for(int k = i+1; k < j; k++){
        dp[i][j] = res = max(res, solve(i, k) + solve(k, j) + a[i] * a[k] * a[j] );
    }

    return dp[i][j] = res;
}

int main(){
    vector<int> nums;
    int x;
    while(cin >> x) nums.push_back(x);

    int n = nums.size();
    a.assign(n+2, 1);
    for(int i=0;i<n;i++) a[i+1] = nums[i];

    memset(dp, -1, sizeof(dp));

    cout << solve(0, n+1);
}
