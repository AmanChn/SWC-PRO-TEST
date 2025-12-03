#include<bits/stdc++.h>
using namespace std;

int MaximizeMinWt(unordered_map<int,vector<pair<int,int>>> &adj,int src, int dest, int n){
    vector<int> cap(n,0);
    cap[src] = INT_MAX;

    priority_queue<pair<int,int>> pq;
    pq.push({cap[src],src});

    while( !pq.empty() ){
        int wt = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if( node == dest ) return wt;

        if (wt < cap[node]) continue;

        for( auto nbr : adj[node]){
            int edWt = nbr.second;
            int nd = nbr.first;
            int mini = min(wt,edWt);

            if( mini > cap[nd] ){
                cap[nd] = mini;
                pq.push({mini,nd});
            }
        }
    }

    return -1;
}

int main(){
    unordered_map<int,vector<pair<int,int>>> adj;
    adj[0].push_back({1,5});
    adj[1].push_back({2,3});
    adj[0].push_back({3,4});
    adj[3].push_back({2,6});
    adj[2].push_back({4,2});

    int src = 0, dest = 4;
    cout<<MaximizeMinWt(adj,src,dest,4);

    return 0;
}