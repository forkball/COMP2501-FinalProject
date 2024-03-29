#include "Graph.h"
#include <iostream>	//used for debug purposes
using namespace std;

//class used to compare 2 nodeTuple structs
class compareNode
{
public:
	int operator() (const QNode &n1, const QNode &n2)
	{
		return n1.cost > n2.cost;
	}
};

//main constructor
//takes the width, height of graph, as well as a gameobject used to render each node.
Graph::Graph(int nodeWidth, int nodeHeight, GameObject nodeSprite) : nodeObj(nodeSprite) {
	//initializes the 2d nodes array and nodeMap
	nodes = std::vector<std::vector<Node>>();
	nodeMap = std::map<int, Node*>();

	//data for setting node positions on, screen.
	float x_b = -6.0f;
	float y_b = 0.2f;
	float movementX = 0.18f;
	float movementY = -0.26f;

	//fills the 2d nodes array with nodes.
	for (int i = 0; i < nodeHeight; i++) {
		std::vector<Node> nodeRow = std::vector<Node>();

		for (int j = 0; j < nodeWidth; j++) {
			//creates each node, starting at (-4.4, 4.4), topLeft, going down, right
			//with x distance .22, y distance .3
			Node newNode = Node(x_b + j * movementX, y_b + i * movementY);
			nodeRow.push_back(newNode);

		}
		nodes.push_back(nodeRow);
	}

	//connects node to each other to form a 4-connected graph with random edge weights
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i).size(); j++) {

			//if there exists a node to the right of the current node, link them together
			if (j + 1 < nodes.at(i).size()) {
				int randWeight = 10 + (rand() % 6);	//creates a random weight between 10-15

				Node *n1 = &nodes.at(i).at(j);		//referncec to current node in graph.
				Node *n2 = &nodes.at(i).at(j + 1);	//reference to node to the left of the current node.

				n1->addNode(*n2, randWeight);			//links both nodes together
			}

			//if there exists a node below the current node, link them together
			if (i + 1 < nodes.size()) {
				int randWeight = 10 + (rand() % 6);	//creates a random weight between 10-15

				Node *n1 = &nodes.at(i).at(j);		//referncec to current node in graph.
				Node *n2 = &nodes.at(i + 1).at(j);	//node below the current node.

				n1->addNode(*n2, randWeight);			//links both nodes together
			}
		}
	}

	//adds all nodes to map with nodeId as key and a pointer to the node
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i).size(); j++) {
			nodeMap.insert(std::pair<int, Node*>(nodes.at(i).at(j).getId(), &nodes.at(i).at(j)));
		}
	}
}

//Loops through array and prints out associated data for each node.
void Graph::printData() {
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i).size(); j++) {
			cout << i << ", " << j << " - " << nodes.at(i).at(j).getId() << " - " << &nodes.at(i).at(j);
			cout << " - " << nodes.at(i).at(j).getEdges().size() << endl;
		}
	}
}

//returns the id of the node at the screen coordinates. If no node exists, it will return -1
int Graph::getNodeIdFromCoords(double _x, double _y) {
	float start_x = -6.0f;
	float start_y = 0.2f;
	float movementX = 0.18f;
	float movementY = -0.26f;

	start_x -= movementX * .5;
	start_y -= movementY * .5;

	int x = (int)((_x - start_x) / movementX);
	int y = (int)((_y - start_y) / movementY);

	//check if the node is 
	if (y >= nodes.size() || y < 0) {
		return -1;
	}
	else if (x >= nodes.at(y).size() || x < 0) {
		return -1;
	}
	else {
		return nodes.at(y).at(x).getId();
	}
}

//returns the id of the node at the mouse coordinates
int Graph::selectNode(double x, double y) {
	unsigned int window_width_g = 800;
	unsigned int window_height_g = 600;

	//if the mouse is outside the window, return -1
	if (x < 0 || x > window_width_g || y < 0 || y > window_height_g) {
		return -1;
	}
	else {
		float cursor_x_pos = (x / (float)(window_width_g / 2)) - 1.0f;	//transforms cursor position to screen coordinates
		float cursor_y_pos = (y / (float)(window_height_g / 2)) - 1.0f;

		cursor_x_pos /= 0.2;
		cursor_y_pos /= 0.2;	//transforms cursor position based on screen scale.

		return getNodeIdFromCoords(cursor_x_pos, cursor_y_pos);
	}
}

