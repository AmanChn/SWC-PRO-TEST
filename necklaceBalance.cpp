/*
Given n (1 to 100000)
And a string of size 2n

Where string is made of characters R and B showing the beads of a nacklace which are of two types red and blue respective.
The nacklace has a knot in the middle, between nth and n+1 th bead
You can't move a bead across that knot
You have to find the min number of beads to be removed to make count of blue and red beads same in the necklace
You can remove beads from both the end of the necklace

Ex:
2 RRRR, ans: 4
3 RRBRBR, ans: 2
3 RBBBBB, ans: 6
*/

#include<bits/stdc++.h>
using namespace std;

int solve(string necklace, int n){
    unordered_map<int,int> mp;
    mp[0] = -1;
    int balance = 0;
    int maxlen = 0;

    for( int i=0; i<necklace.size(); i++ ){
        if( necklace[i] == 'R'){
            balance--;
        }
        else{
            balance++;
        }

        if( mp.find(balance) != mp.end() ){
            if( i >=n && mp[balance] < n ){
                int len = i - mp[balance];
                maxlen = max(maxlen,len);
            }
        }
        else{
            mp[balance] = i;
        }
    }

    return necklace.size() - maxlen;
}

int main(){
    int n;
    cin>>n;

    string necklace;

    cin>>necklace;

    cout<<solve(necklace, n);

    return 0;
}