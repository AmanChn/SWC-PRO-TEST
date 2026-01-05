// [Assuming each digit can be used only once]

// You are given old touch smartphone having dial pad and calculator app.
// Aim: The goal is to type a number on the dial pad.
// But as the phone is old, some of the numbers and some operations can’t be touched.
// For eg. 2,3,5,9 keys are not responding, i.e you cannot use them
// But you can always make a number using other numbers and operations in Calculator. There could be multiple ways of making a number
// Calculator have 1-9 and +,-,*,/,= as operations. Once you have made the number in Calculator you can copy the number and use it.
// You have to find the minimum number of touches required to obtain a number.
// Input:
// There will be multiple Test cases.Each test case will consist of 4 lines
// 1) The first line will consist of N, M, O
// N: no of keys working in Dialpad (out of 0,1,2,3,4,5,6,7,8,9)
// M:types of operations supported (+,-,*,/)
// O: Max no of touches allowed
// 2) second line of input contains the digits that are working e.g 0,2,3,4,6.
// 3) Third line contains the valued describing operations, 1(+),2(-),3(*),4(/)
// 4) fourth line contains the number that we want to make .
// Output:
// Output contains 1 line printing the number of touches required to make the number
// Sample Test Case:
// 1                   // No of test cases
// 5 3 5            // N ,M, O
// 1 2 4 6 0     // digits that are working (total number of digits = N),
// 1 2 3         // describing operations allowed (1–> ‘+’, 2–> ‘-‘, 3–> ‘*’ , 4–> ‘/’ )(total number is equals to M)
// 5                 // number we want to make
// Answer 4
// How 4? 1+4=, “=” is also counted as a touch
// 2nd Sample Case
// 3                   // No of Test cases
// 6 4 5            // N ,M, O
// 1 2 4 6 9 8  // digits that are working (total number of digits = N),
// 1 2 3 4        // describing operations allowed (1–> +, 2–> -, 3–> , 4–>/)
// 91                // number we want to make
// 6 3 5 // 2nd test case
// 0 1 3 5 7 9
// 1 2 4 // +, -, / allowed here
// 28
// 5 2 10
// 1 2 6 7 8
// 2 3               // -, allowed
// 981
// Output:
// 2        // 91 can be made by directly entering 91 as 1,9 digits are working, so only 2 operations
// 5            // 35-7=, other ways are 1+3*7=
// INTEGER_MAX_VALUE          //No ways
// */

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int findMinTouch(vector<int> digits,set<char> operators, int target, int N, int M, int O){
    map<pair<int,int>, int> dist; // {value,mask} : cost

    priority_queue<array<int,4>, vector<array<int,4>>, greater<>> pq; // cost:value:mask:usedOp
    pq.push({0,0,0,0});
    dist[{0,0}] = 0;

    int ans = INT_MAX;

    while( !pq.empty() ){
        auto node = pq.top(); pq.pop();
        int cost = node[0];
        int value = node[1];
        int mask = node[2];
        int usedOp = node[3];

        if( cost > O ) continue;

        if( dist[{value,mask}] < cost ) continue;

        if( value == target ){ 
            if( usedOp == 0 ) ans = min(ans,cost); // no operotor used
            else ans = min(ans,cost+1); // cost +1 for '=' press
        }

        for( auto d : digits ){
            if( mask & (1<<d) ) continue; // as one digit can be used only once

            int newmask = mask | (1<<d);

            // at any point we can do 3 things:
            // 1. append one more digit to the curretnt num
            // 2. use and operator
            // 3. use = to evaluate
            int v1 = value*10 + d;
            if( v1 <= 1000 ){ // applying limit so that the number of states do not explode
                if( !dist.count({v1,newmask}) || dist[{v1,newmask}] > cost+1){
                    dist[{v1,newmask}] = cost+1; // cost+1 for adding a new digit
                    pq.push({cost+1,v1,newmask,0});
                }
            }

            // now try to add operator to get a new state
            for( auto o : operators ){
                int v2;
                if( o == '+' ) v2 = value + d;
                if( o == '-' ) v2 = value - d;
                if( o == '*' ) v2 = value * d;
                if( o == '/' && d!=0 && (value%d) == 0) v2 = value/d;
                // checking for divide constratint & also divide only of completely divisible
                else if(o == '/') continue;

                if( abs(v2) <= 1000 ){
                    if( !dist.count({v2,newmask}) || dist[{v2,newmask}] > cost+2){
                        dist[{v2,newmask}] = cost+2; // cost+2 for adding a new digit & operator
                        pq.push({cost+2,v2,newmask,1});
                    }
                }
            }
        }
    }

    return ans>O ? INT_MAX : ans;
}


int main(){
    int test_cases;
    cin>>test_cases;

    while( test_cases-- ){
        int N,M,O;
        cin>>N>>M>>O;

        vector<int> digits;

        for( int i=0; i<N; i++ ){
            int d; cin>>d;
            digits.push_back(d);
        }

        set<char> operators;

        for( int i=0; i<M; i++ ){
            int op; cin>>op;
            if( op == 1 ) operators.insert('+');
            if( op == 2 ) operators.insert('-');
            if( op == 3 ) operators.insert('*');
            if( op == 4 ) operators.insert('/');
        }

        int target;
        cin>>target;

        cout<<findMinTouch(digits,operators,target,N,M,O);
    }

    return  0;
}