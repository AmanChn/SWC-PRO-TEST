#include<bits/stdc++.h>
using namespace std;

class disjointSet{
    vector<int> rank, parent, size;
    public:
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

vector<vector<int>> dir = { {-1,0}, {1,0}, {0,1}, {0,-1} };

bool checkBoundary(int r, int c, int n, int m){
    return r>=0 && c>=0 && r<n && c<m;
}

void print_graph(vector<int> adj[], int n){
    for( int i=0;i<n;i++ ){
        for( auto node : adj[i] ){
            cout<<node<<" ";
        }
        cout<<endl;
    }
}

void DFStraversal(vector<int> adj[], vector<int> &vis_dfs, vector<int> &dfsstore, int node){
        vis_dfs[node] = 1;
        dfsstore.push_back(node);

        for( auto i: adj[node] ){
            if(!vis_dfs[i]){
                DFStraversal(adj, vis_dfs, dfsstore,i);
            }
        }
}

void DFS(vector<int> adj[], vector<int> &vis_dfs, vector<int> &dfsstore, int n, int node){
    for( int i=0;i<n; i++ ){
        if( !vis_dfs[i] ){
            DFStraversal(adj,vis_dfs,dfsstore,i);
        }
    }
}

void BFS(vector<int> adj[], vector<int> &vis_bfs, vector<int> &bfsstore, int n, int node){
    queue<int> q;
    q.push(node);
    vis_bfs[node] = 1;

    while( !q.empty() ){
        int front_node = q.front();
        q.pop();
        bfsstore.push_back(front_node);

        for( auto i : adj[front_node] ){
            if( !vis_bfs[i]){
                q.push(i);
                vis_bfs[i] = 1;
            }
        }
    }
}

void multiSourceBFS(vector<vector<int>> &grid){
    vector<vector<int>> vis (grid.size(), vector<int>(grid[0].size(),0));

    queue<pair<int,int>> q;
    
    for( int i=0; i<grid.size(); i++ ){
        for( int j=0; j<grid[i].size(); j++ ){
            if( grid[i][j] == 1 ){
                q.push({i,j});
                vis[i][j] = 1;
            }
        }
    }
    
    while( !q.empty() ){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for( int i=0; i<4; i++ ){
            int nr = r + dir[i][0];
            int nc = c + dir[i][1];

            //condition and calc here
            if(  ){
                q.push({nr,nc});
                vis[nr][nc] = 1;
            }
        }
    }

}

void print_arr(vector<int> &arr){
    for( auto i: arr ){
        cout<<i<<" ";
    }
    cout<<endl;
}

vector<int> dijkstra(vector<pair<int,int>> adj[], int V, int S){
    vector<int> dist(V, INT_MAX);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({0,S}); //dis:node
    dist[S] = 0;

    while( !pq.empty() ){
        auto wt = pq.top().first;
        auto node = pq.top().second;
        pq.pop();
        for( auto nbr : adj[node] ){
            int w = nbr.second;
            int nd = nbr.first;
            if( wt + w  < dist[nd] ){
                dist[nd] = w + wt;
                pq.push({dist[nd],nd});
            }
        }
    }

    return dist;
}

vector<int> bellmanFord(vector<pair<int,int>> adjwt[],int V, int S){
    vector<int> dist(V,INT_MAX);
    dist[S] = 0;

    for( int i=0; i<V;i++ ){
        for( int j=0; j<V; j++ ){
            for( auto edge : adjwt[j] ){
                int u = j;
                int v = edge.first;
                int wt = edge.second;

                if( dist[u] + wt < dist[v] ){
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }

    return dist;
}

int kruskal(vector<pair<int,int>> adjwt[], int V){
    vector<vector<int>> edges;

    for( int i=0; i<V; i++ ){
        for( auto it : adjwt[i] ){
            int node = i;
            int nbr = it.first;
            int wt = it.second;

            edges.push_back({wt,node,nbr});
        }
    }

    disjointSet ds(V);

    sort( edges.begin(), edges.end() );
    int mstsum = 0;
    for( auto i : edges ){
        if(ds.findUltParent(i[1]) != ds.findUltParent(i[2]) ){
            ds.UnionByRank(i[1], i[2]);
            mstsum += i[0];
        }
    }
    return mstsum;
}

int main(){
    int n = 5, e=7; 
    vector<vector<int>> graph(5, vector<int>(3,0));

    graph = {
            {1, 3, 2}, 
            {4, 3, -1},
            {2, 4, 1}, 
            {1, 2, 1},
            {0, 1, 5} 
    };

    vector<int> adj[n];
    
    for(int i=0;i<n;i++){
        for( int j=0;j<n;j++ ){
            if( graph[i][j] == 1 ){
                adj[i].push_back(j);
            }
        }
    }

    // print_graph(adj,n);

    vector<int> vis_dfs(n,0);
    vector<int> vis_bfs(n,0);
    vector<int> dfsstore;
    vector<int> bfsstore;

    DFS(adj,vis_dfs,dfsstore,n,0);
    BFS(adj,vis_bfs,bfsstore,n,0);

    // print_arr(dfsstore); 
    // print_arr(bfsstore); 

    vector<pair<int,int>> adjwt[n]; // node : nbr,wt

    adjwt[0] = {{1,5},{2,7}};
    adjwt[1] = {{0,2},{3,4},{4,1}};
    adjwt[2] = {{0,4},{3,9},{4,8}};
    adjwt[3] = {{1,9},{2,3},{4,2}};
    adjwt[4] = {{1,1},{2,2},{3,3}};

    // vector<int> dis = dijkstra(adjwt,n,0);
    // vector<int> dis = bellmanFord(adjwt,n,0);

    // print_arr(dis);

    // int mstsum = kruskal(adjwt,n);
    // cout<<mstsum;
    
    return 0;
}