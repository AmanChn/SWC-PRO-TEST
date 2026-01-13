/*
Q.There is a large plot with various sinkholes present. 
	Since one sinkhole can combine with another sinkhole, it is required to get
	at most one sinkhole while occupying the plot. You have to find the maximum 
	square-area formed with at most one sinkhole present.
	If there are two plots with the same area then print the one with 
	lesser sinkhole present otherwise if the sinkholes are also same then print
	anyone. For each case, you have to print the bottom leftmost coordinate and 
	top rightmost point. Please keep in mind that the plot starts with (1, 1).

	Time limit= 1sec and Memory limit– 256Mb

	Input: First line will give the number of test cases. For each test case, we
	will be given the size of the plot matrix N x M (where 1<=N, M<=1000). Next
	line will give the number of sinkholes present in the matrix K (1<=K<=N+M). 
	Next, K-lines will give the coordinates of the sinkholes.

	Output: For each test case, you have to print the number of the test case
	and the coordinates of the resultant square.
	i.e. #i xb yb xt yt (ith test case, xb=bottomost left x-coordinate, 
	yb=bottomost  left y-coordinate, xt= topmost right x-coordinate,
	yt= topmost right y-coordinate)
	
  *	time complexity of my approach = O(n*m*log(min(m,n))) *
*/


#include <bits/stdc++.h>
using namespace std;

int getSum(vector<vector<int>>& ps, int x1,int y1,int x2,int y2){
    return ps[x2][y2] - ps[x1-1][y2] - ps[x2][y1-1] + ps[x1-1][y1-1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin>>T;
    for(int tc=1;tc<=T;tc++){
        int N,M; cin>>N>>M;
        vector<vector<int>> grid(N+1, vector<int>(M+1,0));

        int K; cin>>K;
        for(int i=0;i<K;i++){
            int x,y; cin>>x>>y;
            grid[x][y] = 1;
        }

        vector<vector<int>> ps(N+1, vector<int>(M+1,0));
        for(int i=1;i<=N;i++)
            for(int j=1;j<=M;j++)
                ps[i][j] = grid[i][j] + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];

        int lo=1, hi=min(N,M), best=0, bx=1,by=1;

        while(lo<=hi){
            int mid=(lo+hi)/2;
            bool found=false;
            int tx=1,ty=1;

            for(int i=1;i+mid-1<=N && !found;i++){
                for(int j=1;j+mid-1<=M;j++){
                    int cnt = getSum(ps,i,j,i+mid-1,j+mid-1);
                    if(cnt<=1){
                        tx=i; ty=j;
                        found=true;
                        break;
                    }
                }
            }

            if(found){
                best=mid;
                bx=tx; by=ty;
                lo=mid+1;
            }else hi=mid-1;
        }

        cout<<"#"<<tc<<" "<<bx<<" "<<by<<" "<<bx+best-1<<" "<<by+best-1<<"\n";
    }
}
