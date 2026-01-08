// You are given N stalls at different positions on a line and C cows.
// You must place the cows in the stalls such that the minimum distance between any two cows is maximized.

// 5 3
// 1 2 4 8 9

#include<bits/stdc++.h>
using namespace std;

bool checkCowsPlace(vector<int> &pos, int dis, int c){
    int last = pos[0], cnt=1;
    for( int i=1; i<pos.size(); i++ ){
        if( pos[i] - last >= dis){
            cnt++;
            last = pos[i];
        }
    }

    return cnt >= c;
}

int binarySearch(vector<int> pos, int s, int e, int c){
    int ans = 0;
    while( s <= e ){
        int mid = s + (e-s)/2;

        if( checkCowsPlace(pos,mid,c) ){
            ans = mid;
            s = mid+1;
        }
        else{
            e = mid-1;
        }
    }

    return ans;
}

int main(){
    int n,c;
    cin>>n>>c;

    vector<int> pos(n,0);

    for( int i=0; i<n; i++ ){
        cin>>pos[i];
    }

    sort(pos.begin(),pos.end());

    // our search space will be 1 to (last stall pos - first stall pos)
    // ie we can place cows at a dist of 1 or at in case there is only 2 cows then diff will be
    // last stall - first stall
    int s=1, e = pos.back() - pos.front();

    cout<<binarySearch(pos,s,e,c);

    return 0;
}