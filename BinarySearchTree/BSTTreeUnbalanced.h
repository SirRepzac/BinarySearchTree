#pragma once
#pragma once
#include "BSTNode.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BSTTreeUnbalanced
{
	BSTNode* head;

	BSTNode* FindAlgo(int key, BSTNode* currentNode);

	void InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes);

public:
	BSTTreeUnbalanced();
	BSTNode* Find(int key);
	void Insert(int key);
	void Delete(int key);
	void Delete(BSTNode* node);
	void DeleteTree();
};