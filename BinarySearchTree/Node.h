#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
using namespace std;

// Order 3, has 3 children
class Tree;

class Node
{
	friend Tree;

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

	Node* NextNode(int key) const;

	int NodeNeedsKey();

	void AddNewKey(int key, int position);

	void SortKeys();

	int GetMiddleKey(int* keys);

	int* GetExtendedKeysSorted(int key);

	bool IsLeaf();

	void Restructure(int key, Node* nodes);

};