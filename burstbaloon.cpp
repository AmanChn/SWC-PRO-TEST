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
    vector<int> a(n+2, 1);

    for(int i=0;i<n;i++) a[i+1] = nums[i];

    int N = n + 2;
    vector<vector<int>> dp(N, vector<int>(N, 0));

    for(int len=2; len<N; len++){
        for(int i=0; i+len<N; i++){
            int j = i + len;
            for(int k = i+1; k < j; k++){
                dp[i][j] = max(dp[i][j],
                    dp[i][k] + dp[k][j] + a[i]*a[k]*a[j]);
            }
        }
    }
    return dp[0][N-1];
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
        res = max(res, solve(i, k) + solve(k, j) + a[i] * a[k] * a[j] );
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
