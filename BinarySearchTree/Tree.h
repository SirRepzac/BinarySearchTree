#pragma once
#include "Node.h"
using namespace std;

//B-Tree

class Tree
{
public:
	Node* head;

	Tree();

	void Insert(Node* newNode);

	Node* Find(int key);

private:

	Node* FindMethod(int key, Node* from);

};