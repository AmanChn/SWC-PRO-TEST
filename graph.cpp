#include<bits/stdc++.h>
using namespace std;

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

void print_arr(vector<int> &arr){
    for( auto i: arr ){
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(){
    int n = 5, e =7; 
    vector<vector<int>> graph(5, vector<int>(5,0));

    graph = {
            {0,1,1,0,0},
            {1,0,0,1,1},
            {1,0,0,1,1},
            {0,1,1,0,1},
            {0,1,1,1,0},
    };

    vector<int> adj[n];
    
    for(int i=0;i<n;i++){
        for( int j=0;j<n;j++ ){
            if( graph[i][j] == 1 ){
                adj[i].push_back(j);
            }
        }
    }

    print_graph(adj,n);

    vector<int> vis_dfs(n,0);
    vector<int> vis_bfs(n,0);
    vector<int> dfsstore;
    vector<int> bfsstore;

    DFS(adj,vis_dfs,dfsstore,n,0);
    BFS(adj,vis_bfs,bfsstore,n,0);

    print_arr(dfsstore); 
    print_arr(bfsstore); 
    
    return 0;

}