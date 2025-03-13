#pragma once

#include <iostream>
#include <string>

using namespace std;

class BSTTree;
class BSTTreeUnbalanced;

class BSTNode
{

	friend BSTTree;
	friend BSTTreeUnbalanced;

	int key;

	int nodeAmount;

	BSTNode* parent;

	BSTNode* leftChild;
	BSTNode* rightChild;

	BSTNode();
	BSTNode(int key);

	int ChildAmount();
	bool IsLeaf();

	int GetHeight();

	BSTNode* GetNextNode(int key);
	int GetNextNodeId(int key);

	int GetChildId(BSTNode* node);

	void SetNewChild(int newKey);
	void DeleteChild(BSTNode* child);

	string ToString();

	BSTNode* GetSmallest();
};