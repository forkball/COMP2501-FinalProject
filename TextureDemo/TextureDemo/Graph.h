#pragma once

#include "Node.h"
#include "GameObject.h"

#include <queue>
#include <map>
#include <algorithm>

//struct used to rank various nodes in the priority_queue
struct QNode {
	Node *node;
	int cost;
};

class Graph {
public:
	//constructor. 
	Graph(int nodeWidth, int nodeHeight, GameObject node);
	//Loops through array and prints out associated data for each node.
	void printData();
	//returns the id of the node at the screen coordinates. If no node exists, it will return -1
	int Graph::getNodeIdFromCoords(double x, double y);
	//returns the id of a node from an x/y coordinate
	int selectNode(double x, double y);
	//returns a reference to the node with the supplied id.
	Node& getNode(int id);
	//renders all the nodes in the graph
	void render(Shader &shader);
	//creates and marks a path from start to end
	std::vector<glm::vec2> pathfind(glm::vec2 start, glm::vec2 end);
private:
	//node sprite used to draw each node.
	GameObject nodeObj;
	//2d vector containing all the nodes in the graph
	std::vector<std::vector<Node>> nodes;
	//map used for easy access to nodes via id
	std::map<int, Node*> nodeMap;
};