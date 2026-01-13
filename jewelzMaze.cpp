/*
There is a maze that has one entrance and one exit. Jewels are placed in passages of the maze. 
You want to pick up the jewels after getting into the maze through the entrance and before getting 
out of it through the exit. You want to get as many jewels as possible, but you don’t want to take 
the same passage you used once.

When locations of a maze and jewels are given, find out the greatest number of jewels you can get 
without taking the same passage twice, and the path taken in this case.

Input
There can be more than one test case in the input file. The first line has T, the number of test cases.
Then the totally T test cases are provided in the following lines (T ≤ 10 ).

In each test case, In the first line, the size of the maze N (1 ≤ N ≤ 10) is given. 
The maze is N×N square-shaped. From the second line through N lines, information of the maze is given.
“0” means a passage, “1” means a wall, and “2” means a location of a jewel. The entrance is located 
on the upper-most left passage and the exit is located on the lower-most right passage. 
There is no case where the path from the entrance to the exit doesn’t exist.

Output
From the first line through N lines, mark the path with 3 and output it. In N+1 line, output the 
greatest number of jewels that can be picked up. Each test case must be output separately as a empty.
*/

#include<bits/stdc++.h>
using namespace std;

int maxJewels;
int jewels;
vector<vector<int>> currPath;
vector<vector<int>> bestPath;
vector<vector<bool>> vis;

int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int n;
void dfs(vector<vector<int>> &maze, int r, int c, int jewels){
    if( r == n-1 && c == n-1){
        if( jewels > maxJewels ){
            maxJewels = jewels;
            bestPath = currPath;
        }
        return;
    }

    for( int d=0; d<4; d++ ){
        int nr = r + dir[d][0];
        int nc = c + dir[d][1];

        if( nr<0 || nr>=n || nc<0 || nc>=n ) continue;

        if( vis[nr][nc] == 1 || maze[nr][nc] == 1) continue;

        vis[nr][nc] = 1;
        currPath[nr][nc] = 3;

        int newJewels = jewels;
        if( maze[nr][nc] == 2 ){
            newJewels++;
        }

        dfs(maze,nr,nc,newJewels);

        //backtracking
        vis[nr][nc] = 0;
        currPath[nr][nc] = maze[nr][nc];
    }
}

int main(){
    cin>>n;

    vector<vector<int>> maze(n, vector<int>(n,0));

    for( int i=0; i<n; i++ ){
        for( int j=0; j<n; j++ ){
            cin>>maze[i][j];
        }
    }

    vis.resize(n, vector<bool>(n,0));
    currPath = maze;
    bestPath = maze;

    maxJewels = 0;
    jewels = 0;
    if( maze[0][0] == 2 ) jewels = 1;

    vis[0][0] = 1;
    currPath[0][0] = 3;

    dfs(maze,0,0,jewels);

    for( auto i : bestPath ){
        for( auto j : i ){
            cout<<j<<" ";
        }
        cout<<endl;
    }

    cout<<maxJewels;

    return 0;
}