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
	if (leftChild != nullptr)
		counter++;
	if (rightChild != nullptr)
		counter++;
	return counter;
}

bool BSTNode::IsLeaf()
{
	return ChildAmount() == 0;
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

	return key < this->key ? leftChild : rightChild;
}

int BSTNode::GetNextNodeId(int key)
{
	return key < this->key ? 0 : 1;
}

int BSTNode::GetChildId(BSTNode* node)
{
	if (leftChild == node)
		return 0;
	if (rightChild == node)
		return 1;
	return -1;
}

void BSTNode::SetNewChild(int newKey)
{
	int childId = GetNextNodeId(newKey);
	BSTNode* node = new BSTNode(newKey);
	node->parent = this;
	if (childId == 0)
		leftChild = node;
	else
		rightChild = node;
}

void BSTNode::DeleteChild(BSTNode* child)
{
	if (leftChild == child)
		leftChild = nullptr;
	else if (rightChild == child)
		rightChild = nullptr;
}

int BSTNode::GetNodeAmount()
{
	int nodeAmount = 1;
	if (leftChild != nullptr)
	{
		nodeAmount += leftChild->GetNodeAmount();
	}
	if (rightChild != nullptr)
	{
		nodeAmount += rightChild->GetNodeAmount();
	}
	return nodeAmount;
}

string BSTNode::ToString()
{	
	return "[" + to_string(key) + "]";
}

BSTNode* BSTNode::GetSmallest()
{
	return leftChild == nullptr ? this : leftChild->GetSmallest();
}
