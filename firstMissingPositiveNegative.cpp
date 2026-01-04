// given unsorted array with +ve, -ve and 0. find the first missing positive number.
// Expected TC: O(n) && SC: O(1)

#include<bits/stdc++.h>
using namespace std;

void printarr(vector<int> &arr){
    for( auto i : arr ){
        cout<<i<<" ";
    }
    cout<<endl;
}

int findFirstMissingPositive(vector<int> &arr){
    int n = arr.size();

    // The smallest missing positive number must lie in range: [1,𝑛+1]
    // We use the array itself to place numbers at their correct indices.
    // this loop rearranges the array so that every valid number goes to its correct index.
    // If number x exists in array and 1 ≤ x ≤ n, then it must be placed at index (x − 1).
    for( int i=0; i<n; i++ ){
        while( arr[i]>=1 && arr[i]<=n && arr[i] != arr[arr[i]-1]){
            swap(arr[i],arr[arr[i]-1]);
        }
    }

    printarr(arr);

    for( int i=0; i<n; i++ ){
        if( arr[i] != i+1 ){
            return i+1;
  
        }
    }

    return n+1;
}

int findFirstMissingNegative(vector<int> &arr){
    int n = arr.size();

    for( int i=0; i<n; i++ ){
        while( arr[i]<0 && abs(arr[i])<=n && arr[i] != arr[abs(arr[i])-1]){
            swap(arr[i],arr[abs(arr[i])-1]);
        }
    }

    printarr(arr);

    for( int i=0; i<n; i++ ){
        if( arr[i] != -1*(i+1) ){
            return -1*(i+1);
  
        }
    }

    return -1*(n+1);
}

int main(){
    // vector<int> arr = {-3,1,4,0,-2,3,-1};
    vector<int> arr = {-3,-4,-6,-5,-2,0,-1};
    
    cout<<findFirstMissingPositive(arr);
    cout<<endl;
    cout<<findFirstMissingNegative(arr);

    return 0;
}