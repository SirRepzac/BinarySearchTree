#pragma once

#include <iostream>
#include <string>

using namespace std;

class BSTTree;

class BSTNode
{

	friend BSTTree;
	int key;

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

	int GetNodeAmount();

	string ToString();

	BSTNode* GetSmallest();
};