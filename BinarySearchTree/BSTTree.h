#pragma once
#include "BSTNode.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BSTTree
{
	BSTNode* head;

	float c;

	BSTNode* FindAlgo(int key, BSTNode* currentNode);
	void InsertAlgo(int key, BSTNode* currentNode);
	bool CheckIfRebalanceIsNeeded(BSTNode* node);

	void InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes);

	BSTNode* BuildBalancedTree(vector<BSTNode*>& nodes, int start, int end);

	void Rebalance(); // Not yet implemented
	void InOrderTraversalWithDepth(BSTNode* node, vector<pair<BSTNode*, int>>& nodesWithDepth, int depth);

public:
	BSTTree();
	BSTNode* Find(int key);
	void Insert(int key);
	void Delete(int key);
	void Delete(BSTNode* node);
	string ToString();


};