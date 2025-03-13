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
	BSTNode* InsertAndTrack(BSTNode* node, int value, BSTNode*& unbalancedNode);
	double GetBalanceFactor(BSTNode* node);
	void RebalanceAt(BSTNode* node);

	BSTNode* RotateRight(BSTNode* node);

	BSTNode* RotateLeft(BSTNode* node);

	BSTNode* RotateLeftRight(BSTNode* node);

	BSTNode* RotateRightLeft(BSTNode* node);



	BSTNode* FindUnbalancedNode(BSTNode* node);
	void UpdateNodeAmount(BSTNode* node);
	void InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes);
	void Rebalance();
	bool CheckIfRebalanceIsNeeded(BSTNode* node);

public:
	BSTTree();
	BSTNode* Find(int key);
	void Insert(int key);
	void Delete(int key);
	void Delete(BSTNode* node);
	void DeleteTree();
};