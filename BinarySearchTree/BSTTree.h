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
	double GetBalanceFactor(BSTNode* node);

	BSTNode* RotateRight(BSTNode* node);

	BSTNode* RotateLeft(BSTNode* node);

	void UpdateNodeAmount(BSTNode* node);
	void InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes);
	void RebalanceAt(BSTNode* node);

	bool CheckIfRebalanceIsNeeded(BSTNode* node);

public:
	BSTTree();
	BSTNode* Find(int key);
	void Insert(int key);
	void Delete(int key);
	void Delete(BSTNode* node);
	void DeleteTree();
};