#pragma once
#include "BSTNode.h"

#include <iostream>
#include <string>

using namespace std;

class BSTTree
{
	BSTNode* head;

	float c;

	BSTNode* FindAlgo(int key, BSTNode* currentNode);
	void InsertAlgo(int key, BSTNode* currentNode);
	bool CheckIfRebalanceIsNeeded(BSTNode* node);

	void Rebalance(); // Not yet implemented
public:
	BSTTree();
	BSTNode* Find(int key);
	void Insert(int key);
	void Delete(int key);
	void Delete(BSTNode* node);
	string ToString();

};