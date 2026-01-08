// “Endoscopy camera / Laser endoscope movement problem”
// (sometimes also called Laser reflection in a mirror maze).
// You are given an N × M grid with:

// Cell	Meaning
// .	empty
// #	wall (blocks ray)
// /	mirror
// \	mirror
// S	start
// T	target

// A laser ray is fired from S in one of 4 directions.

// Rules:
// The ray moves straight until it hits a mirror or wall.
// Mirrors reflect direction.
// If it hits wall → stop.
// Find minimum reflections to reach T.

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dir = {{-1,0}, {0,1}, {1,0}, {0,-1}}; // U R D L

int reflect(int d, char m){
    if( m == '/' ){
        int mp[4] = {1,0,3,2};
        return mp[d];
    }
    else if ( m == '\\'){
        int mp[4] = {3,2,1,0};
        return mp[d];
    }
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<string> grid(n);
    for(int i=0;i<n;i++) cin >> grid[i];

    int sr,sc,tr,tc;
    cin>>sr>>sc>>tr>>tc;

    for( int i=0; i<n; i++ ){
        for( int j=0; j<m; j++ ){
            if( grid[i][j] == 'S' ){
                sr = i; sc = j;
            }
            if( grid[i][j] == 'T'){
                tr = i; tc = j;
            }
        }
    }

    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int> (4,INT_MAX)));
    deque<array<int,4>> dq;

    for( int d=0; d<4; d++ ){
        dist[sr][sc][d] = 0;
        dq.push_back({sr,sc,d,0}); //r,c,direction,cost;
    }

    while( !dq.empty() ){
        int r = dq.front()[0];
        int c = dq.front()[1];
        int dr = dq.front()[2];
        int cost = dq.front()[3];
        dq.pop_front();

        int nr = r + dir[dr][0];
        int nc = c + dir[dr][1];

        if( nr<0 || nr>=n || nc<0 || nc>=m || grid[nr][nc] == '#' ) continue;

        int nd = dr, ncost = cost;

        if( grid[nr][nc] == '/' || grid[nr][nc] == '\\' ){
            nd = reflect(dr,grid[nr][nc]);
            ncost++;
        }

        if( dist[nr][nc][nd] > ncost ){
            dist[nr][nc][nd] = ncost;
            // if cost is not changed i.e not reflected, push it to front as we will get min cost this way
            if( ncost == cost ) dq.push_front({nr,nr,nd,ncost});
            else dq.push_back({nr,nc,nd,ncost}); // if cost is changed ie reflected then push it to the back
        }
    }

    int ans = INT_MAX;

    for( int d=0; d<4; d++ ){
        ans = min(ans,dist[tr][tc][d]);
    }
    
    cout<<ans;

    return 0;
}