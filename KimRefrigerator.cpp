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

int totalCost(vector<vector<int>> &dist, int mask, int pos, vector<vector<int>> &dp, int n){
    int m = dist.size();

    // Target: All N customers are visited. (e.g., if N=3, target is (1<<3)-1 = 7, binary 111)
    int allCustomerVisited = (1 << n) - 1; 

    // Base case: if all customers are visited, return distance from current position to Home (m-1)
    if( mask == allCustomerVisited ) return dist[pos][m-1];

    // Memoization check
    if( dp[mask][pos] != -1 ) return dp[mask][pos];

    int ans = INT_MAX;

    // Loop through customers only (indices 1 to n)
    for( int i = 1; i <= n; i++ ){
        int customer_bit = i - 1; // Map customer index 1..n to bit index 0..(n-1)
        
        if( (mask & (1 << customer_bit)) == 0 ){
            int sub_problem = totalCost(dist, (mask | (1 << customer_bit)), i, dp, n);
            if (sub_problem != INT_MAX) { // Prevent integer overflow
                ans = min(ans, dist[pos][i] + sub_problem);
            }
        }
    }

    return dp[mask][pos] = ans;
}

int main(){
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;
    if (!(cin >> test_cases)) return 0;

    while( test_cases-- ){
        int n;
        cin >> n;

        nodes office, home;
        cin >> office.x >> office.y >> home.x >> home.y;

        vector<nodes> nd;
        nd.push_back(office); // index 0
        for( int i = 0; i < n; i++ ){
            nodes customer;
            cin >> customer.x >> customer.y;
            nd.push_back(customer); // indices 1 to n
        }
        nd.push_back(home); // index n+1

        int m = nd.size();
        vector<vector<int>> dist(m, vector<int>(m, 0));

        for( int i = 0; i < m; i++ ){
            for( int j = 0; j < m; j++ ){
                if( i == j ) continue;
                dist[i][j] = manhattan_dist(nd[i], nd[j]);
            }
        }

        // TSP with bitmask DP
        int mask = 0; // No customers visited yet at the start
        int pos = 0;  // Starting at the office (index 0)
        
        // DP size: 2^n possible customer masks, and m possible positions
        vector<vector<int>> dp(1 << n, vector<int>(m, -1));

        // Print result with a newline for handling multiple test cases correctly
        cout << totalCost(dist, mask, pos, dp, n) << "\n";
    }
    return 0;
}

/*What changed?mask initialized to 0: We don't track the office in the bitmask anymore. We only care if the N customers are visited.
customer_bit = i - 1: Maps your array positions 1 to n to bit entries 0 to n-1.
dp size reduced: Scaled down safely to 1 << n states instead of wasting space with 1 << (m-1).*/
