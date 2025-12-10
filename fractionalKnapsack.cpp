#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b){
    double r1 = (double) a.first / (double) a.second;
    double r2 = (double) b.first / (double) b.second;

    return r1 > r2;
}

double fractionalKnapsack(vector<pair<int,int>> &arr, int W){
    int n = arr.size();
    sort(arr.begin(),arr.end(), cmp);
    
    double totalSum = 0.0;

    for( int i=0; i<n; i++ ){
        if( arr[i].second <= W ){
            totalSum += arr[i].first;
            W -= arr[i].second;
        }
        else{
            totalSum += ((double)arr[i].first/(double)arr[i].second)*(double)W;
            break;
        }
    }

    return totalSum;
}

int main(){
    vector<pair<int,int>> arr = {{100,20},{60,10},{120,30} }; // val:wt
    int W = 50;

    cout<<fractionalKnapsack(arr,W);

    return 0;
}