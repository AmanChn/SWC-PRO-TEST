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





















return 0;

}