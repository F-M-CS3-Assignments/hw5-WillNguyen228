#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // for std::find_if
#include <climits>
#include "Graph.h"
#include "BetterPriorityQueue.h"

using namespace std;

// Check if the queue contains a BPQNode with the same gnode
bool BetterPriorityQueue::Contains(const BPQNode& n) const {
    for (const auto& element : c) { // loops through every element in the queue
        if (element == n) {
            return true;
        }
    }
    return false;
}

// This function takes a BPQNode named n, and tries to update the priority of a matching BPQNode 
bool BetterPriorityQueue::Update(const BPQNode& n) {
    if (n.gnode == 0) return false; //check if the node is empty

    for (unsigned int i = 0; i < c.size(); ++i) { // loop through the priority queue
        if (c[i].gnode == n.gnode) { // if we find a node in the queue that has the same gnode then we check if its priority should be updated
            if (n.pri < c[i].pri) { // update the priority only if the new one is smaller
                c[i].pri = n.pri; // this actually updates the priority of the node in the queue
                push_heap(c.begin(), c.end(), comp); //rebuild the heap so the priority queue stays valid
                return true;
            } else {
                return false; // same node found, but no need to update
            }
        }
    }
    return false; // not found so no need to update
}

// String representation of the queue
string BetterPriorityQueue::ToString() const {
    string result = "[";
    for (size_t i = 0; i < c.size(); ++i) { // loop through the priority queue
        result += BPQNodeToString(c[i]); //convert each node to a string using the BPQNodeToString() underneath
        if (i != c.size() - 1) result += ", "; //add a comma between items but not after the last one
    }
    result += "]";
    return result;
}

// Converts a BPQNode to string like "(id, pri: value)"
string BetterPriorityQueue::BPQNodeToString(const BPQNode& n) {
    return "(" + to_string(n.gnode) + ", pri: " + to_string(n.pri) + ")";
}

// Access the top node with the smallest priority element without removing it
BPQNode BetterPriorityQueue::Top() const {
    if (!c.empty()) {
        return c.front(); // In a min-heap, the smallest element is at the front
    }
    return BPQNode(); // Return default node if empty
}

// Remove the top node with the smallest priority
void BetterPriorityQueue::Pop() {
    if (!c.empty()) {
        pop_heap(c.begin(), c.end(), comp); // Move smallest to the end
        c.pop_back(); // Remove it
    }
}
