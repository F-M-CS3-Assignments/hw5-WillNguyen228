#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include "Graph.h" // for nodekey_t and INVALID_NODE_KEY

// This is used for the items in the BetterPriorityQueue
struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const BPQNode &other) const {
		return pri > other.pri;
	}
	
	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};

// Define priority queue that allows updates, membership checks, and string helper functions
class BetterPriorityQueue : public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>> {
public:
    bool Contains(const BPQNode& n) const;
    bool Update(const BPQNode& n);
    string ToString() const;
    static string BPQNodeToString(const BPQNode& n);
};

#endif 