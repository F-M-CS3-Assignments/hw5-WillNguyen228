all:
	g++ -Wall -g Graph.cpp GraphTests.cpp -o graph-tests

run:
	./graph-tests

try: all run