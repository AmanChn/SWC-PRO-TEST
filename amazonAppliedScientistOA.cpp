#include<bits/stdc++.h>
using namespace std;

// ✅ QUESTION 1 — “Maximum Final Value of Array”
// You are given an array of integers. You may perform the following operations any number of times:
// Allowed Operations
// Rearrange the elements in any order.
// Reduce any element to any number ≥ 1.
// Required Conditions
// After performing operations:
// The first element must be 1.
// For every i ≥ 1,
// arr[i]−arr[i−1]≤1
// (i.e., consecutive elements can differ by at most 1).
// Goal
// Determine the maximum possible value of the last element of the array after performing operations while keeping all constraints valid.
// Example
// Input:
// arr = [3, 1, 2, 4]
// Steps:
// Reduce 3 → 1 → new array = [1, 1, 2, 4]
// Rearrange → [1, 1, 2, 4]
// Maximum possible final form is [1, 3, 5, 7]
// → last element = 4
// Output
// 4

int MaxFinal(vector<int> &arr){
    sort( arr.begin(), arr.end() );

    if( arr[0] != 1) arr[0] = 1;

    int ans = 0;

    for (int x : arr) {
        if (x > ans) {              // can be reduced to ans + 1
            ans++;                  // place value ans+1 in our “beautiful” array
        }
        // if x <= ans, it can't increase the maximum; ignore for ans
    }

    return ans;
}


// ✅ QUESTION 2 — “Group Students by Skill Levels”
// Amazon Technical Academy wants to group students into classes based on their skill levels.
// You are given:
// An array levels[] where levels[i] is the skill level of the i-th student.
// An integer maxSpread representing the maximum allowed difference between the highest and lowest skill levels in a class.
// Rule for Forming a Class
// A valid class must satisfy:
// max(levels_in_class)−min(levels_in_class)≤maxSpread
// You may rearrange the students in any order.
// Goal
// Return the minimum number of classes needed to group all students.
// Example
// n = 5
// levels = [4, 7, 1, 3, 4] =>  1,3,4,4,7
// maxSpread = 3

// Optimal grouping:
// Class 1: [1, 3, 4] → spread = 4 - 1 = 3
// Class 2: [4, 7] → spread = 7 - 4 = 3
// Minimum number of classes = 2

int FindClasses(vector<int> &levels, int maxSpread){
    sort( levels.begin(), levels.end() );
    int classes = 0;
    int n = levels.size();
    int i=0;

    while( i < n ){
        int start = levels[i];
        classes++;
        i++;
        while( i < n && levels[i] - start <= maxSpread){
            i++;
        }
    }

    return classes;
}


// ✅ CODE QUESTION 3 

// Your team at Amazon is building a quiz-style application to help students prepare for certification exams.
// Each quiz includes multiple tests over different subjects, and there are a number of questions in each subject.
// A student must answer at least a required number of questions in each subject to pass that subject.
// You are given:
// answered[i] → number of questions already answered correctly for subject i
// needed[i] → number of questions needed to pass subject i
// q → the number of additional questions the student can still answer (any subject)
// A subject is passed if:
// answered[i] + extra_attempts >= needed[i]

// Your task:

// Return the maximum number of subjects that the student can pass using at most q extra answered questions.
// Function Description
// Complete the function:
// int findMaximumNumberOfSubjects(vector<int> answered,
//                                 vector<int> needed,
//                                 int q)
// Parameters:
// answered[i]: int array — number of questions already answered
// needed[i]: int array — required questions to pass
// q: int — extra questions allowed
// Constraints:
// 1 ≤ n ≤ 10^5
// 0 ≤ answered[i], needed[i] ≤ 10^9
// Output:
// Return the maximum number of subjects that can be passed.
// Example
// answered = [5, 0]
// needed   = [5, 5]
// q = 4
// Subject 1 already passed
// Subject 2 needs 5 more questions → we have 4, not enough
// → Result = 1

int findMaximumNumberOfSubjects(vector<int> answered, vector<int> needed, int q){
    int ans = 0;

    vector<int> more;

    for( int i=0; i<answered.size(); i++ ){
        if( answered[i] >= needed[i] ){
            more.push_back(0);
        }
        else{
            more.push_back(needed[i]-answered[i]);
        }
    }

    sort(more.begin(), more.end());

    for( auto i : more ){
        if( q >= i ){
            ans++;
            q -=i; 
        }
    }

    return ans;
}


// ✅ CODE QUESTION 4

// A supply chain manager at a warehouse wants to analyze inbound shipping intervals.
// She wants to merge overlapping time intervals to simplify reporting.
// You are given a list of intervals, where each interval is represented as:
// [start, end]
// Your task:

// Merge all overlapping intervals and return the merged list in sorted order.
// Function Description
// Complete the function:
// vector<vector<int>> findOverlappingIntervals(vector<vector<int>>& intervals)
// Parameters:
// intervals: 2D integer array — list of intervals
// Constraints:
// 1 ≤ n ≤ 10^5
// 1 ≤ intervals[i][0], intervals[i][1] ≤ 10^9
// Example
// Input:
// intervals = [[7,7], [3,6], [2,4], [1,2], [10,12], [9,10], [6,8]]
// Output:
// [[1,12]]
// Explanation:
// (1,2) → overlaps with (2,4) → overlaps with (3,6) → overlaps with (6,8) → overlaps with (7,9)
// That chain eventually overlaps with (9,10) and (10,12)
// So everything merges into [1,12].


vector<vector<int>> mergeInterval(vector<vector<int>> &intervals){
    vector<vector<int>> ans;
    sort( intervals.begin(), intervals.end() );
    ans.push_back(intervals[0]);

    int j=0;
    for( int i=1; i<intervals.size(); i++ ){
        if( intervals[i][0] <= ans[j][1] ){
            ans[j][1] = max(intervals[i][1], ans[j][1]);
        }
        else{
            ans.push_back(intervals[i]);
            j++;
        }
    }

    return ans;
} 


int main(){
    vector<int> arr = {4, 7, 1, 3, 4};

    cout<<MaxFinal(arr)<<endl;
    cout<<FindClasses(arr,3)<<endl;

    vector<vector<int>> intervals = {
        {7,9}, {3,6}, {2,4}, {1,2}, {10,12}, {9,10}, {6,8}
    };

    vector<vector<int>> ans = mergeInterval(intervals);

    for( auto i : ans ){
        for( auto j : i ){
            cout<<j<<" ";
        }
        cout<<endl;
    }

    vector<int> answered = {5,0};
    vector<int> needed = {5,5};
    int q = 5;

    cout<<findMaximumNumberOfSubjects(answered, needed, q)<<endl;


    return 0;
}