/*
You have to place an electronic banner of a company as high as it can be, so that whole the city can view the banner 
standing on top of TWO PILLERS.
The height of two pillers are to be chosen from given array.. say [1, 2, 3, 4, 6]. We have to maximise the height
of the two pillars standing side by side, so that the pillars are of EQUAL HEIGHT and banner can be placed on top of it.
In the above array, (1, 2, 3, 4, 6) we can choose pillars like this, say two pillars as p1 and p2.
In case, there is no combination possible, print 0.

INPUT :
1
5
1 2 3 4 6
Output :
8
*/

#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& rods, int idx, int sum1, int sum2){
        if( idx == rods.size() ){
            if( sum1 == sum2 ) return sum1;
            return 0;
        }

        int op1 = solve(rods,idx+1,sum1,sum2); // skip
        int op2 = solve(rods,idx+1,sum1+rods[idx],sum2); // add to sum1
        int op3 = solve(rods,idx+1,sum1,sum2+rods[idx]); // add to sum2

        return max({op1,op2,op3});
}
    // Reducing one of the state in above solution , as N * M * M would lead to MLE/TLE  where M = sum(Array)

    // Lets store the difference of s1 and s2 in the state , so the difference would range from -M to M

    // Hence, number of states = N* ( 2 * M) , hence we reduced the time by M
   
    // Note: +5000 to make index positive because sum can be negative but index should be positive.
    static const int offset = 5000;
    int dp[21][2 * offset + 1];

    // returns the maximum subset sum s1 , such that there exist another mutually exclusive subset s2 with difference in their sums = diff   OR
    // The maximum total height contributed to the LEFT pillar from rods idx...n-1, assuming the current difference is diff.
    int solveMem(vector<int> &rods, int idx, int diff){
        if( idx == rods.size() ){
            if( diff == 0 ) //meaning this configuration is valid
                return 0;

            return INT_MIN;
        }

        if( dp[idx][diff + offset] != -1 ){
            return dp[idx][diff + offset];
        }

        int opt1 = solveMem(rods,idx+1,diff); //skip

        // diff = left - right
        // new diff=(left + rod) - right = diff + rod
        int opt2 = rods[idx] + solveMem(rods,idx+1,diff+rods[idx]); //add to left
        
        // new diff=left - (right + rod) = diff - rod
        int opt3 = solveMem(rods,idx+1,diff-rods[idx]); // add to right
        // NO rods[idx] +   Why?
        // Because the function is counting LEFT height only.
        // Rod placed on RIGHT shouldn't increase LEFT height.

        return dp[idx][diff + offset] = max({opt1,opt2,opt3});
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            // int idx=0, sum1=0, sum2=0;
            // return solve(rods,idx,sum1,sum2);
    
            //diff = height(left pillar) - height(right pillar)
            int idx=0, diff=0; 
            memset(dp , -1 , sizeof(dp));
    
            int ans = solveMem(rods,idx,diff);
    
            return ans<0 ? 0 : ans; 
        }
    }
    return 0;
}