//renders all the nodes in the graph
//renders all the nodes in the graph
void Graph::render(Shader &shader) {

	//goes through each node and renders it, using the provided gameObject
	for (int j = 0; j < nodes.size(); j++) {

		if (nodes.size() == 0) {	//if there are no nodes, do nothing.
			return;
		}

		//get the location of the color uniform
		GLint color_loc = glGetUniformLocation(shader.getShaderID(), "colorMod");

		for (int i = 0; i < nodes.at(j).size(); i++) {
			//gets the current node to draw
			Node currentNode = nodes.at(j).at(i);

			//set the node 'pen' to the position of the current node.
			nodeObj.setPosition(glm::vec3(currentNode.getX(), currentNode.getY(), 0.0f));

			//set the color of the node via the color uniform. Default is dark green
			glUniform3f(color_loc, -0.2f, -0.2f, -0.2f);	//dark green

			nodeObj.render(shader);
		}
	}
}

//returns a reference to the node with the supplied id.
Node& Graph::getNode(int id) {

	//because we also store the graph as a map with the id as the key, we can easily reference each node.
	return *nodeMap.at(id);
}

//using zombie-key based approach to Djikstra's algorithm
std::vector<glm::vec2> Graph::pathfind(glm::vec2 start, glm::vec2 end) {
	int startNodeId = getNodeIdFromCoords(start.x, start.y),
		endNodeId = getNodeIdFromCoords(end.x, end.y);
	//final path
	vector<glm::vec2> finalPath;
	//priority queue used in pathfinding.
	//it is created using the NodeTuple struct with a min compare function called compareNode
	priority_queue <QNode, vector<QNode>, compareNode> pq;

	//sets the costs of all nodes to infinity. reset all nodes to be off-path
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i).size(); j++) {
			if (!nodes.at(i).at(j).isObstacle()) nodes.at(i).at(j).setCost(INT_MAX);
			nodes.at(i).at(j).setOnPath(false);
			nodes.at(i).at(j).setVisited(false);
		}
	}

	//The startnode is added to the pq with cost 0
	QNode startNode = { &getNode(startNodeId), 0 };
	pq.push(startNode);

	//now that the pq is setup, we can start the algorithm
	//keep in mind that the as the QNode struct has a pointer to the corresponding node
	//some function calls will use pointer syntax (->) 


	while (!pq.empty()) {
		//get the current lowest-cost node in pq
		QNode lowest = pq.top();

		//if the current node is the end node, done!
		if (lowest.node->getId() == endNodeId) {
			break;
		}

		//OPEN NODE
		vector<Edge> neighbours = lowest.node->getEdges();
		for (int i = 0; i < neighbours.size(); i++) {

			//compute cost to get to neighbouring node
			//cost = the cost to get the corrent node + cost to traverse the edge

			Node *n = &getNode(lowest.node->getOtherNode(neighbours.at(i)).getId());

			n->setVisited(true);
			int nodeCost = lowest.cost + neighbours.at(i).cost;

			//if current node cost is higher than calculated, update node, and add QNode to queue			
			if (n->getCost() > nodeCost) {
				n->setCost(nodeCost);
				n->setPrev(lowest.node);

				QNode updatedNode = { n, nodeCost };
				pq.push(updatedNode);
			}
		}

		pq.pop();	//REMOVE NODE FROM QUEUE
	}

	//queue is done, go in reverse from END to START to determine path
	Node* currentNode = getNode(endNodeId).getPrev();

	//while the current node isn't null, or the end, mark the current node as on the path
	while (currentNode != NULL && currentNode->getId() != startNodeId) {
		currentNode->setOnPath(true);
		finalPath.insert(finalPath.begin(), glm::vec2(currentNode->getX(),currentNode->getY()));
		currentNode = currentNode->getPrev();
	}

	return finalPath;

}