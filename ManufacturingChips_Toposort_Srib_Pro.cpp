/* You're given a 2D matrix (N x N) where each cell contains: 0 = empty cell 1, 2, 3, 4 = colors 
(e.g., 1 = Grey, 2 = Blue, 3 = Red, 4 = Yellow) Each color represents a solid rectangle. 
These rectangles: Can overlap with others Were painted one after another Later rectangles appear on top of 
earlier ones You're given a target color, and your task is to determine the painting order of that color 
(eg. if it was painted second return 2) Additional Rule: If two rectangles do not overlap, their order is 
based on ascending color number (i.e., 1 before 2, etc.) If it's impossible to determine a valid order 
(due to invalid overlaps, or circular dependencies), return -1. */

#include <bits/stdc++.h>
using namespace std;

int solve( vector<vector<int>>&grid, int targetColor, int colors ){
    vector<int> minR(colors+1,0);
    vector<int> minC(colors+1,0);
    vector<int> maxR(colors+1,0);
    vector<int> maxC(colors+1,0);
    
    vector<int> present(colors+1,0);
    
    for( int i=0;i<grid.size(); i++ ){
        for( int j=0;j<grid.size(); j++ ){
            int col = grid[i][j];
            
            if( col==0 ) continue;
            
            present[col] = 1;
            
            minR[col] = min(minR[col],i);
            minC[col] = min(minR[col],j);
            maxR[col] = max(maxR[col],i);
            maxC[col] = max(maxC[col],j);
        }
    }
    
    vector<set<int>> adj(colors+1);
    vector<int> indegree(colors+1,0);
    
    // biold graph and indegree
    for( int col=1; col<=colors;col++){
        
        if( !present[col] ) continue;
        
        for(int r=minR[col]; r<=maxR[col]; r++){
            for( int c=minC[col]; c<=maxC[col]; c++ ){
                int other = grid[r][c];
                
                if( other !=0 && other != col ){
                    if( ad[col].insert(other).second ){
                        indegree[other]++;
                    }
                }
            }
        }
    }
    
    priority_queue<int, vector<int>, greater<int>> pq;
    
    int totalcolors = 0;
    
    for( int c=1; c<=colors; c++ ){
        if( present[c] ) totalcolors++;
        if( indegree[c] == 0 ){
            pq.push(c);
        }
    }
    
    vector<int> topo(colors+1,-1);
    int pos = 1;
    int processed = 0;
    
    while( !pq.empty() ){
        int curr = pq.top();
        pq.pop();
        
        topo[curr] = pos++;
        processed++;
        
        for( auto nbr : adj[curr] ){
            indegree[nbr]--;
            
            if( indegree[nbr] == 0 ){
                pq.push(nbr);
            }
        }
    }
    
    return processed != totalcolors ? -1 : order[targetColor];
    
}

int main()
{
    int t=0;
    cin>>t;
    
    while( t-- ){
        int r,c,colors;
        cin>>r>>c>>colors;
        
        vector<vector<int>> grid(r,vector<int>(c,0));
        
        for( int i=0; i<r; i++ ){
            for( int j=0; j<c; j++ ){
                int col;
                cin>>col;
                grid[i][j] = col;
            }
        }
        
        int targetColor;
        cin>>targetColor;
        
        
        cout<<solve(grid,targetColor,colors);
    }

    return 0;
}
