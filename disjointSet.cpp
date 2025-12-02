#include<bits/stdc++.h>
using namespace std;

class disjointSet{
    public:
    vector<int> rank, parent, size;
    disjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){ parent[i] = i;}
    }

    int findUltParent(int node){
        if( node == parent[node] ) return node;
        return parent[node] = findUltParent(parent[node]);
    }

    void UnionByRank(int u, int v){
        int ultpar_u = findUltParent(u);
        int ultpar_v = findUltParent(v);

        if( rank[ultpar_u] < rank[ultpar_v] ){
            parent[ultpar_u] = ultpar_v;
        }
        else if( rank[ultpar_u] > rank[ultpar_v] ){
            parent[ultpar_v] = ultpar_u;
        }
        else{
            parent[ultpar_u] = ultpar_v;
            rank[ultpar_v]++;
        }
    }

    void UnionBySize(int u, int v){
        int ultp_u = findUltParent(u);
        int ultp_v = findUltParent(v);

        if( ultp_u == ultp_v ) return;

        if( size[ultp_u] < size[ultp_v] ){
            parent[ultp_u] = ultp_v;
            size[ultp_v] += size[ultp_u];
        }
        else{
            parent[ultp_v] = ultp_u;
            size[ultp_u] += size[ultp_v];
        }
    }
};

int main(){

    disjointSet ds(6);

    ds.UnionBySize(1,2);
    ds.UnionBySize(3,4);
    ds.UnionBySize(5,6);

    if( ds.findUltParent(3) == ds.findUltParent(1) ){
        cout<<"same component"<<endl;
    }
    else{
        cout<<"not same component"<<endl;
    }

    ds.UnionBySize(1,3);
    ds.UnionBySize(4,6);

    return 0;
}
