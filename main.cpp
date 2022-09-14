#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adjList;

   public:
    Graph(int v) : V(v), adjList(v) {}

    void addEdge(int u, int v, int wt) {
        adjList[u].push_back({wt, v});  // directed graph from u to v with weight wt.
        // for undirected graph add:
        // adjList[v].push_back({wt, u});
    }

    void dijkstra() {  // O((V+E)*logV). 
        // Can be improved using Fibonacci Heap which gives O(E + logV * (deleteMin + decreaseKey)) = O((E+V)*logV) time complexity.
        vector<int> dist(V, INT_MAX);  // distance of each vertex from the source vertex 0.

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  // min heap based on first element of pair i.e., distance in this case
        pq.push({0, 0});                                                                     // {distance from source to current node , current node}
        dist[0] = 0;

        while (!pq.empty()) {
            auto curr = pq.top();  // get the nearest unvisited vertex from the source (extract-min) O(logV) time complexity for a MinHeap implementation of PriorityQueue class in Java and C++ STL respectively as they are implemented using Heaps internally which is a complete binary tree with height logV where V is number of vertices/nodes in graph or size of heap/priority queue respectively). See https://www.geeksforgeeks.org/implement-min-heap-using-stl/. For Fibonacci Heap it would be O(1) amortized time complexity.
            pq.pop();

            int u = curr.second;  // current vertex

            for (auto neighbour : adjList[u]) {  // iterate over all neighbours of the current vertex
                if (dist[neighbour.second] > dist[u] + neighbour.first) {  // relax the edge from u to v i.e., update distance of v only if it is greater than new possible shorter distance calculated by adding distance of u to weight of edge from u to v
                    dist[neighbour.second] = dist[u] + neighbour.first;    // update the shortest path for neighbor
                    pq.push({dist[neighbour.second], neighbour.second});   // add neighbor to min heap with updated shortest path value as key/priority in pair object added in priority queue which would be used while extracting-min next time and also used while relaxing edges adjacent to this node later on, so that we can get correct minimum value everytime we extract-min or decreaseKey operation respectively using MinHeap based PriorityQueue class implementation internally in C++ STL and Java respectively as they are implemented using Heaps internally which is a complete binary tree with height logV where V is number of vertices/nodes in graph or size of heap/priority queue respectively. See https://www.geeksforgeeks.org/implement-min-heap-using-stl/. For Fibonacci Heap it would be O(1) amortized time complexity for both extractMin and decreaseKey operations respectively as they are implemented using doubly linked list internally which is a linear data structure with constant time insert, delete and search operations on average case analysis.
                }
            }
        }

        // print shortest path distance to all other nodes from source node 0 stored in dist[] array
        cout << "Vertex   Distance from Source" << endl;
        for (int i = 0; i < V; ++i) {  // iterate over all vertices one by one starting from vertex 0 till V - 1 where V is total number of vertices in the graph. This loop will take O(V) time complexity as we have already calculated the distances to each vertex while relaxing edges adjacent to each vertex above so no need to calculate them again here explicitly just printing them out here which takes only constant amount of time per iteration hence overall O(V) time complexity.
            cout << i << "\t\t" << dist[i] << endl;
        }

    }
};

int main() {
    int V = 9;  // number of vertices/nodes in graph

    Graph g(V);

    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    cout << "Shortest distances from source node 0 to all other nodes in graph:" << endl;
    g.dijkstra();

    return 0;
}
