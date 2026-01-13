/*
You’ll be given a grid as below:
0 1 0 2 0
0 2 2 2 1
0 2 1 1 1
1 0 1 0 0
0 0 1 2 2
1 1 0 0 1
x x S x x
   In the grid above,
  1: This cell has a coin.
  2: This cell has an enemy.
  0: It contains nothing.
  The highlighted(yellow) zone is the control zone. S is a spaceship that we need to control so that we can get maximum coins.
  Now, S’s initial position will be at the center and we can only move it right or left by one cell or do not move.
  At each time, the non-highlighted part of the grid will move down by one unit.
  We can also use a bomb but only once. If we use that, all the enemies in the 5×5 region above the control zone will be killed.
  If we use a bomb at the very beginning, the grid will look like this:
    0 1 0 2 0
    0 0 0 0 1
    0 0 1 1 1
    1 0 1 0 0
    0 0 1 0 0
    1 1 0 0 1
    x x S x x
  As soon as, the spaceship encounters an enemy or the entire grid has come down, the game ends.
  For example,
  At the very first instance, if we want to collect a coin we should move left( coins=1). This is because when the grid comes down by 1 unit we have a coin on the second position and by moving left we can collect that coin. Next, we should move right to collect another coin( coins=2).
  After this, remain at the same position( coins=4).
  This is the current situation after collecting 4 coins.
    0 1 0 2 0 0 1 0 0 0
    0 2 2 2 1 -->after using 0 0 0 0 1
    x x S x x -->bomb x x S x x
   Now, we can use the bomb to get out of this situation. After this, we can collect at most 1 coin. So maximum coins=5.
*/

// #include<bits/stdc++.h>
// using namespace std;
// int ans =INT_MIN;

// void getMaxCoin(vector<vector<int>> &grid, int isRowSafe, bool bombUsed, int r, int c, int coins){
//     if( r<0 || c<0 || c>=5 ){
//         ans = max(ans,coins);
//         return;
//     }

//     //if cell is 1 or 0
//     if( grid[r][c] == 1 || grid[r][c] == 0){
//         int newcoins = coins;
//         if (grid[r][c] == 1) {
//             newcoins++;
//         }
//         if( bombUsed ){
//             isRowSafe--;
//         }

//         getMaxCoin(grid,isRowSafe,bombUsed,r-1,c-1,newcoins);
//         getMaxCoin(grid,isRowSafe,bombUsed,r-1,c,newcoins);
//         getMaxCoin(grid,isRowSafe,bombUsed,r-1,c+1,newcoins);
//     }
//     else{ // there is enemy ie grid[r][c] == 2;
//         if( bombUsed && isRowSafe <=0 ){
//             ans = max(ans,coins);
//             return;
//         }
//         else if( bombUsed && isRowSafe > 0 ){
//             isRowSafe--;
//             getMaxCoin(grid,isRowSafe,bombUsed,r-1,c-1,coins);
//             getMaxCoin(grid,isRowSafe,bombUsed,r-1,c,coins);
//             getMaxCoin(grid,isRowSafe,bombUsed,r-1,c+1,coins);
//         }
//         else{ // bomb is not used so use it
//             bombUsed = true;
//             isRowSafe = 4; // as the current and above 4 rows will be cleared of enemies
//             getMaxCoin(grid,isRowSafe,bombUsed,r-1,c-1,coins);
//             getMaxCoin(grid,isRowSafe,bombUsed,r-1,c,coins);
//             getMaxCoin(grid,isRowSafe,bombUsed,r-1,c+1,coins);

//         }
//     }
// }

// int main(){
//     int n;
//     cin>>n;
//     int m = 5;

//     vector<vector<int>> grid(n,vector<int> (m,0));

//     for( int i=0;i<n;i++ ){
//         for( int j=0; j<m; j++ ){
//             cin>>grid[i][j];
//         }
//     }

//     // int r = grid.size()-1, c = 2;
//     int r = grid.size()-1;
//     int isRowSafe = 0;

//     getMaxCoin(grid,isRowSafe,false,r,1,0);
//     getMaxCoin(grid,isRowSafe,false,r,2,0);
//     getMaxCoin(grid,isRowSafe,false,r,3,0);

//     cout<<ans;
// }


#include <bits/stdc++.h>
using namespace std;

int n;
int grid[105][5];
int dp[105][5][6];

int solve(){
    memset(dp, -1, sizeof(dp));

    dp[n][2][0] = 0;   // start at middle, no bomb used

    for(int r=n; r>0; r--){
        for(int c=0; c<5; c++){
            for(int t=0; t<=5; t++){
                if(dp[r][c][t] == -1) continue;

                for(int mv=-1; mv<=1; mv++){
                    int nc = c + mv;
                    if(nc < 0 || nc >= 5) continue;

                    int val = dp[r][c][t];
                    int cell = grid[r-1][nc];
                    int nt = max(0, t-1);

                    if(cell == 2 && t == 0){
                        // must use bomb now
                        nt = 5;
                    }
                    else{
                        if(cell == 1) val++;
                    }

                    dp[r-1][nc][nt] = max(dp[r-1][nc][nt], val);
                }
            }
        }
    }

    int ans = 0;
    for(int c=0;c<5;c++)
        for(int t=0;t<=5;t++)
            ans = max(ans, dp[0][c][t]);

    return ans;
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<5;j++)
            cin >> grid[i][j];

    cout << solve();
}
