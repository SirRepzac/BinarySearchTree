#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

// Order 3, has 3 children
class BTreeTree;

class BTreeNode
{
	friend BTreeTree;

public:
	static const int maxKeyAmount = 2;

	int keyAmount;

	BTreeNode();

	void SetValues(int* keys);

	string ToString() const;

private:
	BTreeNode* parent;

	union
	{
		BTreeNode* children[maxKeyAmount+1];
		struct
		{
			BTreeNode* childLeft;
			BTreeNode* childMiddle;
			BTreeNode* childRight;
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

	void RemoveChild(BTreeNode* child);

	void AddKey(int key);

	BTreeNode* GetSibling();

	tuple<int, tuple<BTreeNode*, BTreeNode*>> Split(int key);

	int GetKeyPos(int key);

	int GetChildLocation(BTreeNode* child);

	BTreeNode* NextNode(int key) const;

	int NodeNeedsKey();

	BTreeNode* GetEmptyChild();

	void SortKeys();

	void SortChildren();

	bool HasMaxChildren();

	int GetMiddleKey(int* keys);

	bool IsLeaf();


};