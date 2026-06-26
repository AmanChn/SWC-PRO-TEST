/* You have a cylinder which is of height N, each height has a circular movable disk which 
has M no. of cells on each level and each cell can have either 'S' or '-' printed on the cell. 
the circular disk can be moved in both direction clockwise and anticlockwise at all heights N, 
find the minimum no. of turns that must be made in total such that one of the cell column in 
the entire cylinder has all 'S' on them in line */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if(!(cin >> N >> M)) return 0;
    vector<string> a(N);
    for(int i=0;i<N;i++) cin >> a[i];

    // running sum of distances for each column k
    vector<ll> sum(M, 0);

    for(int i=0;i<N;i++){
        vector<int> dist(M, INF);
        queue<int> q;
        // multi-source initialize
        for(int p=0;p<M;p++){
            if(a[i][p]=='S'){
                dist[p] = 0;
                q.push(p);
            }
        }
        if(q.empty()){
            cout << -1 << '\n';
            return 0;
        }

        // BFS on cycle
        while(!q.empty()){
            int u = q.front(); q.pop();
            int v1 = (u+1) % M;
            if(dist[v1] == INF){
                dist[v1] = dist[u] + 1;
                q.push(v1);
            }
            int v2 = (u-1+M) % M;
            if(dist[v2] == INF){
                dist[v2] = dist[u] + 1;
                q.push(v2);
            }
        }

        // accumulate distances for each column
        for(int k=0;k<M;k++) sum[k] += dist[k];
    }

    ll ans = LLONG_MAX;
    for(int k=0;k<M;k++) ans = min(ans, sum[k]);
    cout << ans << '\n';
    return 0;
}



// OR



#include <bits/stdc++.h>
using namespace std;

/*
--S-S
S--S-
-S---
--S--
-SS-S

*/
int main(){
    int n,m;
    cin>>n>>m;
    vector<string> grid;
    
    for( int i=0; i<m; i++ ){
        string temp = "";
        cin>>temp;
        
        grid.push_back(temp);
    }
    
    queue<pair<int,int>> q;
    vector<vector<int>> dist(n,vector<int>(m,INT_MAX));
    
    for( int i=0; i<grid.size(); i++ ){
        for( int j=0; j<grid[i].size(); j++ ){
            if( grid[i][j] == 'S' ){
                q.push({i,j});
                dist[i][j] = 0;
            }
        }
    }
    
    while( !q.empty() ){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        
        int nc1 = (c + 1)%m;
        
        if( nc1>=0 && nc1<m && dist[r][nc1] == INT_MAX ){
            dist[r][nc1] = dist[r][c] +1;
            q.push({r,nc1});
        }
        
        int nc2 = (c - 1 + m)%m;
        
        if( nc2>=0 && nc2<m && dist[r][nc2] == INT_MAX ){
            dist[r][nc2] = dist[r][c] +1;
            q.push({r,nc2});
        }
    }
    
    int ans=INT_MAX;
    

    for( int i=0; i<m; i++ ){
        int temp=0;
        for( int j=0;j<n;j++ ){
            temp += dist[j][i];
        }
        ans = min(ans,temp);
    }

    cout<<ans;
    
    
    return 0;
}
