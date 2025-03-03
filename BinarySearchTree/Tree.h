#pragma once
#include "Node.h"
#include <sstream>
#include <queue>
using namespace std;

//B-Tree

class Tree
{
public:
	Node* head;

	Tree();

	void Insert(Node* newNode);
	void Insert(int key);

	Node* Find(int key);
	string ToString();

private:

	Node* FindMethod(int key, Node* from);

	void InsertMethod(int key, Node* from);

};