#pragma once

#include <map>
using namespace std;

class WeightedEdge {
private:
	wstring node1;
	wstring node2;
	float weight;

public:
	WeightedEdge(wstring initNode1, wstring initNode2, float initWeight) {
		this->node1 = initNode1;
		this->node2 = initNode2;
		this->weight = initWeight;
	}
	~WeightedEdge() {
		// NO POINTERS TO CLEAN UP
	}

	wstring getNode1() { return node1; }
	wstring getNode2() { return node2; }
	float getWeight() { return weight; }
};

template <typename T> 
class WeightedGraph {
private:
	std::map<wstring, T*> nodes;
	std::map<wstring, WeightedEdge*> edges;

public:
	WeightedGraph() {}

	void getKeys(vector<wstring>* keys) {
		for (const auto& keyPair : nodes) {
			wstring key = keyPair.first;
			keys->push_back(key);
		}
	}

	bool nodeExists(wstring testNode) {
		return this->nodes.count(testNode) > 0;
	}

	wstring getEdgeId(wstring node1, wstring node2) {
		return node1 + L"-" + node2;
	}

	void addNode(wstring nodeId, T* nodeData) {
		this->nodes[nodeId] = nodeData;
	}

	T* getNodeData(wstring nodeId) {
		return this->nodes[nodeId];
	}

	void addEdge(wstring node1, wstring node2, float weight) {
		wstring edgeId = this->getEdgeId(node1, node2);
		wstring edgeId2 = this->getEdgeId(node2, node1);  // at edge the other way as well 
		this->edges[edgeId] = new WeightedEdge(node1, node2, weight);
		this->edges[edgeId2] = new WeightedEdge(node2, node1, weight); //modified to add edges both ways. 
	}

	void removeEdge(wstring node1, wstring node2) {
        wstring edgeId = this->getEdgeId(node1, node2);
        delete this->edges[edgeId]; 
        this->edges.erase(edgeId);
        wstring edgeId2 = this->getEdgeId(node2, node1);
        delete this->edges[edgeId2]; 
        this->edges.erase(edgeId2);
    }

	bool hasNeighbor(wstring node1, wstring node2) {
		wstring edgeId = this->getEdgeId(node1, node2);
		return this->edges.find(edgeId) != this->edges.end();
	}

	float getNeighborWeight(wstring node1, wstring node2) {
		if (hasNeighbor(node1, node2)) {
			wstring edgeId = this->getEdgeId(node1, node2);
			return this->edges[edgeId]->getWeight();
		}
		return 0.0f;
	}
	/*
	* it gets a list of neighbors of the current node and put it back into the parameter "neighbors"
	*/
	void getNeighbors(vector<wstring>* neighbors, wstring& node) {
		neighbors->clear(); // just in case 
		for ( auto& current_edge : edges) {
			 WeightedEdge* edge = current_edge.second;
			if (edge->getNode1().compare(node) == 0) {
				wstring node2 = edge->getNode2();
				neighbors->push_back(node2);
			}
			else if (edge->getNode2().compare(node) == 0) {
				wstring node1 = edge->getNode1();
				neighbors->push_back(node1);
			}
		}
	}
	std::wstring findClosestNeighbor(vector<wstring>& neighbors, const wstring& current_node) {
		// Initialize the closest neighbor to the first neighbor in the list so that we can compare it to others 
		std::wstring closest_neighbor = neighbors[0];
		float closest_weight = getNeighborWeight(closest_neighbor, current_node);

		// iterate to see if the remaining ones are closer 
		for (size_t x = 0; x < neighbors.size(); ++x) {
			const std::wstring& neighbor = neighbors[x];
			float current_weight = getNeighborWeight(neighbor, current_node);
			if (current_weight < closest_weight) {
				closest_neighbor = neighbor;
				closest_weight = current_weight;
			}
		}

		return closest_neighbor;
	}


	void findPath(vector<wstring>* path, wstring node1, wstring node2) {
		path->clear();  //should clear the path first i am not sure if we need this 
		vector<wstring> visited; //list of visited nodes 
		wstring currentNode = node1;
		path->push_back(currentNode);
		visited.push_back(currentNode);
		while (currentNode != node2) {
			vector<wstring> neighbors;
			getNeighbors(&neighbors, currentNode);  // gets the neighbors of current node 

			// Check if there are any unvisited neighbors
			vector<wstring> unvisitedNeighbors;
			for (const auto& neighbor : neighbors) {
				if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
					unvisitedNeighbors.push_back(neighbor);
				}
			}

			if (unvisitedNeighbors.empty()) { // we need to backtrack now 
				path->pop_back();
				if (path->empty()) { // we can't generate a path. 
					return;
				}
				currentNode = path->back();
			}
			else {
				if (std::find(unvisitedNeighbors.begin(), unvisitedNeighbors.end(), node2) != unvisitedNeighbors.end()) { // check if neighbor has destination 
					path->push_back(node2);
					visited.push_back(node2); // not needed 
					return;
				}
				//go to the cloest neighbor and iterate again, making it the current node 
				currentNode = findClosestNeighbor(unvisitedNeighbors, currentNode);
				path->push_back(currentNode);
				visited.push_back(currentNode);
			}
		}
		wcout << L"Finding path from " << node1 << L" to " << node2 << endl;
	}
};