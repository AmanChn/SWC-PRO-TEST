#include<bits/stdc++.h>
using namespace std;

int kadane(vector<int> &arr){
    //maximum subarray sum
    int ans = INT_MIN;
    int sum = 0;

    for( int i=0;i<arr.size(); i++ ){
        sum += arr[i];

        ans = max(ans,sum);

        if( sum < 0 ){
            sum = 0;
        }
    }

    return ans;
}

int main(){

    vector<int> arr = {1,2,5,-1,-10,1,6};

    cout<<kadane(arr);

    return 0;
}
