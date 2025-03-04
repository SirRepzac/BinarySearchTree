#pragma once
#include "BTreeNode.h"
#include <sstream>
#include <queue>
using namespace std;

//B-Tree

class BTreeTree
{
public:
	BTreeNode* head;

	BTreeTree();

	void Insert(BTreeNode* newNode);
	void Insert(int key);

	BTreeNode* Find(int key);
	string ToString();

private:

	BTreeNode* FindMethod(int key, BTreeNode* from);

	void InsertMethod(int key, BTreeNode* from);

};