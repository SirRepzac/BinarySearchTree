#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Order 3, has 3 children
class Tree;
class BTreePrinter;

class Node
{
	friend Tree;
	friend BTreePrinter;

public:
	static const int maxKeyAmount = 2;

	int keyAmount;

	Node();

	void SetValues(int* keys);

	string ToString() const;

private:
	Node* parent;

	union
	{
		Node* children[maxKeyAmount+1];
		struct
		{
			Node* childLeft;
			Node* childMiddle;
			Node* childRight;
		};
	};

	union
	{
		int keys[maxKeyAmount];

		struct
		{
			int keyLeft;
			int keyRight;
		};
	};


	bool IsKeyInNode(int key) const;

	void RemoveKey(int key);

	void ClearChildren();

	void ClearKeys();

	void SetKeyAmount();

	void RemoveChild(Node* child);

	void AddKeyAndChild(int key, Node* newChild, Node* oldChild);

	Node* GetLeftSibling();

	void Split(int key);

	int GetKeyPos(int key);

	int GetChildLocation(Node* child);

	Node* NextNode(int key) const;

	int NodeNeedsKey();

	void AddNewKey(int key, int position);

	void SortKeys();

	void SortChildren();

	bool HasMaxChildren();

	int GetMiddleKey(int* keys);

	bool IsLeaf();


};