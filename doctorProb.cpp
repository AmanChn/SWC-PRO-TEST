/*
https://www.geeksforgeeks.org/samsung-interview-experience-set-39-campus-r-d-noida/
https://www.careercup.com/page?pid=samsung-interview-questions

A Doctor travels from a division to other division where divisions are connected like a graph(directed graph) and 
the edge weights are the probabilities of the doctor going from that division to other connected division but the 
doctor stays 10mins at each division now there will be given time and had to find the division in which he will be 
staying by that time and is determined by finding division which has high probability.

Input is number of test cases followed by the number of nodes, edges, time after which we need to find the division 
in which he will be there, the edges starting point, end point, probability.

Note: If he reaches a point where there are no further nodes then he leaves the lab after 10 mins and the traveling 
time is not considered and during that 10min at 10th min he will be in next division, so be careful

2
6 10 40
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5
6 10 10 
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5

6 0.774000  
3 0.700000
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    int testcases;
    cin>>testcases;

    while( testcases-- ){
        int n, m, T;
        cin >> n >> m >> T;
        
        vector<pair<int, double>> graph[n + 1];
        
        for (int i = 0; i < m; i++) {
            int u, v;
            double prob;
            cin >> u >> v >> prob;
            graph[u].push_back({v, prob});
        }

        // dp[time][node] = probability of being at node at time
        // Time goes in steps of 10 minutes
        int steps = T / 10;

        vector<vector<double>> dp(steps + 1, vector<double>(n + 1, 0.0));

        dp[0][1] = 1.0; // Initially at node 1 with probability 1.0

        for( int t=0; t<steps; t++ ){
            for( int u=1; u<=n; u++ ){

                if( dp[t][u] > 0 ){ // If no outgoing edges, doctor leaves (probability becomes 0)
                    if( graph[u].empty() ) continue;
                }

                for( auto nd : graph[u] ){
                    auto v = nd.first;
                    auto prob = nd.second;

                    // Distribute probability to neighbors
                    dp[t+1][v] += dp[t][u] * prob;
                }
            }
        }

        int maxNode = 1;
        double maxProb = 0.0;

        for( int i=1; i<=n; i++ ){
            if( dp[steps][i] > 0 ){
                maxProb = dp[steps][i];
                maxNode = i;
            }
        }

        cout << maxNode << " " << fixed << setprecision(6) << maxProb << endl;
    }

    return 0;
}