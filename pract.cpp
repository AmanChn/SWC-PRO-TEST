#include<bits/stdc++.h>
using namespace std;


int dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

bool checkBoundary(int r, int c, int n, int m){
    return r>=0 && c>=0 && r<n && c<m;
}

void DFStraversal(vector<int> adj[], vector<int> vis, vector<int> dfsstore, int node){
    
}


void DFS(vector<int> adj[], vector<int> vis, vector<int> dfsstore, int n, int node){
    
    for( int i=0; i<n; i++ ){
        if( !vis[i] ){
            DFStraversal(adj,vis,dfsstore,node);
        }
    }
}

vector<int> bellmanford(vector<pair<int,int>> adj[], int v){
    vector<int> dist(v,INT_MAX);
    dist[0] = 0;

    for( int i=0; i<v; i++ ){
        for( int j=0; j<v; j++ ){
            for( auto e : adj[j] ){
                int u = j;
                int v = e.first;
                int w = e.second;

                if( dist[u] + w < dist[v] ){
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    return dist;
}

int kruskal(vector<pair<int,int>> adj[],int v){
    vector<vector<int>> edges;

    for( int i=0; i<v; i++ ){
        for( auto i : adj[i] ){
            int u = i;
            int nbr = i.first;
            int w = i.second;

            edges.push_back({w,u,v});
        }
    }

    disjointset ds(v);

    sort(edges.begin(),edges.end());

    int mstsum = 0;

    for( auto i : edges ){
        if( ds.findUltparent(i[1]) != ds.findUltParent(i[2]) ){
            ds.UnionByRank(i[1],i[2]);
            mstsum += i[0];
        }
    }

    return mstsum;

}

int prims(vector<pair<int,int>> adj[],int v){
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<bool> vis(v,false);
    int mstsum = 0;
    pq.push({0,0});


    while( !pq.empty() ){
        int w = pq.top().first;
        int node = pq.top().second;

        if( vis[node] ) continue;

        vis[node] = 1;
        mstsum += w;

        for( auto nd : adj[node] ){
            int nbr = nd.first;
            int d = nd.second;

            if( !vis[nbr] ){
                pq.push({d,nbr});
            }
        }

    }
    return mstsum;
}

int main(){

    int V = 5;

    // Edge list representation: {source, destination, weight}
    vector<vector<int>> edges = {
        {1, 3, 2}, 
        {4, 3, -1},
        {2, 4, 1}, 
        {1, 2, 1},
        {0, 1, 5} 
    };

    vector<pair<int,int>> adj[V];

    for( auto i : edges ){
        adj[i[0]].push_back({i[1],i[2]});
        // adj[i[1]].push_back({i[0],i[2]});
    }

    // Define the source vertex
    int src = 0;

    vector<int> ans = bellmanford(adj,V);

    // Output the shortest distances from src to all vertices
    for (int dist : ans) 
        cout << dist << " ";

    
    return 0;
}