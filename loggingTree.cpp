// Logging Roadside Trees*
// ### *Problem Statement*
// The Korean Expressway Corporation is expanding a road and needs to chop down roadside trees using a logging robot. The goal is to *minimize the total time* taken.
// *The Robot's Features:*

// 1. *Movement:* The robot moves forward and backward. Moving 1 unit distance takes *1 minute*.
// 2. *Cutting:* Cutting and loading a tree takes *1 minute* per tree.
// 3. *Loading Constraint:* Trees must be loaded in *non-increasing order of length*. A tree can only be loaded if its length is shorter than or equal to the previously loaded tree. (The very first tree loaded can be of any length).
// 4. *Dual Side:* If there are trees on both the Left and Right sides at the current position, the robot can cut both without moving, provided the loading order condition is met.
// 5. *Capacity:* The robot can hold an infinite number of trees.

// *Road Layout:*

// - The road is a straight line from position 0 (Start) to N (End).
// - Trees may exist at positions 1 to N-1.
// - Positions 0 and N have no trees.
// - The length of trees varies; if no tree exists at a position, the length is 0.

// ### *Input Format*

// 1. Line 1: An integer N (Length of the road).
// 2. Line 2: N+1 integers representing tree lengths on the *Left* side (indices 0 to N).
// 3. Line 3: N+1 integers representing tree lengths on the *Right* side (indices 0 to N).

// ### *Output Format*
// Print the *shortest time (in minutes)* to cut all trees and reach the ending point N.

// ### *Example 1*
// Input:
// 5
// 0 3 2 1 0 0
// 0 3 2 1 0 0

// Output:
// 11

// ### *Example 2*
// Input:
// 7
// 0 5 1 5 9 1 5 0
// 0 0 0 0 0 0 0 0

// Output:
// 23

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N;
vector<int> leftTrees, rightTrees;
map<pair<int, pair<int,int>>, int> memo;

struct Tree {
    int len, pos, side; // side: 0=left, 1=right
};

vector<Tree> trees;

int solve(int mask, int lastPos, int lastLen) {
    int numTrees = trees.size();
    
    // All trees cut
    if (mask == (1 << numTrees) - 1) {
        return abs(N - lastPos);
    }
    
    auto key = make_pair(mask, make_pair(lastPos, lastLen));
    if (memo.count(key)) return memo[key];
    
    int result = INF;
    
    // Try cutting each remaining tree
    for (int i = 0; i < numTrees; i++) {
        if (mask & (1 << i)) continue; // Already cut
        
        // Check if we can cut this tree (length constraint)
        if (trees[i].len > lastLen) continue;
        
        int newMask = mask | (1 << i);
        int moveCost = abs(trees[i].pos - lastPos);
        
        // Option 1: Cut only this tree
        int cost = moveCost + 1 + solve(newMask, trees[i].pos, trees[i].len);
        result = min(result, cost);
        
        // Option 2: Check if we can cut another tree at the same position
        for (int j = 0; j < numTrees; j++) {
            if (i == j) continue;
            if (mask & (1 << j)) continue;
            if (trees[j].pos == trees[i].pos && trees[j].side != trees[i].side) {
                // Try cutting tree i first, then tree j
                if (trees[j].len <= trees[i].len) {
                    int newMask2 = newMask | (1 << j);
                    int cost2 = moveCost + 2 + solve(newMask2, trees[i].pos, trees[j].len);
                    result = min(result, cost2);
                }
            }
        }
    }
    
    memo[key] = result;
    return result;
}

int main() {
    cin >> N;
    
    leftTrees.resize(N + 1);
    rightTrees.resize(N + 1);
    
    for (int i = 0; i <= N; i++) cin >> leftTrees[i];
    for (int i = 0; i <= N; i++) cin >> rightTrees[i];
    
    // Collect all trees
    for (int i = 1; i < N; i++) {
        if (leftTrees[i] > 0) {
            trees.push_back({leftTrees[i], i, 0});
        }
        if (rightTrees[i] > 0) {
            trees.push_back({rightTrees[i], i, 1});
        }
    }
    
    cout << solve(0, 0, 10001) << endl;
    
    return 0;
}