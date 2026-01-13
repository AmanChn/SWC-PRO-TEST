/*
Given:
Fishing Spots: 1 to N
3 Gates with gate position and number of fishermen waiting to get in
Distance between consecutive spots = distance between gate and nearest spot = 1 m
 
Fishermen are waiting at the gates to get in and occupy nearest fishing spot. Only 1 gate can be opened at a time and all fishermen of that gate must occupy spots before next gate is open.  
There could be 2 spots closest to the gate. Assign only 1 spot to the last fisherman in such a way that we get minimum walking distance. For rest of the fishermen, ignore and assign any one.
 
Write a program to return sum of minimum distance need to walk for fishermen.
 
Distance is calculated as gate to nearest spot + nearest spot to closest vacant spot.
If the gate is at position 4, then fishermen occupying spot 4 will walk 1 m,
*/

#include <iostream>
#define INT_MAX 999999
using namespace std;

int n,ans;
bool visited[100];

struct gate{
    int loc, men;
}gates[4];

int findLeft(int index){
    for(int i = index; i>0; i--){
        if(visited[i]==false)
            return i;
    }
    return INT_MAX;
}

int findRight(int index){
    for(int i = index+1; i<=n; i++){
        if(visited[i]==false)
            return i;
    }
    return INT_MAX;
}

void solve(int x,int y, int z, int distance, int cur_gate){
    //optimization condition, never forget
    if(distance > ans) return;

    //base case when all the mens at the current gate have occupied their places change gate
    if(gates[cur_gate].men==0){
        if(cur_gate==x) cur_gate=y;
        else if(cur_gate==y) cur_gate=z;
        // if every possible combination is seen just return the minimum distance
        else{
            ans=min(ans,distance);
            return ;
        }
    }

    //recursive case
    //searching for vacant spot at the left of current gate
    int l = findLeft(gates[cur_gate].loc);
    //searching for vacant spot at the right of current gate
    int r = findRight(gates[cur_gate].loc);

    //cost of occupying the left vacant spot
    int costL = abs(gates[cur_gate].loc - l) + 1;
    //cost of occupying the right vaacant spot
    int costR = abs(gates[cur_gate].loc - r) + 1;

    bool goRight=true, goLeft=true;
    if(costL > costR) goLeft = false;
    if(costR > costL) goRight = false;

    if(goLeft){
        visited[l]=true;
        gates[cur_gate].men--;
        solve(x,y,z,distance + costL, cur_gate);
        //backtracking
        visited[l]=false;
        gates[cur_gate].men++;
    } 

    if(goRight){
        visited[r]=true;
        gates[cur_gate].men--;
        solve(x,y,z,distance + costR, cur_gate);
        //backtracking
        visited[r]=false;
        gates[cur_gate].men++;
    }
}

int main() {
    int t;
    cin>>t;
    while(t--){
        cin>>n;

        //enter data for the positions and mens at the gate
        for(int i=1; i<=3; i++)
            cin>>gates[i].loc>>gates[i].men;

        for(int i=0; i<100; i++)
            visited[i]=false;
        
        ans=INT_MAX;
        //checking for all possible permutations of gate opening
        solve(1,2,3,0,1);
        solve(1,3,2,0,1);
        solve(2,1,3,0,2);
        solve(2,3,1,0,2);
        solve(3,1,2,0,3);
        solve(3,2,1,0,3);
        
        cout<<ans<<endl;
        
    }
    return 0;
}

 
/* TestCases
5
10
4 5
6 2
10 2
10
8 5
9 1
10 2
24
15 3
20 4
23 7
39
17 8
30 5
31 9
60
57 12
31 19
38 16
 
outputs
18
25
57
86
339
*/