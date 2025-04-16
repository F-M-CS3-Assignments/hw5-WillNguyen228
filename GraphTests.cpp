#include "Graph.h"
#include <iostream>
#include <cassert>

using namespace std;

void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();


	g.AddNode(15);
	//cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15)]");


	g.AddNode(12);
	//cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15), (12)]");

	
	try
	{
		g.AddNode(12);
		assert(false);
	}
	catch( const invalid_argument& e ) { }

	
	cout << "PASSED!" << endl << endl;
}


void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();

	g.AddNode(15);
	g.AddNode(12);
	g.AddNode(9);
	// cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15), (12), (9)]");

	
	const GraphEdge *ge1 = g.AddEdge(15, 9, 2);
	assert(g.NodesToString() == "[(15), (12), (9)]");
	//cout << "edges:" <<  g.EdgesToString() << endl;
	assert(g.EdgesToString() == "[((15)->(9) w:2)]");
	assert(ge1->from == 15);
	assert(ge1->to == 9);
	assert(ge1->weight == 2);
	
	const GraphEdge *ge2 = g.AddEdge(9, 12); // this makes the weight 0, since default value for weight is 0
	assert(g.NodesToString() == "[(15), (12), (9)]");
	//cout << "edges:" <<  g.EdgesToString() << endl;
	assert(g.EdgesToString() == "[((15)->(9) w:2), ((9)->(12) w:0)]");
	assert(ge2->from == 9);
	assert(ge2->to == 12);
	assert(ge2->weight == 0);
	
	try
	{
		const GraphEdge *ge3 = g.AddEdge(20, 12);
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}


	try
	{
		const GraphEdge *ge3 = g.AddEdge(15, 9, 7);
		// edge already exists!
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}


	// more tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestIsPresentSizeAndOrder() {
	cout << "Testing IsPresent, Size, and Order..." << endl;
	
	// more tests go here!

	Graph g2 = Graph();
	assert(g2.Size() == 0);
	assert(g2.Order() == 0);
	assert(g2.IsPresent(17) == false);


	cout << "PASSED!" << endl << endl;
}



void TestGetOutwardEdgesFrom(){
	cout << "Testing GetOutwardEdgesFrom..." << endl;
	Graph g = Graph();
	g.AddNode(17);
	g.AddNode(18);
	g.AddNode(22);
	g.AddNode(34);

	const GraphEdge* ge1 = g.AddEdge(17, 18, 3);
	g.AddEdge(22, 18); // weight will be 0 of course
	const GraphEdge* ge3 = g.AddEdge(17, 34, 8);
	g.AddEdge(22, 17, 6); // note, 22 is not a neighbor of 17, but 17 is a neighbor of 22
	
	set<const GraphEdge*> soln;
	soln.insert(ge3);
	soln.insert(ge1);
	
	set<const GraphEdge*> result = g.GetOutwardEdgesFrom(17);
	assert(result.size() == soln.size());
	assert(result == soln);


	// more tests go here!
	
	
	cout << "PASSED!" << endl << endl;
}


void TestGetNodes(){
	cout << "Testing GetNodes..." << endl;
		
	Graph g = Graph();
	g.AddNode(51);
	g.AddNode(24);
	g.AddNode(73);

	
	set<nodekey_t> nodes = g.GetNodes();
	set<nodekey_t> soln = {24, 73, 51};
	assert(nodes.size() == soln.size());
	assert(nodes == soln);


	g = Graph();
	nodes = g.GetNodes();
	soln.clear();
	assert(nodes.size() == soln.size());
	assert(nodes == soln);
		
	cout << "PASSED!" << endl << endl;
}




void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();

	g->AddNode(3);
	g->AddNode(5);
	g->AddEdge(3, 5, 15);
	delete g;
	
	
	Graph *g2 = new Graph();
	g2->AddNode(12);
	g2->AddNode(11);
	delete g2;


	Graph *g3 = new Graph();
	delete g3;
	
	
	Graph g4 = Graph(); // deconstructed automatically when this funciton ends
	
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}

