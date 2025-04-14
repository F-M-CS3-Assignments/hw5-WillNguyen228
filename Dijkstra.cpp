#include "Dijkstra.h"
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <limits>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    // Big-O Time Complexity:
    // The time complexity of Dijkstra's algorithm depends on the number of nodes and edges in the graph.
    // For this implementation, we use a priority queue (BetterPriorityQueue) which allows us to efficiently
    // extract the node with the smallest distance. The time complexity is as follows:
    // - Extracting a node from the priority queue: O(log N) where N is the number of nodes in the queue.
    // - For each edge, we perform a decrease-key operation, which takes O(log N) time.
    // Thus, the overall time complexity is O((V + E) * log V), where V is the number of vertices and E is the number of edges.

    // Initializing all distances to infinity and the starting node's distance to 0
    // int numNodes = g->GetNodes().size();  // get the total number of nodes in the graph
    unordered_map<nodekey_t, int> distances;
    unordered_map<nodekey_t, nodekey_t> previousNodes;

    for (auto node : g->GetNodes()) {
        distances[node] = numeric_limits<int>::max();
        previousNodes[node] = -1;
    }  // store the previous node in the shortest path for each node

    distances[start] = 0;  // since the istance from the start node to itself is 0

    // Initializing a priority queue and adding the start node
    BetterPriorityQueue pQueue;
    BPQNode startNode;
    startNode.gnode = start;
    startNode.pri = 0;
    pQueue.push(startNode);

    // Running the dijkstra algorithm
    while (!pQueue.empty()) {
        BPQNode currentNode = pQueue.Top();  // get the node with the smallest distance
        pQueue.Pop(); //removing that node

        // if we've reached the end node, stop the algorithm
        if (currentNode.gnode == end) {
            break;
        }

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
                distances[neighbor] = newDistance;
                previousNodes[neighbor] = currentNode.gnode;

                // Add the neighbor to the priority queue
                BPQNode neighborNode;
                neighborNode.gnode = neighbor;
                neighborNode.pri = newDistance;
                
                if (pQueue.Contains(neighborNode)) {
                    pQueue.Update(neighborNode);
                } else {
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