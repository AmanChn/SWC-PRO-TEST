/* 
https://gist.github.com/gunpreet34/d0e45eedd61dadbf42fe6540da98facf

Mr. Kim has to deliver refrigerators to N customers. From the office, he is going to visit all the customers and then return to his home. 
Each location of the office, his home, and the customers is given in the form of integer coordinates (x,y) (0≤x≤100, 0≤y≤100) . 
The distance between two arbitrary locations (x1, y1) and (x2, y2) is computed by |x1-x2| + |y1-y2|, where |x| denotes the absolute value 
of x; for instance, |3|=|-3|=3. The locations of the office, his home, and the customers are all distinct. You should plan an optimal way 
to visit all the N customers and return to his among all the possibilities.
You are given the locations of the office, Mr. Kim’s home, and the customers; the number of the customers is in the range of 5 to 10. 
Write a program that, starting at the office, finds a (the) shortest path visiting all the customers and returning to his home. 
Your program only have to report the distance of a (the) shortest path.

Constraints

5≤N≤10. Each location (x,y) is in a bounded grid, 0≤x≤100, 0≤y≤100, and x, y are integers.

Input

You are given 10 test cases. Each test case consists of two lines; the first line has N, the number of the customers, and the 
following line enumerates the locations of the office, Mr. Kim’s home, and the customers in sequence. Each location consists of 
the coordinates (x,y), which is reprensented by ‘x y’.

Output

Output the 10 answers in 10 lines. Each line outputs the distance of a (the) shortest path. Each line looks like ‘#x answer’ 
where x is the index of a test case. ‘#x’ and ‘answer’ are separated by a space.

I/O Example

Input (20 lines in total. In the first test case, the locations of the office and the home are (0, 0) and (100, 100) respectively, 
and the locations of the customers are (70, 40), (30, 10), (10, 5), (90, 70), (50, 20).)

5 ← Starting test case #1
0 0 100 100 70 40 30 10 10 5 90 70 50 20

6 ← Starting test case #2
88 81 85 80 19 22 31 15 27 29 30 10 20 26 5 14

10 ← Starting test case #3
39 9 97 61 35 93 62 64 96 39 36 36 9 59 59 96 61 7 64 43 43 58 1 36

Output (10 lines in total)

#1 200
#2 304
#3 366
*/

#include<bits/stdc++.h>
using namespace std;

struct nodes
{
    int x, y;
};

int manhattan_dist(nodes a, nodes b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int totalCost(vector<vector<int>> &dist, int mask, int pos, vector<vector<int>> &dp){
    int m = dist.size();

    // int allCustomerVisited = ((1<<m)-1)>>1; // check only for customers and office 
    int allCustomerVisited = (1<<(m-1)) - 1; // check only for customers and office (use any)

    if( mask == allCustomerVisited) return dist[pos][m-1];

    if( dp[mask][pos] != -1 ) return dp[mask][pos];

    int ans = INT_MAX;

    // we will not visit home and office while delivering the fridge
    // and we will only visit home at last. thats why i is 1 to m-1
    for( int i=1; i<m-1; i++ ){
        if( (mask & (1<<i)) == 0 ){
            ans = min(ans, dist[pos][i] + totalCost(dist,(mask | (1<<i)),i,dp));
        }
    }

    return dp[mask][pos] = ans;
}

int main(){
    int test_cases;
    cin>>test_cases;

    while( test_cases-- ){
        int n;
        cin>>n;

        nodes office,home;
        cin>>office.x>>office.y>>home.x>>home.y;

        vector<nodes> nd;

        nd.push_back(office);
        for( int i=0; i<n; i++ ){
            nodes customer;
            cin>>customer.x>>customer.y;
            nd.push_back(customer);
        }

        nd.push_back(home);
        int m = nd.size();
        vector<vector<int>> dist(m, vector<int>(m,0));

        for( int i=0; i<nd.size(); i++ ){
            for( int j=0; j<nd.size(); j++ ){
                if( i == j ) continue;
                dist[i][j] = manhattan_dist(nd[i], nd[j]);
            }
        }

        //TSP with bitmask DP
        int mask = 1; // mark office as visited.
        int pos = 0;
        vector<vector<int>> dp((1<<(m-1)), vector<int>(m,-1));
        // we will not visit home while delivering the fridge
        // and we will only visit home at last. thats why we only need the mask of ofc & n customers

        cout<< totalCost(dist,mask,pos,dp);

        // cout<<endl;
        // for( auto i : dp ){
        //     for( auto j : i){
        //         cout<<j<<" ";
        //     }
        //     cout<<endl;
        // }cout<<endl;
    }
    
    return 0;
}