void TestGraphWithCycles() {
    cout << "Testing Graph with Cycles..." << endl;
    Graph g = Graph();
    g.AddNode(1);
    g.AddNode(2);
    g.AddEdge(1, 2);
    g.AddEdge(2, 1); // back edge

    assert(g.EdgesToString() == "[((1)->(2) w:0), ((2)->(1) w:0)]");
    cout << "PASSED!" << endl << endl;
}

void TestSelfLoop() {
    cout << "Testing Self-loop..." << endl;
    Graph g = Graph();
    g.AddNode(10);
    const GraphEdge* selfEdge = g.AddEdge(10, 10, 7);
    assert(selfEdge->from == 10 && selfEdge->to == 10 && selfEdge->weight == 7);
    cout << "PASSED!" << endl << endl;
}

void TestEmptyGraph() {
    cout << "Testing Empty Graph..." << endl;
    Graph g = Graph();
    
    // Check that graph has no nodes or edges
    assert(g.NodesToString() == "[]");
    assert(g.EdgesToString() == "[]");
    
    cout << "PASSED!" << endl << endl;
}

void TestOneNodeGraph() {
    cout << "Testing One Node Graph..." << endl;
    Graph g = Graph();
    
    g.AddNode(1);
    
    // Check that there is one node and no edges
    assert(g.NodesToString() == "[(1)]");
    assert(g.EdgesToString() == "[]");
    
    cout << "PASSED!" << endl << endl;
}

void TestNoOutgoingEdges() {
    cout << "Testing No Outgoing Edges..." << endl;
    Graph g = Graph();
    
    g.AddNode(1);
    g.AddNode(2);
    
    // Node 1 has no outgoing edges, so the result should be an empty set
    set<const GraphEdge*> result = g.GetOutwardEdgesFrom(1);
    set<const GraphEdge*> soln;  // empty set
    
    assert(result.size() == soln.size());
    assert(result == soln);
    
    cout << "PASSED!" << endl << endl;
}

void TestFullyConnectedGraph() {
    cout << "Testing Fully Connected Graph..." << endl;
    Graph g = Graph();
    
    // Add nodes
    for (int i = 1; i <= 4; i++) {
        g.AddNode(i);
    }
    
    // Add edges between every pair of nodes
    g.AddEdge(1, 2, 1);
    g.AddEdge(1, 3, 2);
    g.AddEdge(1, 4, 3);
    g.AddEdge(2, 3, 4);
    g.AddEdge(2, 4, 5);
    g.AddEdge(3, 4, 6);
    
    // Check the edges
    assert(g.EdgesToString() == "[((1)->(2) w:1), ((1)->(3) w:2), ((1)->(4) w:3), ((2)->(3) w:4), ((2)->(4) w:5), ((3)->(4) w:6)]");
    
    cout << "PASSED!" << endl << endl;
}

void TestDisconnectedGraph() {
    cout << "Testing Disconnected Graph..." << endl;
    Graph g = Graph();
    
    // Add nodes for two disconnected components
    g.AddNode(1);
    g.AddNode(2);
    g.AddNode(3);
    g.AddNode(4);
    
    // Add edges only for the first component
    g.AddEdge(1, 2, 2);
    g.AddEdge(2, 3, 3);
    
    // Check the edges for the first component
    assert(g.EdgesToString() == "[((1)->(2) w:2), ((2)->(3) w:3)]");
    
    // Ensure that the second component (nodes 3 and 4) is disconnected
    set<const GraphEdge*> result = g.GetOutwardEdgesFrom(4);
    set<const GraphEdge*> soln;  // empty set
    assert(result.size() == soln.size());
    
    cout << "PASSED!" << endl << endl;
}

int main(){
	
	TestAddNode();
	TestAddEdge();
	TestIsPresentSizeAndOrder();
	TestGetOutwardEdgesFrom();
	TestGetNodes();
	TestDestructor();
	TestGraphWithCycles();
	TestSelfLoop();
    TestEmptyGraph();
    TestOneNodeGraph();
    TestNoOutgoingEdges();
    TestFullyConnectedGraph();
    TestDisconnectedGraph();

	//type this in the terminal to use valgrind "valgrind --leak-check=full ./graph-tests"
	
	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}
