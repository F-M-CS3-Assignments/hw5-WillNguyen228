#include "Dijkstra.h"
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <limits>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// Big-O Time Complexity:
// The time complexity of Dijkstra's algorithm depends on the number of nodes and edges in the graph.
// We are using a priority queue which allows us to get the node with the smallest distance. 
// The time complexities are:
// The cost for each dequeue and enqueue operation is O(log V) 
// For each neighbor, we are checking if the path is shorter and update it if it is. 
// So in the worst case we check every edge. -> O(E * logV)
// In the worst case, we would have to insert and pop each node in the priority queue too 
// -> O (V * log V)
// In total, our time complexity is O(E * logV) + O(V * log V) = O((V+E) * log V)

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    // Initializing all distances to infinity and the starting node's distance to 0
    // int numNodes = g->GetNodes().size();  // get the total number of nodes in the graph
    unordered_map<nodekey_t, int> distances; // store  distance from start to each node
    unordered_map<nodekey_t, nodekey_t> previousNodes; // to be able to backtrack

    //Set all nodes with infinite distance except the start node
    for (auto node : g->GetNodes()) {
        distances[node] = numeric_limits<int>::max();
        previousNodes[node] = -1; // no predecessor yet
    }  

    distances[start] = 0;  // since the istance from the start node to itself is 0

    // Initializing a priority queue and adding the start node
    BetterPriorityQueue pQueue;
    BPQNode startNode;
    startNode.gnode = start;
    startNode.pri = 0;
    pQueue.push(startNode); 

    // Running the main loop
    while (!pQueue.empty()) {
        BPQNode currentNode = pQueue.Top();  // get the node with the smallest distance
        pQueue.Pop(); //removing that node

        // if we've reached the end node, stop the algorithm
        if (currentNode.gnode == end) {
            break;
        }

        // Get all neighboring nodes
        set<nodekey_t> neighbors;
        for (auto edge : g->GetOutwardEdgesFrom(currentNode.gnode)) {
            neighbors.insert(edge->to);
        }

        // For each neighbor of the current node, relax the edges
        for (auto neighbor : neighbors) {
            //We are getting the weight of the edge
            GraphEdge* edge = g->findExistingEdge(currentNode.gnode, neighbor);
            if (edge == nullptr) continue; // if no edge found, skip
            int weight = edge->weight; 

            int newDistance = distances[currentNode.gnode] + weight;
            // cout << distances[end] << endl;
            // If the new distance is shorter, update the distance and previous node
            if (newDistance < distances[neighbor]) {
                // Update the shortest known distance to this neighbor
                distances[neighbor] = newDistance;
                // Record the current node as the previous node in the shortest path to this neighbor
                previousNodes[neighbor] = currentNode.gnode;

                // Adding the neighbor to the priority queue
                BPQNode neighborNode;
                neighborNode.gnode = neighbor;
                neighborNode.pri = newDistance;
                
                // If the neighbor is already in the priority queue, update its priority
                if (pQueue.Contains(neighborNode)) {
                    pQueue.Update(neighborNode);
                } else {
                    // If not, just insert the neighbor into the priority queue
                    pQueue.push(neighborNode);
                }
            }
        }
    }

    // cout << "There might be an error coming" << endl;
    // Return the distance to the end node
    if (distances[end] == numeric_limits<int>::max()) { // if the node remains at infinity, no path has been found
        return -1;  // No path found
    } else {
        return distances[end];  // Return the shortest path distance
    }
}