#include "BSTNode.h"

using namespace std;

BSTNode::BSTNode()
{
	this->key = 0;
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
}

BSTNode::BSTNode(int key)
{
	this->key = key;
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
}

int BSTNode::ChildAmount()
{
	int counter = 0;
	for (int i = 0; i < 2; i++)
	{
		if (children[i] != nullptr)
			counter++;
	}
	return counter;
}

bool BSTNode::IsLeaf()
{
	if (ChildAmount() == 0)
		return true;
	else
		return false;
}

int BSTNode::GetHeight()
{
	int leftChildHeight = 0;
	int rightChildHeight = 0;

	if (IsLeaf())
	{
		return 0;
	}

	if (leftChild != nullptr)
	{
		leftChildHeight = leftChild->GetHeight();
	}
	if (rightChild != nullptr)
	{
		rightChildHeight = rightChild->GetHeight();
	}

	int largerHeight = rightChildHeight > leftChildHeight ? rightChildHeight : leftChildHeight;
	return largerHeight + 1;

}

BSTNode* BSTNode::GetNextNode(int key)
{

	return children[GetNextNodeId(key)];
}

int BSTNode::GetNextNodeId(int key)
{
	if (key < this->key)
		return 0;
	else
		return 1;
}

int BSTNode::GetChildId(BSTNode* node)
{
	for (int i = 0; i < 2; i++)
	{
		if (children[i] == node)
			return i;
	}

	return -1;
}

void BSTNode::SetNewChild(int newKey)
{
	int childId = GetNextNodeId(newKey);
	BSTNode* node = new BSTNode(newKey);
	node->parent = this;
	children[childId] = node;
}

void BSTNode::DeleteChild(BSTNode* child)
{
	
	children[GetChildId(child)] = nullptr;
}

int BSTNode::GetNodeAmount()
{
	int nodeAmount = 1;
	if (IsLeaf())
	{
		return 1;
	}
	else
	{
		if (rightChild != nullptr)
		{
			nodeAmount += rightChild->GetNodeAmount();
		}
		if (leftChild != nullptr)
		{
			nodeAmount += leftChild->GetNodeAmount();
		}

		return nodeAmount;
	}
}

string BSTNode::ToString()
{	
	return "[" + to_string(key) + "]";
}

BSTNode* BSTNode::GetSmallest()
{
	if (leftChild == nullptr)
	{
		return this;
	}
	else
	{
		return leftChild->GetSmallest();
	}
}
