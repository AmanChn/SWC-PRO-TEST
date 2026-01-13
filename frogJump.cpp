/*
Given a 2 D matrix where 1 represent the places where the frog can jump and 0 represent the empty spaces,
the frog can move freely in horizontal direction (on 1’s only) without incurring any cost (jump). 
A vertical jump from a given point of the matrix to other point on the matrix can be taken (on 1’s only) 
with cost as the number of jumps taken.
Given a source and destination, the frog has to reach the destination minimizing the cost (jump).
*/

#include<bits/stdc++.h>
using namespace std;

int minJumpCost(vector<vector<int>> &grid, int sr,int sc, int dr, int dc){
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m,INT_MAX));
    dist[sr][sc] = 0;

    deque<pair<int,int>> dq;
    dq.push_back({sr,sc});

    while( !dq.empty() ){
        int r = dq.front().first;
        int c = dq.front().second;
        dq.pop_front();

        int curr_cost = dist[r][c];

        if( r == dr && c == dc) return curr_cost;

        //move left 0 cost
        for( int nc = c-1; nc>=0 && grid[r][nc] == 1; nc-- ){
            if( dist[r][nc] > dist[r][c] ){
                dist[r][nc] = dist[r][c];
                dq.push_front({r,nc});
            }
        }

        //move right 0 cost
        for( int nc = c+1; nc<m && grid[r][nc] == 1; nc++ ){
            if( dist[r][nc] > dist[r][c] ){
                dist[r][nc] = dist[r][c];
                dq.push_front({r,nc});
            }
        }

        //move vertically cost is diff in rows
        for( int nr=0; nr<n; nr++ ){
            if( nr != r && grid[nr][c] == 1){
                if( dist[nr][c] > dist[r][c] + abs(nr-r) ){
                    dist[nr][c] = dist[r][c] + abs(nr-r);
                    dq.push_back({nr,c});
                }
            }
        }
    }

    return dist[dr][dc] == INT_MAX? -1 : dist[dr][dc];
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> grid(n, vector<int>(m,0));

    for( int i=0; i<n; i++ ){
        for( int j=0; j<m; j++ ){
            cin>>grid[i][j];
        }
    }

    int sr,sc,dr,dc;
    cin>>sr>>sc>>dr>>dc;

    int result = minJumpCost(grid,sr,sc,dr,dc);

    if( result == -1 )
        cout<<"No Path Exist"<<endl;
    else
        cout<<result<<endl;
    
    return 0;
}