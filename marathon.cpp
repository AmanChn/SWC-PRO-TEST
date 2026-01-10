/*
A person is running a marathon of distance D with limited energy H.
He can change his pace every 1 km. Every pace consumes some amount of energy.
Given 5 paces in increasing order of time, i.e. time taken to run 1 km and energy consumed in 1km.
You need to find the least amount of time required to complete the marathon within the given amount of energy.
Paces are given such that the combination always completes the marathon.

Input format:
The first line contains the number of test cases T.
Each test case is given as follows:
- The first line of each test case contains the 2 integers D and H (D is the distance and H is the energy)
- The next 5 lines are as follows:
    - There are 3 integers (M, S and E) where: M is the minutes and S is the seconds required to run 1 km
      and E is the energy consumed in 1 km.

Output Format:
Print the following:
# followed by test case number followed by minimum time in mutes followed by seconds
Eg: #1 153 20

Eg: D = 30, H = 130
5 Paces: (M min S sec E energy)
4 50 7
5 0 5
5 10 4
5 20 3
5 30 2

Output: #1 153 20
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    int test_cases;
    cin>>test_cases;

    while( test_cases-- ){
        int D, H;
        cin>>D>>H;

        int pace = 2;
        vector<pair<int,int>> paces(pace);

        for( int i=0; i<pace; i++ ){
            int M,S,E;
            cin>>M>>S>>E;

            paces[i] = {M*60+S,E};
        }

        vector<vector<int>> dp(D+1,vector<int> (H+1,INT_MAX));
        dp[0][0] = 0;

        for( int d=0; d<=D; d++ ){
            for( int h=0; h<=H; h++ ){
                if( dp[d][h] == INT_MAX ) continue;

                //try each pace
                for( int p=0; p<paces.size(); p++ ){
                    int newD = d + 1;
                    int newH = h + paces[p].second;

                    if( newD <= D && newH <= H ){
                        dp[newD][newH] = min(dp[newD][newH], dp[d][h] + paces[p].first);
                    }
                }
            }
        }

        // for( auto i : dp ){
        //     for( auto j : i ){
        //         cout<<j<<" ";
        //     }
        //     cout<<endl;
        // }

        //find min time for dist D
        int minTime = INT_MAX;
        for( int h=0; h<=H; h++ ){
            minTime = min(minTime, dp[D][h]);
        }

        cout << "#" << test_cases+1 << " " << minTime / 60 << " " << minTime % 60 << "\n";
    }

    return 0;
}
