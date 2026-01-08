// You are given a grid of size N × M.
// Each cell contains a pipe type (1–7) or 0 meaning no pipe.
// Each pipe type allows flow in specific directions.
// You start from position (R,C) and you have exactly L time units.
// In one time unit you can move to a connected cell only if the pipes are compatible.
// You must count how many distinct cells you can reach in at most L time.
// Pipe Types
// Type	Directions allowed
// 1	    up, down, left, right
// 2	    up, down
// 3	    left, right
// 4	    up, right
// 5	    right, down
// 6	    down, left
// 7	    up, left

// Connection Rule
// You can move from (r,c) to (nr,nc) only if:
// Current pipe allows that direction.
// Next pipe allows the opposite direction.
// Example:
// If you move right, next pipe must allow left.

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dir = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // U D L R

vector<vector<int>> pipe = {
    {}, // no pipe
    {0,1,2,3}, // UDLR
    {0,1}, // UD
    {2,3},
    {0,3},
    {3,1},
    {1,2},
    {0,2}
};

bool canGo(int from, int to, int dir){
    int opp = dir^1; // 0↔1 , 2↔3
    return find(pipe[to].begin(), pipe[to].end(), opp) != pipe[to].end();
}

int main(){
    int testcase;
    cin>>testcase;

    while( testcase-- ){
        int n,m,sr,sc,l;
        cin>>n>>m>>sr>>sc>>l;

        vector<vector<int>> grid(n,vector<int>(m,0));

        for( int i=0; i<n; i++ ){
            for(int j=0;j<m;j++){
                cin>>grid[i][j];
            }
        }

        vector<vector<bool>> vis(n, vector<bool>(m,false));
        queue<pair<int,int>> q;
        int time = 1;
        q.push({sr,sc}); // r,c (starting point)
        vis[sr][sc] = true;
        
        while( !q.empty() && time < l){
            int sz = q.size();

            while( sz-- ){
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                for( auto d : pipe[grid[r][c]] ){
                    int nr = r + dir[d][0];
                    int nc = c + dir[d][1];

                    if( nr<0 || nr>=n || nc<0 || nc>=m || vis[nr][nc] || grid[nr][nc] == 0 )
                        continue;

                    if( canGo(grid[r][c], grid[nr][nc], d) ){
                        vis[nr][nc] = true;
                        q.push({nr,nc});
                    }
                }
            }

            time++;
        }

        int ans = 0;
        for( auto i : vis ){
            for( auto j : i ){
                cout<<j<<" ";
                if( j ) ans++;
            }
            cout<<endl;
        }

        cout<<ans<<endl;
    }

    return 0;  
} 