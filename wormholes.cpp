// There is a source (S) and destination (D) and a spacecraft has to go from S to D. There are N number of wormholes in between which has following properties:
// Each wormhole has an entry and an exit. Each wormhole is bi-directional i.e. one can enter and exit from any of the ends. The time to cross the wormhole is given and the space craft may or may not use the wormhole to reach D. The cost to travel outside wormhole between two points (x1, y1) and (x2, y2) is given by a formula |x1 - x2| + |y1 - y2|
// where, (x1, y1) and (x2, y2) are the co-ordinates of two points. The co-ordinates of S and D are given and we have to find the minimum cost to reach D from S. The main problem here is to minimum cost to reach spaceship from source to destination co-ordinate using any number of warm-hole. It is ok if you wont use any warmhole.

// Note: It’s not mandatory to consider all the wormholes

// Input Format
// First line contains t, number of test cases
// There are N number of warmholes each warmhole has 5 values. First 2 values are starting co-ordinate of warmhole and after that value no. 3 and 4 represents ending co-ordinate of warmhole and last 5th value is represents cost to pass through this warmhole.
// Line 1 contains value of N. Line 2 Conatins Source and Destination coordinate. Next N lines contain the warmhole information.

// Constraints
// 1 < t < 10 1 < N < 6 -1 < x < 101 -1 < y < 101 0 < cost < 101

// Output Format
// Output a single integer (minimum cost)

// Sample Input 0
// 1
// 3
// 0 0 100 100
// 1 2 120 120 16
// 2 5 120 100 21
// 6 8 150 180 16

// Sample Output 0
// 48

#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int x, y;

    Node(int a, int b){
        this->x = a;
        this->y = b;
    }
};

int manhattan_dist(Node* a, Node* b){
    return abs(a->x - b->x) + abs(a->y-b->y);
}

void printall(vector<Node*> points,vector<pair<int,int>> wormholeIdx,vector<int> wormholeCost, vector<vector<int>> dist){
        cout<<"printing points:"<<endl;
        for( auto i: points ){
            cout<<i->x<<" "<<i->y;
            cout<<endl;
        }
        cout<<endl;
        cout<<"printing wormhole cost:"<<endl;
        for( auto i: wormholeCost ){
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<"printing wormhole idx:"<<endl;
        for( auto i: wormholeIdx ){
            cout<<i.first<<" "<<i.second;
        }
        cout<<endl;
        cout<<"printing dist:"<<endl;
        for( auto i: dist ){
            for( auto j : i ){
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
}

int main(){
    int test_cases;
    cin>>test_cases;

    for(int t=0; t<test_cases; t++){
        int N;
        cin>>N;

        int sx,sy,dx,dy;
        cin>>sx>>sy>>dx>>dy;

        Node* source = new Node(sx,sy);
        Node* dest = new Node(dx,dy);

        vector<Node*> points;
        points.push_back(source);

        vector<pair<int,int>> wormholeIdx; // indices of wormhole start and end
        vector<int> wormholeCost;

        for( int i=0; i<N; i++ ){
            int ox,oy,ex,ey,cost;
            cin>>ox>>oy>>ex>>ey>>cost;

            Node* open = new Node(ox,oy);
            Node* end = new Node(ex,ey);

            int idx1 = points.size();
            points.push_back(open);
            int idx2 = points.size();
            points.push_back(end);

            wormholeIdx.push_back({idx1,idx2});
            wormholeCost.push_back(cost);
        }

        points.push_back(dest);

        int destIdx = points.size()-1;

        int V = points.size();

        vector<vector<int>> dist(V,vector<int>(V,INT_MAX));

        //normal movement edges
        for( int i=0;i<V;i++ ){
            for( int j=0; j<V;j++ ){
                dist[i][j] = manhattan_dist(points[i], points[j]);
            }
        }
    
        //wormhole edges
        for( int i=0;i<N;i++ ){
            int u = wormholeIdx[i].first;
            int v = wormholeIdx[i].second;

            dist[u][v] = min(dist[u][v], wormholeCost[i]);
            dist[v][u] = min(dist[v][u], wormholeCost[i]);
        }

        printall(points,wormholeIdx,wormholeCost,dist);

        vector<int> d(V,INT_MAX);
        d[0] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0,0});

        while( !pq.empty() ){
            auto cost = pq.top().first;
            auto node = pq.top().second;
            pq.pop();

            if( cost > d[node] ) continue;

            for( int v=0; v<V; v++ ){
                if( d[v] > d[node] + dist[node][v] ){
                    d[v] = d[node] + dist[node][v];
                    pq.push({d[v],v});
                }
            }

        }

        cout<<d[destIdx];
    }
    
    return 0;
}