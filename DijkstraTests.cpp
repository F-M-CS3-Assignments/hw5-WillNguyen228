#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;

int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	g->AddNode(4);
	g->AddNode(5);
	g->AddNode(6);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);
	g->AddEdge(1, 6, 14);
	g->AddEdge(6, 1, 14);
	
	g->AddEdge(2, 3, 10);
	g->AddEdge(3, 2, 10);
	g->AddEdge(2, 4, 15);
	g->AddEdge(4, 2, 15);
	
	g->AddEdge(3, 6, 2);
	g->AddEdge(6, 3, 2);
	g->AddEdge(3, 4, 11);
	g->AddEdge(4, 3, 11);
	
	g->AddEdge(6, 5, 9);
	g->AddEdge(5, 6, 9);
	
	g->AddEdge(4, 5, 6);
	g->AddEdge(5, 4, 6);
	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 5;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 20);

	delete g;
	
	cout << "DONE Testing Dijkstra Algorithm" << endl;
	
	return ans;
}


void MoreDijkstraTests(){
	cout << "Deep Testing Dijkstra Algorithm..." << endl;

	// Your code goes here!
	// Test 1: One node, start == end
	{
		Graph *g = new Graph();
		g->AddNode(1);
		assert(dijkstra(1, 1, g) == 0);
		delete g;
	}

	// Test 2: Two disconnected nodes
	{
		Graph *g = new Graph();
		g->AddNode(1);
		g->AddNode(2);
		assert(dijkstra(1, 2, g) == -1);  // no path
		delete g;
	}

	// Test 3: Two connected nodes
	{
		Graph *g = new Graph();
		g->AddNode(1);
		g->AddNode(2);
		g->AddEdge(1, 2, 5);
		assert(dijkstra(1, 2, g) == 5);
		delete g;
	}

	// Test 4: Multiple paths, Dijkstra should pick the shortest
	{
		Graph *g = new Graph();
		for (int i = 1; i <= 4; i++) g->AddNode(i);
		g->AddEdge(1, 2, 1);
		g->AddEdge(2, 4, 10);
		g->AddEdge(1, 3, 2);
		g->AddEdge(3, 4, 3);
		assert(dijkstra(1, 4, g) == 5);  // 1->3->4 is shorter than 1->2->4
		delete g;
	}

	// Test 5: Cycle in the graph
	{
		Graph *g = new Graph();
		for (int i = 1; i <= 3; i++) g->AddNode(i);
		g->AddEdge(1, 2, 4);
		g->AddEdge(2, 3, 6);
		g->AddEdge(3, 1, 2);  // Cycle
		assert(dijkstra(1, 3, g) == 10);  // 1->2->3
		delete g;
	}

	// Test 6: Slightly larger graph (6 nodes, like a ring)
	{
		Graph *g = new Graph();
		for (int i = 1; i <= 6; i++) g->AddNode(i);
		g->AddEdge(1, 2, 1);
		g->AddEdge(2, 3, 1);
		g->AddEdge(3, 4, 1);
		g->AddEdge(4, 5, 1);
		g->AddEdge(5, 6, 1);
		g->AddEdge(6, 1, 1);  // closing the ring
		assert(dijkstra(1, 4, g) == 3);  // shortest path: 1->2->3->4
		delete g;
	}

	cout << "DONE Deep Testing Dijkstra Algorithm" << endl;
}


int main(){
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	cout << endl;
	MoreDijkstraTests();
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
