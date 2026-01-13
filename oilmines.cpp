/* not to do
There is an island surrounded by oil mines. You will be given n companies and m oil mines having values.
You have to distribute the mines to "n" companies in fair manner. Remember the companies can have oil 
mines adjacent to each other and not in between of each others.After distributing them compute the 
difference of oil mines from the company getting highest and company getting lowest. This number 
should be minimum.(then only the distribution can be termed as fair).

Input 
2 
2 4 
6 13 10 2 
2 4 
6 10 13 2

output 
5 
1
*/

// #include <bits/stdc++.h>
// using namespace std;
// const int INF = 1e9;

// int main(){
//     int T; cin>>T;
//     while(T--){
//         int n,m;
//         cin>>n>>m;
//         vector<int>a(m);
//         for(int i=0;i<m;i++) cin>>a[i];

//         int ans = INF;

//         for(int s=0; s<m; s++){
//             vector<int>b;
//             for(int i=0;i<m;i++)
//                 b.push_back(a[(s+i)%m]);

//             vector<int> cuts(m-1);
//             for(int i=0;i<n-1;i++) cuts[i]=1;
//             for(int i=n-1;i<m-1;i++) cuts[i]=0;

//             do{
//                 int last=0;
//                 int mn=INF,mx=0;
//                 for(int i=0;i<m-1;i++){
//                     if(cuts[i]){
//                         int sum=accumulate(b.begin()+last, b.begin()+i+1,0);
//                         mn=min(mn,sum);
//                         mx=max(mx,sum);
//                         last=i+1;
//                     }
//                 }
//                 int sum=accumulate(b.begin()+last,b.end(),0);
//                 mn=min(mn,sum);
//                 mx=max(mx,sum);

//                 ans=min(ans,mx-mn);
//             }while(prev_permutation(cuts.begin(),cuts.end()));
//         }
//         cout<<ans<<"\n";
//     }
// }


#include <bits/stdc++.h>
using namespace std;

int n, m;
int ans;

/*
 pos      -> current index in linear array
 cuts     -> number of cuts used so far
 currSum  -> current segment sum
 minSum   -> minimum segment sum so far
 maxSum   -> maximum segment sum so far
*/
void dfs(int pos, int cuts, int currSum,
         int minSum, int maxSum,
         const vector<int>& arr) {

    // End of array
    if (pos == m) {
        if (cuts == n - 1) {
            minSum = min(minSum, currSum);
            maxSum = max(maxSum, currSum);
            ans = min(ans, maxSum - minSum);
        }
        return;
    }

    // Option 1: continue current company
    dfs(pos + 1, cuts,
        currSum + arr[pos],
        minSum, maxSum, arr);

    // Option 2: cut after this mine (if allowed)
    if (cuts < n - 1) {
        dfs(pos + 1, cuts + 1,
            arr[pos],
            min(minSum, currSum),
            max(maxSum, currSum),
            arr);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m;
        vector<int> oil(m);
        for (int i = 0; i < m; i++) cin >> oil[i];

        ans = INT_MAX;

        // Fix starting point to handle circular nature
        for (int start = 0; start < m; start++) {
            vector<int> arr;
            for (int i = 0; i < m; i++)
                arr.push_back(oil[(start + i) % m]);

            dfs(1, 0, arr[0], INT_MAX, INT_MIN, arr);
        }

        cout << ans << '\n';
    }

    return 0;
}

m x 2^m