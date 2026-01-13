#include<bits/stdc++.h>
using namespace std;

vector<long long> buildPrefix(vector<int>& arr) {
    int n = arr.size();
    vector<long long> pref(n+1, 0);

    for(int i = 0; i < n; i++) {
        pref[i+1] = pref[i] + arr[i];
    }
    return pref;
}

int kadane(vector<int> &arr){
    //maximum subarray sum
    int ans = INT_MIN;
    int sum = 0;

    for( int i=0;i<arr.size(); i++ ){
        sum += arr[i];

        ans = max(ans,sum);

        if( sum < 0 ) sum = 0;
    }

    return ans;
}

int maxSubarraySumCircular(vector<int>& nums) {
    int total = 0;
    int curMax = 0, maxSum = INT_MIN;
    int curMin = 0, minSum = INT_MAX;

    for(int x : nums) {
        curMax = max(x, curMax + x);
        maxSum = max(maxSum, curMax);

        curMin = min(x, curMin + x);
        minSum = min(minSum, curMin);

        total += x;
    }

    if(maxSum < 0) return maxSum;   // all numbers negative
    return max(maxSum, total - minSum);
}

int main(){

    vector<int> arr = {1,2,5,-1,-10,1,6};

    cout<<kadane(arr);

    return 0;
}
